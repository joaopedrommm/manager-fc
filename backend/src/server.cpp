// =============================================================================
// server.cpp — Manager FC HTTP API
// =============================================================================

#ifdef _WIN32
  #define _WIN32_WINNT 0x0A00   // Windows 10+  <-- linha nova
  #define WIN32_LEAN_AND_MEAN
  #include <winsock2.h>
  #include <ws2tcpip.h>
#endif

#include "httplib.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#include "models/Campeonato.h"
#include "models/Calendario.h"
#include "models/Simulacao.h"
#include "models/Jogador.h"
#include "models/Goleiro.h"
#include "models/JogadorDeCampo.h"
#include "colecoes/AVL.h"
#include "colecoes/LinkedList.h"
#include "colecoes/Queue.h"
#include "data/elencos.h"

// ---------------------------------------------------------------------------
// Mesmas funcoes auxiliares do main.cpp
// ---------------------------------------------------------------------------
static int compararTimes(Time* const& a, Time* const& b) {
    if (a->getPontos()    != b->getPontos())    return a->getPontos()    - b->getPontos();
    if (a->getVitorias()  != b->getVitorias())  return a->getVitorias()  - b->getVitorias();
    if (a->getSaldoGols() != b->getSaldoGols()) return a->getSaldoGols() - b->getSaldoGols();
    if (a->getGolsPro()   != b->getGolsPro())   return a->getGolsPro()   - b->getGolsPro();
    return b->getId() - a->getId();
}

static void preencherElencoReal(Time& t) {
    switch (t.getId()) {
        case  1: criarFlamengo(t);      break;
        case  2: criarAtleticoMg(t);    break;
        case  3: criarPalmeiras(t);     break;
        case  4: criarFluminense(t);    break;
        case  5: criarAthleticoPr(t);   break;
        case  6: criarInternacional(t); break;
        case  7: criarSaoPaulo(t);      break;
        case  8: criarGremio(t);        break;
        case  9: criarBotafogo(t);      break;
        case 10: criarVasco(t);         break;
        case 11: criarCorinthians(t);   break;
        case 12: criarCruzeiro(t);      break;
        case 13: criarBahia(t);         break;
        case 14: criarSantos(t);        break;
        case 15: criarBragantino(t);    break;
        case 16: criarChapecoense(t);   break;
        case 17: criarCoritiba(t);      break;
        case 18: criarVitoria(t);       break;
        case 19: criarMirassol(t);      break;
        case 20: criarRemo(t);          break;
    }
}

// ---------------------------------------------------------------------------
// Resultado compacto para historico
// ---------------------------------------------------------------------------
class ResPartida {
public:
    int rodada;
    std::string timeCasa, timeVisit;
    int golsCasa, golsVisit;
};

// ---------------------------------------------------------------------------
// Estado global do jogo — persiste entre requisicoes HTTP
// ---------------------------------------------------------------------------
class EstadoJogo {
public:
    bool            iniciado    = false;
    int             meuTimeId   = -1;
    AVL<Time*>*     tabela      = nullptr;
    Queue<Rodada*>* calendario  = nullptr;
    Simulacao*      sim         = nullptr;
    LinkedList<ResPartida>* historico = nullptr;
    int             rodadaAtual = 0;

    void reset() {
        // Drena e libera o calendario restante
        if (calendario) {
            while (!calendario->empty()) {
                Rodada* r = calendario->dequeue();
                for (int i = 0; i < r->getNumPartidas(); i++)
                    delete r->getPartida(i);
                delete r;
            }
            delete calendario;
            calendario = nullptr;
        }
        delete tabela;    tabela    = nullptr;
        delete sim;       sim       = nullptr;
        delete historico; historico = nullptr;
        iniciado    = false;
        meuTimeId   = -1;
        rodadaAtual = 0;
        for (int i = 0; i < NUM_TIMES; i++) times[i].resetStats();
    }
} jogo;

