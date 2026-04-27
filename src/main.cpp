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
#include "structures/AVL.h"
#include "structures/LinkedList.h"

struct Resultado {
    int         rodada;
    std::string timeCasa;
    std::string timeVisit;
    int         golsCasa;
    int         golsVisit;
};

int compararTimes(Time* const& a, Time* const& b) {
    if (a->getPontos()    != b->getPontos())    return a->getPontos()    - b->getPontos();
    if (a->getVitorias()  != b->getVitorias())  return a->getVitorias()  - b->getVitorias();
    if (a->getSaldoGols() != b->getSaldoGols()) return a->getSaldoGols() - b->getSaldoGols();
    if (a->getGolsPro()   != b->getGolsPro())   return a->getGolsPro()   - b->getGolsPro();
    return b->getId() - a->getId();
}

void preencherElenco(Time& t) {
    int f = t.getForca();

    auto nota = [&](int bonus) -> int {
        int v = f + bonus + (rand() % 11) - 5;
        if (v < 40) v = 40;
        if (v > 99) v = 99;
        return v;
    };

    t.adicionarJogador(new Goleiro       ( 1, "Goleiro",      nota( 0), nota( 0), nota(-5)));
    t.adicionarJogador(new Defensor      ( 2, "Zagueiro 1",   nota(-2), nota(-3), nota(-5), nota(-5)));
    t.adicionarJogador(new Defensor      ( 3, "Zagueiro 2",   nota(-2), nota(-3), nota(-5), nota(-5)));
    t.adicionarJogador(new JogadorDeCampo( 4, "Lateral D", "LAT", nota(-3), nota( 2), nota(-2), nota(-5)));
    t.adicionarJogador(new JogadorDeCampo( 5, "Lateral E", "LAT", nota(-3), nota( 2), nota(-2), nota(-5)));
    t.adicionarJogador(new JogadorDeCampo( 6, "Vol 1",     "VOL", nota(-1), nota(-2), nota( 0), nota(-3), Agressividade::ALTA));
    t.adicionarJogador(new JogadorDeCampo( 7, "Vol 2",     "VOL", nota(-1), nota(-2), nota( 0), nota(-3), Agressividade::ALTA));
    t.adicionarJogador(new JogadorDeCampo( 8, "Meia",      "MEI", nota( 2), nota( 0), nota( 3), nota( 0)));
    t.adicionarJogador(new Atacante      ( 9, "Ala D",          nota( 0), nota( 4), nota(-1), nota( 2)));
    t.adicionarJogador(new Atacante      (10, "Ala E",          nota( 0), nota( 4), nota(-1), nota( 2)));
    t.adicionarJogador(new Atacante      (11, "Centroavante",   nota( 3), nota( 1), nota(-2), nota( 5)));
}

void exibirTabela(const AVL<Time*>& tabela) {
    std::cout << "\n=== Tabela de Classificacao ===" << std::endl;
    std::cout << std::left
              << std::setw(4)  << "Pos"
              << std::setw(22) << "Clube"
              << std::setw(5)  << "Pts"
              << std::setw(5)  << "V"
              << std::setw(5)  << "E"
              << std::setw(5)  << "D"
              << std::setw(5)  << "GP"
              << std::setw(5)  << "GC"
              << std::setw(5)  << "SG"
              << std::endl;
    std::cout << std::string(61, '-') << std::endl;

    int pos = 1;
    tabela.forEach([&](Time* const& t) {
        std::string marca = "   ";
        if      (pos <= 6)  marca = "LIB";
        else if (pos <= 12) marca = "SUL";
        else if (pos >= 17) marca = "REL";

        std::cout << std::left
                  << std::setw(4)  << pos
                  << std::setw(22) << t->getNome()
                  << std::setw(5)  << t->getPontos()
                  << std::setw(5)  << t->getVitorias()
                  << std::setw(5)  << t->getEmpates()
                  << std::setw(5)  << t->getDerrotas()
                  << std::setw(5)  << t->getGolsPro()
                  << std::setw(5)  << t->getGolsContra()
                  << std::setw(5)  << t->getSaldoGols()
                  << marca
                  << std::endl;
        pos++;
    });
    std::cout << "\nLIB=Libertadores | SUL=Sul-Americana | REL=Rebaixamento" << std::endl;
}

