// =============================================================================
// server.cpp — Servidor HTTP do Manager FC
//
// Este arquivo substitui o main.cpp no "modo web".
// Em vez de um menu no terminal, o jogo expõe rotas HTTP que o navegador
// pode chamar. O frontend (HTML/JS) fica na pasta /frontend.
//
// Rotas disponíveis:
//   GET  /api/times           → lista os 20 times (tela de escolha)
//   POST /api/escolher-time   → jogador escolhe seu clube
//   GET  /api/status          → estado atual do jogo
//   GET  /api/tabela          → classificação
//   GET  /api/elenco          → elenco do meu time
//   POST /api/jogar-rodada    → simula a próxima rodada
//   POST /api/mudar-formacao  → muda a formação tática
//   POST /api/melhorar-elenco → gasta orçamento para +força
//   GET  /api/historico       → histórico de partidas
// =============================================================================

// No Windows, essa linha é necessária para o httplib funcionar corretamente
#ifdef _WIN32
  #define _WIN32_WINNT 0x0A00
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "httplib.h"
#include "GameState.h"

// =============================================================================
// ESTADO GLOBAL DO JOGO
// Essas variáveis ficam vivas enquanto o servidor estiver rodando.
// São acessadas por todos os handlers (funções de rota).
// =============================================================================
static bool             g_iniciado    = false;
static Time*            g_meuTime     = nullptr;
static int              g_rodadaAtual = 0;
static Simulacao        g_simulacao;
static AVL<Time*>       g_tabela(compararTimes);

// Ponteiros para objetos criados em main() — ficam vivos porque
// svr.listen() bloqueia main() indefinidamente.
static Queue<Rodada*>*      g_calendario = nullptr;
static LinkedList<Resultado>* g_historico = nullptr;

// =============================================================================
// FUNÇÕES QUE CONSTROEM JSON
// Constroem strings JSON manualmente — sem biblioteca extra.
// Cada função lê o estado global e retorna o JSON correspondente.
// =============================================================================

// Escapa aspas dentro de strings para produzir JSON válido
static std::string esc(const std::string& s) {
    std::string out;
    for (char c : s) {
        if (c == '"') out += "\\\"";
        else          out += c;
    }
    return out;
}

// Converte int para string (atalho)
static std::string i2s(int n)   { return std::to_string(n); }
static std::string f2s(float f) { return std::to_string((int)f); }

// ------------------------------------------------------------------
// jsonTimes: lista dos 20 times para a tela de escolha inicial
// ------------------------------------------------------------------
static std::string jsonTimes() {
    std::string j = "{\"times\":[";
    for (int i = 0; i < NUM_TIMES; i++) {
        Time& t = times[i];
        if (i > 0) j += ",";
        j += "{\"id\":"       + i2s(t.getId())        + ","
           + "\"nome\":\""    + esc(t.getNome())       + "\","
           + "\"sigla\":\""   + esc(t.getSigla())      + "\","
           + "\"forca\":"     + i2s(t.getForca())      + ","
           + "\"orcamento\":" + f2s(t.getOrcamento())  + ","
           + "\"formacao\":\"" + esc(t.getFormacao())  + "\"}";
    }
    return j + "]}";
}

// ------------------------------------------------------------------
// jsonTabela: classificação atual (do 1º ao 20º)
// ------------------------------------------------------------------
static std::string jsonTabela() {
    std::string j = "{\"tabela\":[";
    int pos = 1;
    bool primeiro = true;

    g_tabela.forEach([&](Time* const& t) {
        std::string marca = (pos <= 6) ? "LIB" : (pos <= 12) ? "SUL" : (pos >= 17) ? "REL" : "";

        if (!primeiro) j += ",";
        primeiro = false;

        j += "{\"pos\":"      + i2s(pos)               + ","
           + "\"nome\":\""    + esc(t->getNome())       + "\","
           + "\"sigla\":\""   + esc(t->getSigla())      + "\","
           + "\"pontos\":"    + i2s(t->getPontos())     + ","
           + "\"v\":"         + i2s(t->getVitorias())   + ","
           + "\"e\":"         + i2s(t->getEmpates())    + ","
           + "\"d\":"         + i2s(t->getDerrotas())   + ","
           + "\"gp\":"        + i2s(t->getGolsPro())    + ","
           + "\"gc\":"        + i2s(t->getGolsContra()) + ","
           + "\"sg\":"        + i2s(t->getSaldoGols())  + ","
           + "\"marca\":\""   + marca                   + "\","
           + "\"meuTime\":"   + (t == g_meuTime ? "true" : "false") + "}";
        pos++;
    });

    return j + "]}";
}