// ---------------------------------------------------------------------------
// JSON helpers
// ---------------------------------------------------------------------------
static void cors(httplib::Response& res) {
    res.set_header("Access-Control-Allow-Origin",  "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

static std::string esc(const std::string& s) {
    std::string r;
    for (char c : s) {
        if      (c == '"')  r += "\\\"";
        else if (c == '\\') r += "\\\\";
        else r += c;
    }
    return r;
}

static std::string q(const std::string& s) { return "\"" + esc(s) + "\""; }

static std::string jsonTime(const Time& t) {
    std::ostringstream o;
    o << std::fixed << std::setprecision(1);
    o << "{"
      << "\"id\":"         << t.getId()          << ","
      << "\"nome\":"       << q(t.getNome())      << ","
      << "\"sigla\":"      << q(t.getSigla())     << ","
      << "\"forca\":"      << t.getForca()        << ","
      << "\"orcamento\":"  << t.getOrcamento()    << ","
      << "\"formacao\":"   << q(t.getFormacao())  << ","
      << "\"pontos\":"     << t.getPontos()       << ","
      << "\"vitorias\":"   << t.getVitorias()     << ","
      << "\"empates\":"    << t.getEmpates()      << ","
      << "\"derrotas\":"   << t.getDerrotas()     << ","
      << "\"golsPro\":"    << t.getGolsPro()      << ","
      << "\"golsContra\":" << t.getGolsContra()   << ","
      << "\"saldo\":"      << t.getSaldoGols()
      << "}";
    return o.str();
}

static int parseIntKey(const std::string& body, const std::string& key) {
    auto pos = body.find("\"" + key + "\"");
    if (pos == std::string::npos) return -1;
    pos = body.find(':', pos);
    if (pos == std::string::npos) return -1;
    while (++pos < body.size() && (body[pos] == ' ' || body[pos] == '\t'));
    try { return std::stoi(body.substr(pos)); } catch (...) { return -1; }
}

static std::string parseStrKey(const std::string& body, const std::string& key) {
    auto pos = body.find("\"" + key + "\"");
    if (pos == std::string::npos) return "";
    pos = body.find('"', body.find(':', pos) + 1);
    if (pos == std::string::npos) return "";
    auto end = body.find('"', pos + 1);
    if (end == std::string::npos) return "";
    return body.substr(pos + 1, end - pos - 1);
}

// Drena Queue<Rodada*> gerada por gerarCalendario() para o heap
static Queue<Rodada*>* alocarCalendario() {
    Queue<Rodada*>  tmp = gerarCalendario();  // RVO — sem copia
    Queue<Rodada*>* cal = new Queue<Rodada*>();
    while (!tmp.empty()) cal->enqueue(tmp.dequeue());
    return cal;
}

// ---------------------------------------------------------------------------
// main — registra rotas e sobe o servidor
// ---------------------------------------------------------------------------
int main() {
    srand((unsigned)time(nullptr));

    std::cout << "Inicializando elencos..." << std::endl;
    for (int i = 0; i < NUM_TIMES; i++) preencherElencoReal(times[i]);
    std::cout << "Pronto. Iniciando servidor na porta 8080..." << std::endl;

    httplib::Server svr;

    // CORS preflight
    svr.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        cors(res); res.status = 204;
    });

    // -----------------------------------------------------------------------
    // GET /api/times — lista os 20 times com forca e formacao
    // -----------------------------------------------------------------------
    svr.Get("/api/times", [](const httplib::Request&, httplib::Response& res) {
        cors(res);
        std::string json = "[";
        for (int i = 0; i < NUM_TIMES; i++) {
            if (i > 0) json += ",";
            json += jsonTime(times[i]);
        }
        json += "]";
        res.set_content(json, "application/json");
    });

    // -----------------------------------------------------------------------
    // POST /api/iniciar   body: {"id": 1}
    // -----------------------------------------------------------------------
    svr.Post("/api/iniciar", [](const httplib::Request& req, httplib::Response& res) {
        cors(res);
        int id = parseIntKey(req.body, "id");
        if (id < 1 || id > NUM_TIMES) {
            res.status = 400;
            res.set_content("{\"erro\":\"id invalido\"}", "application/json");
            return;
        }
        jogo.reset();
        jogo.iniciado    = true;
        jogo.meuTimeId   = id;
        jogo.tabela      = new AVL<Time*>(compararTimes);
        jogo.sim         = new Simulacao();
        jogo.historico   = new LinkedList<ResPartida>();
        jogo.calendario  = alocarCalendario();
        jogo.rodadaAtual = 0;
        for (int i = 0; i < NUM_TIMES; i++) jogo.tabela->insert(&times[i]);

        std::string json = "{\"ok\":true,\"time\":" + jsonTime(times[id - 1]) + "}";
        res.set_content(json, "application/json");
    });

    // -----------------------------------------------------------------------
    // GET /api/estado
    // -----------------------------------------------------------------------
    svr.Get("/api/estado", [](const httplib::Request&, httplib::Response& res) {
        cors(res);
        if (!jogo.iniciado) {
            res.set_content("{\"iniciado\":false}", "application/json");
            return;
        }
        std::ostringstream o;
        o << "{"
          << "\"iniciado\":true,"
          << "\"rodadaAtual\":"  << jogo.rodadaAtual << ","
          << "\"totalRodadas\":38,"
          << "\"encerrado\":"    << (jogo.calendario->empty() ? "true" : "false") << ","
          << "\"meuTime\":"      << jsonTime(times[jogo.meuTimeId - 1])
          << "}";
        res.set_content(o.str(), "application/json");
    });

    // -----------------------------------------------------------------------
    // GET /api/tabela
    // -----------------------------------------------------------------------
    svr.Get("/api/tabela", [](const httplib::Request&, httplib::Response& res) {
        cors(res);
        if (!jogo.iniciado) { res.set_content("[]", "application/json"); return; }

        std::string json = "[";
        bool first = true;
        int pos = 1;
        jogo.tabela->forEach([&](Time* const& t) {
            if (!first) json += ",";
            first = false;
            std::string base = jsonTime(*t);
            // insere "pos" como primeiro campo: {"pos":1,"id":...}
            json += "{\"pos\":" + std::to_string(pos++) + "," + base.substr(1);
        });
        json += "]";
        res.set_content(json, "application/json");
    });

    // -----------------------------------------------------------------------
    // GET /api/elenco
    // -----------------------------------------------------------------------
    svr.Get("/api/elenco", [](const httplib::Request&, httplib::Response& res) {
        cors(res);
        if (!jogo.iniciado) {
            res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json");
            return;
        }
        const Time& t = times[jogo.meuTimeId - 1];
        std::string json = "[";
        for (int i = 0; i < t.getNumJogadores(); i++) {
            if (i > 0) json += ",";
            const Jogador* j = t.getJogador(i);
            std::ostringstream o;
            o << "{"
              << "\"numero\":"    << (i + 1)           << ","
              << "\"nome\":"      << q(j->getNome())    << ","
              << "\"tipo\":"      << q(j->getTipo())    << ","
              << "\"habilidade\":" << j->getHabilidade()
              << "}";
            json += o.str();
        }
        json += "]";
        res.set_content(json, "application/json");
    });

    // -----------------------------------------------------------------------
    // POST /api/jogar-rodada
    // -----------------------------------------------------------------------
    svr.Post("/api/jogar-rodada", [](const httplib::Request&, httplib::Response& res) {
        cors(res);
        if (!jogo.iniciado) {
            res.status = 400;
            res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json");
            return;
        }
        if (jogo.calendario->empty()) {
            res.set_content("{\"encerrado\":true}", "application/json");
            return;
        }

        Rodada* r = jogo.calendario->dequeue();
        jogo.rodadaAtual = r->getNumero();
        Time* meuTime = &times[jogo.meuTimeId - 1];

        // Identifica minha partida
        Partida* minhaPartida = nullptr;
        for (int i = 0; i < r->getNumPartidas(); i++) {
            Partida* p = r->getPartida(i);
            if (p->getTimeCasa() == meuTime || p->getTimeVisitante() == meuTime) {
                minhaPartida = p;
                break;
            }
        }

        // Simula todas as partidas
        std::string outrasJson = "[";
        bool firstOutra = true;

        for (int i = 0; i < r->getNumPartidas(); i++) {
            Partida* p = r->getPartida(i);
            jogo.tabela->remove(p->getTimeCasa());
            jogo.tabela->remove(p->getTimeVisitante());
            jogo.sim->simularPartida(*p);
            jogo.tabela->insert(p->getTimeCasa());
            jogo.tabela->insert(p->getTimeVisitante());

            ResPartida rp;
            rp.rodada   = jogo.rodadaAtual;
            rp.timeCasa  = p->getTimeCasa()->getNome();
            rp.timeVisit = p->getTimeVisitante()->getNome();
            rp.golsCasa  = p->getGolsCasa();
            rp.golsVisit = p->getGolsVisitante();
            jogo.historico->pushBack(rp);

            if (p != minhaPartida) {
                if (!firstOutra) outrasJson += ",";
                firstOutra = false;
                std::ostringstream o;
                o << "{"
                  << "\"timeCasa\":"  << q(p->getTimeCasa()->getNome())      << ","
                  << "\"timeVisit\":" << q(p->getTimeVisitante()->getNome()) << ","
                  << "\"golsCasa\":"  << p->getGolsCasa()                    << ","
                  << "\"golsVisit\":" << p->getGolsVisitante()
                  << "}";
                outrasJson += o.str();
            }
        }
        outrasJson += "]";

        // Serializa minha partida + eventos
        std::string minhaJson = "null";
        if (minhaPartida) {
            std::string eventosJson = "[";
            bool firstEvt = true;
            minhaPartida->getLog().forEach([&](Evento* const& e) {
                if (!firstEvt) eventosJson += ",";
                firstEvt = false;
                std::string tnome  = e->getTime() ? e->getTime()->getNome()  : "";
                std::string tsigla = e->getTime() ? e->getTime()->getSigla() : "";
                std::ostringstream o;
                o << "{"
                  << "\"minuto\":"    << e->getMinuto()        << ","
                  << "\"tipo\":"      << q(e->getTipo())       << ","
                  << "\"time\":"      << q(tnome)              << ","
                  << "\"sigla\":"     << q(tsigla)             << ","
                  << "\"descricao\":" << q(e->getDescricao())
                  << "}";
                eventosJson += o.str();
            });
            eventosJson += "]";

            std::ostringstream o;
            o << "{"
              << "\"timeCasa\":"   << q(minhaPartida->getTimeCasa()->getNome())       << ","
              << "\"siglaCasa\":"  << q(minhaPartida->getTimeCasa()->getSigla())      << ","
              << "\"timeVisit\":"  << q(minhaPartida->getTimeVisitante()->getNome())  << ","
              << "\"siglaVisit\":" << q(minhaPartida->getTimeVisitante()->getSigla()) << ","
              << "\"golsCasa\":"   << minhaPartida->getGolsCasa()                     << ","
              << "\"golsVisit\":"  << minhaPartida->getGolsVisitante()                << ","
              << "\"eventos\":"    << eventosJson
              << "}";
            minhaJson = o.str();
        }

        // Libera memoria da rodada
        for (int i = 0; i < r->getNumPartidas(); i++) delete r->getPartida(i);
        delete r;

        std::ostringstream resp;
        resp << "{"
             << "\"rodada\":"         << jogo.rodadaAtual                              << ","
             << "\"encerrado\":"      << (jogo.calendario->empty() ? "true" : "false") << ","
             << "\"minhaPartida\":"   << minhaJson                                      << ","
             << "\"outrasPartidas\":" << outrasJson
             << "}";
        res.set_content(resp.str(), "application/json");
    });

    // -----------------------------------------------------------------------
    // POST /api/formacao   body: {"formacao": "4-3-3"}
    // -----------------------------------------------------------------------
    svr.Post("/api/formacao", [](const httplib::Request& req, httplib::Response& res) {
        cors(res);
        if (!jogo.iniciado) { res.status = 400; res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json"); return; }
        std::string f = parseStrKey(req.body, "formacao");
        if (f.empty()) { res.status = 400; res.set_content("{\"erro\":\"formacao invalida\"}", "application/json"); return; }
        times[jogo.meuTimeId - 1].setFormacao(f);
        res.set_content("{\"ok\":true,\"formacao\":" + q(f) + "}", "application/json");
    });

    // -----------------------------------------------------------------------
    // POST /api/melhorar   body: {"quantidade": 2}
    // -----------------------------------------------------------------------
    svr.Post("/api/melhorar", [](const httplib::Request& req, httplib::Response& res) {
        cors(res);
        if (!jogo.iniciado) { res.status = 400; res.set_content("{\"erro\":\"jogo nao iniciado\"}", "application/json"); return; }
        int qtd = parseIntKey(req.body, "quantidade");
        if (qtd <= 0) { res.status = 400; res.set_content("{\"erro\":\"quantidade invalida\"}", "application/json"); return; }
        Time& t = times[jogo.meuTimeId - 1];
        float total = qtd * 15.0f;
        if (total > t.getOrcamento()) {
            res.set_content("{\"ok\":false,\"erro\":\"orcamento insuficiente\"}", "application/json");
            return;
        }
        t.setForca(t.getForca() + qtd);
        t.setOrcamento(t.getOrcamento() - total);
        std::ostringstream o;
        o << std::fixed << std::setprecision(1);
        o << "{\"ok\":true,\"forca\":" << t.getForca() << ",\"orcamento\":" << t.getOrcamento() << "}";
        res.set_content(o.str(), "application/json");
    });

    // -----------------------------------------------------------------------
    // GET /api/historico
    // -----------------------------------------------------------------------
    svr.Get("/api/historico", [](const httplib::Request&, httplib::Response& res) {
        cors(res);
        if (!jogo.iniciado) { res.set_content("[]", "application/json"); return; }
        const std::string& nomeTime = times[jogo.meuTimeId - 1].getNome();
        std::string json = "[";
        bool first = true;
        jogo.historico->forEach([&](const ResPartida& rp) {
            if (rp.timeCasa != nomeTime && rp.timeVisit != nomeTime) return;
            if (!first) json += ",";
            first = false;
            std::ostringstream o;
            o << "{"
              << "\"rodada\":"    << rp.rodada       << ","
              << "\"timeCasa\":"  << q(rp.timeCasa)  << ","
              << "\"timeVisit\":" << q(rp.timeVisit) << ","
              << "\"golsCasa\":"  << rp.golsCasa      << ","
              << "\"golsVisit\":" << rp.golsVisit
              << "}";
            json += o.str();
        });
        json += "]";
        res.set_content(json, "application/json");
    });

    std::cout << "Servidor rodando em http://localhost:8080" << std::endl;
    std::cout << "Abra o frontend com: cd frontend && npm run dev" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}