void exibirElenco(const Time& t) {
    std::cout << "\n=== Elenco: " << t.getNome()
              << " | Forca: " << t.getForca()
              << " | Orcamento: R$" << std::fixed << std::setprecision(1)
              << t.getOrcamento() << "M ===" << std::endl;
    std::cout << std::left
              << std::setw(4)  << "Nr"
              << std::setw(18) << "Nome"
              << std::setw(22) << "Tipo"
              << std::setw(5)  << "HAB"
              << std::endl;
    std::cout << std::string(49, '-') << std::endl;

    for (int i = 0; i < t.getNumJogadores(); i++) {
        const Jogador* j = t.getJogador(i);
        std::cout << std::left
                  << std::setw(4)  << (i + 1)
                  << std::setw(18) << j->getNome()
                  << std::setw(22) << j->getTipo()
                  << std::setw(5)  << j->getHabilidade()
                  << std::endl;
    }
    std::cout << "Formacao: " << t.getFormacao() << std::endl;
}

void menuEscolherFormacao(Time* meuTime) {
    const std::string formacoes[] = {
        "4-4-2", "4-3-3", "4-2-3-1", "3-5-2", "3-4-3",
        "4-2-4", "4-1-2-1-2", "5-4-1", "5-3-2", "5-2-3"
    };
    const int nForm = 10;

    std::cout << "\n=== Escolha a Formacao ===" << std::endl;
    for (int i = 0; i < nForm; i++)
        std::cout << "  " << (i + 1) << ". " << formacoes[i] << std::endl;
    std::cout << "Formacao atual: " << meuTime->getFormacao() << std::endl;
    std::cout << "Opcao (0=cancelar): ";

    int op;
    std::cin >> op;
    if (op >= 1 && op <= nForm) {
        meuTime->setFormacao(formacoes[op - 1]);
        std::cout << "Formacao alterada para " << meuTime->getFormacao() << "!" << std::endl;
    }
}

void menuMelhorarElenco(Time* meuTime) {
    const float CUSTO = 15.0f;
    std::cout << "\n=== Melhorar Elenco ===" << std::endl;
    std::cout << "Forca atual : " << meuTime->getForca() << std::endl;
    std::cout << "Orcamento   : R$" << std::fixed << std::setprecision(1)
              << meuTime->getOrcamento() << "M" << std::endl;
    std::cout << "Custo por +1 de forca: R$" << CUSTO << "M" << std::endl;

    if (meuTime->getOrcamento() < CUSTO) {
        std::cout << "Orcamento insuficiente!" << std::endl;
        return;
    }

    std::cout << "Quantas melhorias deseja comprar? (0=cancelar): ";
    int qtd;
    std::cin >> qtd;
    if (qtd <= 0) return;

    float total = qtd * CUSTO;
    if (total > meuTime->getOrcamento()) {
        std::cout << "Orcamento insuficiente para " << qtd << " melhorias." << std::endl;
        return;
    }

    meuTime->setForca(meuTime->getForca() + qtd);
    meuTime->setOrcamento(meuTime->getOrcamento() - total);
    std::cout << "Elenco melhorado! Nova forca: " << meuTime->getForca()
              << " | Orcamento restante: R$" << meuTime->getOrcamento() << "M" << std::endl;
}