// ------------------------------------------------------------------
// jsonElenco: jogadores do time do jogador
// ------------------------------------------------------------------
static std::string jsonElenco() {
    Time* t = g_meuTime;
    std::string j = "{"
        "\"nome\":\""     + esc(t->getNome())    + "\","
        "\"forca\":"      + i2s(t->getForca())   + ","
        "\"orcamento\":"  + f2s(t->getOrcamento()) + ","
        "\"formacao\":\"" + esc(t->getFormacao()) + "\","
        "\"pontos\":"     + i2s(t->getPontos())  + ","
        "\"jogadores\":[";

    for (int i = 0; i < t->getNumJogadores(); i++) {
        const Jogador* jog = t->getJogador(i);
        if (i > 0) j += ",";
        j += "{\"nome\":\""     + esc(jog->getNome())       + "\","
           + "\"tipo\":\""      + esc(jog->getTipo())       + "\","
           + "\"posicao\":\""   + esc(jog->getPosicao())    + "\","
           + "\"habilidade\":"  + i2s(jog->getHabilidade()) + "}";
    }
    return j + "]}";
}

// ------------------------------------------------------------------
// jsonJogarRodada: simula a próxima rodada e retorna os resultados
// ------------------------------------------------------------------
static std::string jsonJogarRodada() {
    if (g_calendario->empty())
        return "{\"erro\":\"Temporada encerrada\"}";

    Rodada* r = g_calendario->dequeue();
    g_rodadaAtual = r->getNumero();

    std::string j = "{\"rodada\":" + i2s(g_rodadaAtual) + ",\"partidas\":[";
    bool primeiro = true;

    for (int i = 0; i < r->getNumPartidas(); i++) {
        Partida* p = r->getPartida(i);

        // Remove os dois times da AVL, simula, reinsere na posição correta
        g_tabela.remove(p->getTimeCasa());
        g_tabela.remove(p->getTimeVisitante());
        g_simulacao.simularPartida(*p);
        g_tabela.insert(p->getTimeCasa());
        g_tabela.insert(p->getTimeVisitante());

        bool minha = (p->getTimeCasa() == g_meuTime || p->getTimeVisitante() == g_meuTime);

        if (!primeiro) j += ",";
        primeiro = false;

        j += "{\"casa\":\""   + esc(p->getTimeCasa()->getNome())       + "\","
           + "\"visit\":\""   + esc(p->getTimeVisitante()->getNome())   + "\","
           + "\"golsCasa\":"  + i2s(p->getGolsCasa())                  + ","
           + "\"golsVisit\":" + i2s(p->getGolsVisitante())             + ","
           + "\"minha\":"     + (minha ? "true" : "false")             + "}";

        // Guarda no histórico (LinkedList)
        Resultado res;
        res.rodada    = g_rodadaAtual;
        res.timeCasa  = p->getTimeCasa()->getNome();
        res.timeVisit = p->getTimeVisitante()->getNome();
        res.golsCasa  = p->getGolsCasa();
        res.golsVisit = p->getGolsVisitante();
        g_historico->pushBack(res);

        delete p;
    }
    delete r;

    bool encerrada = g_calendario->empty();
    return j + "],\"encerrada\":" + (encerrada ? "true" : "false") + "}";
}

