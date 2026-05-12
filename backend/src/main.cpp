// =============================================================================
// main.cpp  —  Ponto de entrada do Manager FC
// =============================================================================

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

#include "models/Campeonato.h"
#include "models/Calendario.h"
#include "models/Simulacao.h"
#include "models/Jogador.h"
#include "models/Goleiro.h"
#include "models/JogadorDeCampo.h"
#include "colecoes/AVL.h"
#include "colecoes/LinkedList.h"
#include "data/elencos.h"
using namespace std;

class Resultado {
public:
    int         rodada;
    string timeCasa;
    string timeVisit;
    int         golsCasa;
    int         golsVisit;
};

// Define os critérios de desempate entre duas equipas
int compararTimes(Time* const& a, Time* const& b) {
    if (a->getPontos()    != b->getPontos())    return a->getPontos()    - b->getPontos();
    if (a->getVitorias()  != b->getVitorias())  return a->getVitorias()  - b->getVitorias();
    if (a->getSaldoGols() != b->getSaldoGols()) return a->getSaldoGols() - b->getSaldoGols();
    if (a->getGolsPro()   != b->getGolsPro())   return a->getGolsPro()   - b->getGolsPro();
    return b->getId() - a->getId();
}

// Substitui jogadores aleatorios pelos jogadores reais de cada time
void preencherElencoReal(Time& t) {
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

// Mostra a tabela de classificação
void exibirTabela(const AVL<Time*>& tabela) {
    cout << "\n=== Tabela de Classificacao ===" << endl;
    cout << left
              << setw(4)  << "Pos"
              << setw(22) << "Clube"
              << setw(5)  << "Pts"
              << setw(5)  << "V"
              << setw(5)  << "E"
              << setw(5)  << "D"
              << setw(5)  << "GP"
              << setw(5)  << "GC"
              << setw(5)  << "SG"
              << endl;
    cout << string(61, '-') << endl;

    int pos = 1;
    tabela.forEach([&](Time* const& t) {
        string marca = "   ";
        if      (pos <= 6)  marca = "LIB";
        else if (pos <= 12) marca = "SUL";
        else if (pos >= 17) marca = "REL";

        cout << left
                  << setw(4)  << pos
                  << setw(22) << t->getNome()
                  << setw(5)  << t->getPontos()
                  << setw(5)  << t->getVitorias()
                  << setw(5)  << t->getEmpates()
                  << setw(5)  << t->getDerrotas()
                  << setw(5)  << t->getGolsPro()
                  << setw(5)  << t->getGolsContra()
                  << setw(5)  << t->getSaldoGols()
                  << marca
                  << endl;
        pos++;
    });
    cout << "\nLIB=Libertadores | SUL=Sul-Americana | REL=Rebaixamento" << endl;
}

// Mostra o elenco do time, com detalhes de cada jogador
void exibirElenco(const Time& t) {
    cout << "\n=== Elenco: " << t.getNome()
              << " | Forca: " << t.getForca()
              << " | Orcamento: R$" << fixed << setprecision(1)
              << t.getOrcamento() << "M ===" << endl;
    cout << left
              << setw(4)  << "Nr"
              << setw(18) << "Nome"
              << setw(22) << "Tipo"
              << setw(5)  << "HAB"
              << endl;
    cout << string(49, '-') << endl;

    for (int i = 0; i < t.getNumJogadores(); i++) {
        const Jogador* j = t.getJogador(i);
        cout << left
                  << setw(4)  << (i + 1)
                  << setw(18) << j->getNome()
                  << setw(22) << j->getTipo()
                  << setw(5)  << j->getHabilidade()
                  << endl;
    }
    cout << "Formacao: " << t.getFormacao() << endl;
}

// Define a formação do time
void menuEscolherFormacao(Time* meuTime) {
    const string formacoes[] = {
        "4-4-2", "4-3-3", "4-2-3-1", "3-5-2", "3-4-3",
        "4-2-4", "4-1-2-1-2", "5-4-1", "5-3-2", "5-2-3"
    };
    const int nForm = 10;

    cout << "\n=== Escolha a Formacao ===" << endl;
    for (int i = 0; i < nForm; i++)
        cout << "  " << (i + 1) << ". " << formacoes[i] << endl;
    cout << "Formacao atual: " << meuTime->getFormacao() << endl;
    cout << "Opcao (0=cancelar): ";

    int op;
    cin >> op;
    if (op >= 1 && op <= nForm) {
        meuTime->setFormacao(formacoes[op - 1]);
        cout << "Formacao alterada para " << meuTime->getFormacao() << "!" << endl;
    }
}

// Função para melhorar a força do elenco
void menuMelhorarElenco(Time* meuTime) {
    const float CUSTO = 15.0f;
    cout << "\n=== Melhorar Elenco ===" << endl;
    cout << "Forca atual : " << meuTime->getForca() << endl;
    cout << "Orcamento   : R$" << fixed << setprecision(1)
              << meuTime->getOrcamento() << "M" << endl;
    cout << "Custo por +1 de forca: R$" << CUSTO << "M" << endl;

    if (meuTime->getOrcamento() < CUSTO) {
        cout << "Orcamento insuficiente!" << endl;
        return;
    }

    cout << "Quantas melhorias deseja comprar? (0=cancelar): ";
    int qtd;
    cin >> qtd;
    if (qtd <= 0) return;

    float total = qtd * CUSTO;
    if (total > meuTime->getOrcamento()) {
        cout << "Orcamento insuficiente para " << qtd << " melhorias." << endl;
        return;
    }

    meuTime->setForca(meuTime->getForca() + qtd);
    meuTime->setOrcamento(meuTime->getOrcamento() - total);
    cout << "Elenco melhorado! Nova forca: " << meuTime->getForca()
              << " | Orcamento restante: R$" << meuTime->getOrcamento() << "M" << endl;
}

// Entra na simulação da rodada
void jogarRodada(Queue<Rodada*>& calendario, AVL<Time*>& tabela,
                 Simulacao& sim, Time* meuTime,
                 LinkedList<Resultado>& historico, int& numRodada) {
    if (calendario.empty()) {
        cout << "Temporada encerrada!" << endl;
        return;
    }

    Rodada* r = calendario.dequeue();
    numRodada = r->getNumero();
    cout << "\n====== Rodada " << numRodada << "/38 ======" << endl;

    // Identifica a partida do jogador
    Partida* minhaPartida = nullptr;
    for (int i = 0; i < r->getNumPartidas(); i++) {
        Partida* p = r->getPartida(i);
        if (p->getTimeCasa() == meuTime || p->getTimeVisitante() == meuTime) {
            minhaPartida = p;
            break;
        }
    }

    // --- PASSO 1: simula e exibe o jogo do jogador ao vivo ---
    if (minhaPartida) {
        cout << "\n>>> Seu jogo: "
                  << minhaPartida->getTimeCasa()->getNome() << " vs "
                  << minhaPartida->getTimeVisitante()->getNome() << endl;
        cout << "Pressione Enter para simular...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        tabela.remove(minhaPartida->getTimeCasa());
        tabela.remove(minhaPartida->getTimeVisitante());
        sim.simularPartida(*minhaPartida);
        tabela.insert(minhaPartida->getTimeCasa());
        tabela.insert(minhaPartida->getTimeVisitante());

        sim.exibirPartidaAoVivo(*minhaPartida);

        Resultado res;
        res.rodada    = numRodada;
        res.timeCasa  = minhaPartida->getTimeCasa()->getNome();
        res.timeVisit = minhaPartida->getTimeVisitante()->getNome();
        res.golsCasa  = minhaPartida->getGolsCasa();
        res.golsVisit = minhaPartida->getGolsVisitante();
        historico.pushBack(res);
    }

    // --- PASSO 2: simula e mostra os outros jogos compactamente ---
    cout << "\n--- Outros resultados ---" << endl;
    for (int i = 0; i < r->getNumPartidas(); i++) {
        Partida* p = r->getPartida(i);
        if (p == minhaPartida) continue;

        tabela.remove(p->getTimeCasa());
        tabela.remove(p->getTimeVisitante());
        sim.simularPartida(*p);
        tabela.insert(p->getTimeCasa());
        tabela.insert(p->getTimeVisitante());

        sim.exibirResultado(*p);

        Resultado res;
        res.rodada    = numRodada;
        res.timeCasa  = p->getTimeCasa()->getNome();
        res.timeVisit = p->getTimeVisitante()->getNome();
        res.golsCasa  = p->getGolsCasa();
        res.golsVisit = p->getGolsVisitante();
        historico.pushBack(res);

        delete p;
    }

    if (minhaPartida) delete minhaPartida;
    delete r;
}

// Mostra o histórico de partidas do time
void exibirHistorico(const LinkedList<Resultado>& historico,
                     const string& nomeTime) {
    cout << "\n=== Historico: " << nomeTime << " ===" << endl;

    int total = 0;
    historico.forEach([&](const Resultado& r) {
        if (r.timeCasa == nomeTime || r.timeVisit == nomeTime) {
            cout << "Rod." << setw(2) << r.rodada << ": "
                      << left << setw(22) << r.timeCasa
                      << r.golsCasa << " x " << r.golsVisit
                      << "  " << r.timeVisit << endl;
            total++;
        }
    });

    if (total == 0)
        cout << "Nenhuma partida disputada ainda." << endl;
}


int main() {
    srand((unsigned)time(nullptr));

    cout << "============================================" << endl;
    cout << "         BEM-VINDO AO MANAGER FC!          " << endl;
    cout << "  Simulador do Campeonato Brasileiro 2026  " << endl;
    cout << "============================================" << endl;

    // Prepara os times com seus elencos reais
    for (int i = 0; i < NUM_TIMES; i++)
        preencherElencoReal(times[i]);

    // Menu de escolha do time
    cout << "\nEscolha seu clube:\n" << endl;
    for (int i = 0; i < NUM_TIMES; i++) {
        cout << setw(3) << (i + 1) << ". "
                  << left << setw(22) << times[i].getNome()
                  << " | Forca: " << times[i].getForca()
                  << " | Orcamento: R$" << times[i].getOrcamento() << "M"
                  << endl;
    }

    int escolha = 0;
    do {
        cout << "\nDigite o numero do clube (1-" << NUM_TIMES << "): ";
        cin >> escolha;
    } while (escolha < 1 || escolha > NUM_TIMES);

    // Ponteiro para o time escolhido
    Time* meuTime = &times[escolha - 1];
    cout << "\nVoce escolheu: " << meuTime->getNome()
              << " | Formacao: " << meuTime->getFormacao() << endl;

    Simulacao simulacao;

    AVL<Time*> tabela(compararTimes);
    for (int i = 0; i < NUM_TIMES; i++)
        tabela.insert(&times[i]);

    Queue<Rodada*> calendario = gerarCalendario();
    LinkedList<Resultado> historico;

    int rodadaAtual = 0;

    // Menu principal do jogo
    while (true) {
        cout << "\n=======================================" << endl;
        cout << " Rodada " << rodadaAtual << "/38"
                  << " | " << meuTime->getNome()
                  << " | " << meuTime->getPontos() << " pts" << endl;
        cout << "=======================================" << endl;
        cout << "  1. Jogar proxima rodada"               << endl;
        cout << "  2. Ver tabela de classificacao"        << endl;
        cout << "  3. Ver meu elenco"                     << endl;
        cout << "  4. Mudar formacao tatica"              << endl;
        cout << "  5. Melhorar elenco (gastar orcamento)" << endl;
        cout << "  6. Ver historico de partidas"          << endl;
        cout << "  0. Sair"                               << endl;
        cout << "Opcao: ";

        int op;
        cin >> op;

        // Saiu do jogo
        if (op == 0) {
            cout << "Ate a proxima temporada!" << endl;
            break;
        }

        switch (op) {
            // Caso para o fim da temporada
            case 1:
                if (calendario.empty()) {
                    cout << "\n========= FIM DA TEMPORADA =========" << endl;
                    exibirTabela(tabela);
                    cout << "\n--- Desfecho ---" << endl;
                    int pos = 1;
                    tabela.forEach([&](Time* const& t) {
                        if (pos == 1)
                            cout << "CAMPEAO BRASILEIRO: " << t->getNome()
                                      << " (" << t->getPontos() << " pts)" << endl;
                        if (pos >= 17)
                            cout << "REBAIXADO: " << t->getNome() << endl;
                        pos++;
                    });
                } else {
                    // Jogar Rodada como padrão
                    jogarRodada(calendario, tabela, simulacao, meuTime, historico, rodadaAtual);
                }
                break;
            case 2: exibirTabela(tabela);                           break;
            case 3: exibirElenco(*meuTime);                         break;
            case 4: menuEscolherFormacao(meuTime);                  break;
            case 5: menuMelhorarElenco(meuTime);                    break;
            case 6: exibirHistorico(historico, meuTime->getNome()); break;
            default: cout << "Opcao invalida." << endl;
        }
    }

    return 0;
}