// =============================================================================
// jogarRodada()
// =============================================================================
void jogarRodada(Queue<Rodada*>& calendario, AVL<Time*>& tabela,
                 Simulacao& sim, Time* meuTime,
                 LinkedList<Resultado>& historico, int& numRodada) {
    if (calendario.empty()) {
        std::cout << "Temporada encerrada!" << std::endl;
        return;
    }

    Rodada* r = calendario.dequeue();
    numRodada = r->getNumero();
    std::cout << "\n====== Rodada " << numRodada << "/38 ======" << std::endl;

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
        std::cout << "\n>>> Seu jogo: "
                  << minhaPartida->getTimeCasa()->getNome() << " vs "
                  << minhaPartida->getTimeVisitante()->getNome() << std::endl;
        std::cout << "Pressione Enter para simular...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

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
    std::cout << "\n--- Outros resultados ---" << std::endl;
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

void exibirHistorico(const LinkedList<Resultado>& historico,
                     const std::string& nomeTime) {
    std::cout << "\n=== Historico: " << nomeTime << " ===" << std::endl;

    int total = 0;
    historico.forEach([&](const Resultado& r) {
        if (r.timeCasa == nomeTime || r.timeVisit == nomeTime) {
            std::cout << "Rod." << std::setw(2) << r.rodada << ": "
                      << std::left << std::setw(22) << r.timeCasa
                      << r.golsCasa << " x " << r.golsVisit
                      << "  " << r.timeVisit << std::endl;
            total++;
        }
    });

    if (total == 0)
        std::cout << "Nenhuma partida disputada ainda." << std::endl;
}

// =============================================================================
// main()
// =============================================================================
int main() {
    srand((unsigned)time(nullptr));

    std::cout << "============================================" << std::endl;
    std::cout << "         BEM-VINDO AO MANAGER FC!          " << std::endl;
    std::cout << "  Simulador do Campeonato Brasileiro 2026  " << std::endl;
    std::cout << "============================================" << std::endl;

    for (int i = 0; i < NUM_TIMES; i++)
        preencherElenco(times[i]);

    std::cout << "\nEscolha seu clube:\n" << std::endl;
    for (int i = 0; i < NUM_TIMES; i++) {
        std::cout << std::setw(3) << (i + 1) << ". "
                  << std::left << std::setw(22) << times[i].getNome()
                  << " | Forca: " << times[i].getForca()
                  << " | Orcamento: R$" << times[i].getOrcamento() << "M"
                  << std::endl;
    }

    int escolha = 0;
    do {
        std::cout << "\nDigite o numero do clube (1-" << NUM_TIMES << "): ";
        std::cin >> escolha;
    } while (escolha < 1 || escolha > NUM_TIMES);

    Time* meuTime = &times[escolha - 1];
    std::cout << "\nVoce escolheu: " << meuTime->getNome()
              << " | Formacao: " << meuTime->getFormacao() << std::endl;

    Simulacao simulacao;

    AVL<Time*> tabela(compararTimes);
    for (int i = 0; i < NUM_TIMES; i++)
        tabela.insert(&times[i]);

    Queue<Rodada*> calendario = gerarCalendario();
    LinkedList<Resultado> historico;

    int rodadaAtual = 0;

    while (true) {
        std::cout << "\n=======================================" << std::endl;
        std::cout << " Rodada " << rodadaAtual << "/38"
                  << " | " << meuTime->getNome()
                  << " | " << meuTime->getPontos() << " pts" << std::endl;
        std::cout << "=======================================" << std::endl;
        std::cout << "  1. Jogar proxima rodada"               << std::endl;
        std::cout << "  2. Ver tabela de classificacao"        << std::endl;
        std::cout << "  3. Ver meu elenco"                     << std::endl;
        std::cout << "  4. Mudar formacao tatica"              << std::endl;
        std::cout << "  5. Melhorar elenco (gastar orcamento)" << std::endl;
        std::cout << "  6. Ver historico de partidas"          << std::endl;
        std::cout << "  0. Sair"                               << std::endl;
        std::cout << "Opcao: ";

        int op;
        std::cin >> op;

        if (op == 0) {
            std::cout << "Ate a proxima temporada!" << std::endl;
            break;
        }

        switch (op) {
            case 1:
                if (calendario.empty()) {
                    std::cout << "\n========= FIM DA TEMPORADA =========" << std::endl;
                    exibirTabela(tabela);
                    std::cout << "\n--- Desfecho ---" << std::endl;
                    int pos = 1;
                    tabela.forEach([&](Time* const& t) {
                        if (pos == 1)
                            std::cout << "CAMPEAO BRASILEIRO: " << t->getNome()
                                      << " (" << t->getPontos() << " pts)" << std::endl;
                        if (pos >= 17)
                            std::cout << "REBAIXADO: " << t->getNome() << std::endl;
                        pos++;
                    });
                } else {
                    jogarRodada(calendario, tabela, simulacao, meuTime, historico, rodadaAtual);
                }
                break;
            case 2: exibirTabela(tabela);                           break;
            case 3: exibirElenco(*meuTime);                         break;
            case 4: menuEscolherFormacao(meuTime);                  break;
            case 5: menuMelhorarElenco(meuTime);                    break;
            case 6: exibirHistorico(historico, meuTime->getNome()); break;
            default: std::cout << "Opcao invalida." << std::endl;
        }
    }

    return 0;
}