#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "models/Campeonato.h"
#include "models/Calendario.h"
#include "models/Simulacao.h"
#include "structures/AVL.h"

int compararTimes(Time* const& a, Time* const& b) {
    if (a->getPontos()    != b->getPontos())    return a->getPontos()    - b->getPontos();
    if (a->getVitorias()  != b->getVitorias())  return a->getVitorias()  - b->getVitorias();
    if (a->getSaldoGols() != b->getSaldoGols()) return a->getSaldoGols() - b->getSaldoGols();
    return a->getGolsPro() - b->getGolsPro();
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
        if (pos <= 6)       marca = "LIB";
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
    std::cout << "\nLIB = Libertadores | SUL = Sul-Americana | REL = Rebaixamento" << std::endl;
}

int main() {
    srand((unsigned)time(nullptr));

    AVL<Time*> tabela(compararTimes);
    for (int i = 0; i < NUM_TIMES; i++)
        tabela.insert(&times[i]);

    Queue<Rodada*> calendario = gerarCalendario();
    std::cout << "Simulando temporada..." << std::endl;

    int totalGols = 0, totalPartidas = 0;

    while (!calendario.empty()) {
        Rodada* r = calendario.dequeue();
        for (int i = 0; i < r->getNumPartidas(); i++) {
            Partida* p = r->getPartida(i);
            tabela.remove(p->getTimeCasa());
            tabela.remove(p->getTimeVisitante());

            simularPartida(*p);
            totalGols += p->getGolsCasa() + p->getGolsVisitante();
            totalPartidas++;

            tabela.insert(p->getTimeCasa());
            tabela.insert(p->getTimeVisitante());
            delete p;
        }
        delete r;
    }

    exibirTabela(tabela);
    float media = (float)totalGols / totalPartidas;
    std::cout << "\nTotal de gols: " << totalGols
              << " | Media: " << std::fixed << std::setprecision(2) << media
              << " gols/partida" << std::endl;

    return 0;
}