// ------------------------------------------------------------------
// jsonHistorico: partidas jogadas pelo time do jogador
// ------------------------------------------------------------------
static std::string jsonHistorico() {
    std::string nomeTime = g_meuTime->getNome();
    std::string j = "{\"historico\":[";
    bool primeiro = true;

    g_historico->forEach([&](const Resultado& r) {
        if (r.timeCasa != nomeTime && r.timeVisit != nomeTime) return;
        if (!primeiro) j += ",";
        primeiro = false;
        j += "{\"rodada\":"     + i2s(r.rodada)       + ","
           + "\"casa\":\""      + esc(r.timeCasa)      + "\","
           + "\"visit\":\""     + esc(r.timeVisit)     + "\","
           + "\"golsCasa\":"    + i2s(r.golsCasa)      + ","
           + "\"golsVisit\":"   + i2s(r.golsVisit)     + "}";
    });

    return j + "]}";
}

// =============================================================================
// FUNÇÃO AUXILIAR: extrai valor de um campo JSON simples da string do body
// Exemplo: extrair(body, "id") em '{"id":3}' retorna "3"
// =============================================================================
static std::string extrair(const std::string& body, const std::string& campo) {
    std::string chave = "\"" + campo + "\":";
    size_t pos = body.find(chave);
    if (pos == std::string::npos) return "";
    pos += chave.size();
    while (pos < body.size() && body[pos] == ' ') pos++;

    if (body[pos] == '"') {          // valor é string
        pos++;
        size_t fim = body.find('"', pos);
        return body.substr(pos, fim - pos);
    } else {                          // valor é número
        size_t fim = pos;
        while (fim < body.size() && body[fim] != ',' && body[fim] != '}') fim++;
        return body.substr(pos, fim - pos);
    }
}

// =============================================================================
// MAIN: inicializa o jogo e sobe o servidor
// =============================================================================
int main() {
    srand((unsigned)time(nullptr));

    // Preenche os elencos dos 20 times via polimorfismo
    for (int i = 0; i < NUM_TIMES; i++)
        preencherElenco(times[i]);

    // Cria o calendário e o histórico como variáveis locais de main().
    // Ficam vivos enquanto svr.listen() estiver rodando.
    Queue<Rodada*>     calendario = gerarCalendario();
    LinkedList<Resultado> historico;

    g_calendario = &calendario;
    g_historico  = &historico;

    // -----------------------------------------------------------------------
    // Configura o servidor
    // -----------------------------------------------------------------------
    httplib::Server svr;

    // Serve os arquivos da pasta /frontend (HTML, CSS, JS)
    svr.set_mount_point("/", "./frontend");

    // Cabeçalhos CORS — permite que o navegador faça requisições ao servidor
    svr.set_default_headers({
        {"Access-Control-Allow-Origin",  "*"},
        {"Access-Control-Allow-Methods", "GET, POST, OPTIONS"},
        {"Access-Control-Allow-Headers", "Content-Type"}
    });

    // -----------------------------------------------------------------------
    // ROTAS
    // -----------------------------------------------------------------------

    // GET /api/times — lista os 20 times (usada na tela de escolha)
    svr.Get("/api/times", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(jsonTimes(), "application/json");
    });

    // GET /api/status — diz se o jogo foi iniciado e qual a rodada atual
    svr.Get("/api/status", [](const httplib::Request&, httplib::Response& res) {
        if (!g_iniciado) {
            res.set_content("{\"iniciado\":false}", "application/json");
            return;
        }
        std::string j = "{\"iniciado\":true,"
            "\"rodada\":"    + i2s(g_rodadaAtual)            + ","
            "\"meuTime\":\"" + esc(g_meuTime->getNome())     + "\","
            "\"pontos\":"    + i2s(g_meuTime->getPontos())   + ","
            "\"encerrada\":" + (g_calendario->empty() ? "true" : "false") + "}";
        res.set_content(j, "application/json");
    });

    // POST /api/escolher-time — jogador escolhe seu clube
    // Body esperado: {"id": 3}
    svr.Post("/api/escolher-time", [](const httplib::Request& req, httplib::Response& res) {
        if (g_iniciado) {
            res.set_content("{\"erro\":\"jogo ja iniciado\"}", "application/json");
            return;
        }
        std::string idStr = extrair(req.body, "id");
        if (idStr.empty()) {
            res.set_content("{\"erro\":\"id nao informado\"}", "application/json");
            return;
        }
        int id = std::stoi(idStr);
        Time* escolhido = nullptr;
        for (int i = 0; i < NUM_TIMES; i++) {
            if (times[i].getId() == id) { escolhido = &times[i]; break; }
        }
        if (!escolhido) {
            res.set_content("{\"erro\":\"time nao encontrado\"}", "application/json");
            return;
        }

        // Inicializa o estado
        g_meuTime    = escolhido;
        g_iniciado   = true;
        g_rodadaAtual = 0;
        for (int i = 0; i < NUM_TIMES; i++)
            g_tabela.insert(&times[i]);

        res.set_content("{\"ok\":true,\"nome\":\"" + esc(escolhido->getNome()) + "\"}", "application/json");
    });

    // GET /api/tabela
    svr.Get("/api/tabela", [](const httplib::Request&, httplib::Response& res) {
        if (!g_iniciado) { res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json"); return; }
        res.set_content(jsonTabela(), "application/json");
    });

    // GET /api/elenco
    svr.Get("/api/elenco", [](const httplib::Request&, httplib::Response& res) {
        if (!g_iniciado) { res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json"); return; }
        res.set_content(jsonElenco(), "application/json");
    });

    // POST /api/jogar-rodada
    svr.Post("/api/jogar-rodada", [](const httplib::Request&, httplib::Response& res) {
        if (!g_iniciado) { res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json"); return; }
        res.set_content(jsonJogarRodada(), "application/json");
    });

    // POST /api/mudar-formacao
    // Body esperado: {"formacao": "4-3-3"}
    svr.Post("/api/mudar-formacao", [](const httplib::Request& req, httplib::Response& res) {
        if (!g_iniciado) { res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json"); return; }
        std::string formacao = extrair(req.body, "formacao");
        if (formacao.empty()) { res.set_content("{\"erro\":\"formacao nao informada\"}", "application/json"); return; }
        g_meuTime->setFormacao(formacao);
        res.set_content("{\"ok\":true,\"formacao\":\"" + formacao + "\"}", "application/json");
    });

    // POST /api/melhorar-elenco
    // Body esperado: {"qtd": 2}
    svr.Post("/api/melhorar-elenco", [](const httplib::Request& req, httplib::Response& res) {
        if (!g_iniciado) { res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json"); return; }
        const float CUSTO = 15.0f;
        std::string qtdStr = extrair(req.body, "qtd");
        if (qtdStr.empty()) { res.set_content("{\"erro\":\"qtd nao informado\"}", "application/json"); return; }
        int qtd = std::stoi(qtdStr);
        if (qtd * CUSTO > g_meuTime->getOrcamento()) {
            res.set_content("{\"erro\":\"orcamento insuficiente\"}", "application/json"); return;
        }
        g_meuTime->setForca(g_meuTime->getForca() + qtd);
        g_meuTime->setOrcamento(g_meuTime->getOrcamento() - qtd * CUSTO);
        res.set_content("{\"ok\":true,\"forca\":" + i2s(g_meuTime->getForca())
            + ",\"orcamento\":" + f2s(g_meuTime->getOrcamento()) + "}", "application/json");
    });

    // GET /api/historico
    svr.Get("/api/historico", [](const httplib::Request&, httplib::Response& res) {
        if (!g_iniciado) { res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json"); return; }
        res.set_content(jsonHistorico(), "application/json");
    });

    // -----------------------------------------------------------------------
    std::cout << "===============================" << std::endl;
    std::cout << "   Manager FC — Servidor Web   " << std::endl;
    std::cout << "   http://localhost:8080        " << std::endl;
    std::cout << "   Ctrl+C para encerrar         " << std::endl;
    std::cout << "===============================" << std::endl;

    svr.listen("0.0.0.0", 8080);
    return 0;
}