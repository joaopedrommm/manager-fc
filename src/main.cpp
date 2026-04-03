#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "models/Campeonato.h"
#include "models/Calendario.h"
#include "models/Simulacao.h"
#include "structures/AVL.h"

// -----------------------------------------------------------------------
// Comparador da tabela do Brasileirao:
// 1o criterio: pontos
// 2o criterio: vitorias
// 3o criterio: saldo de gols
// 4o criterio: gols pro
// Retorna > 0 se a é melhor que b (fica acima na tabela)
// -----------------------------------------------------------------------
int compararTimes(Time* const& a, Time* const& b) {
    if (a->pontos    != b->pontos)    return a->pontos    - b->pontos;
    if (a->vitorias  != b->vitorias)  return a->vitorias  - b->vitorias;
    if (a->saldoGols() != b->saldoGols()) return a->saldoGols() - b->saldoGols();
    return a->golsPro - b->golsPro;
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
        // Marcadores visuais
        std::string marca = "   ";
        if (pos <= 6)       marca = "LIB";  // Libertadores
        else if (pos <= 12) marca = "SUL";  // Sul-Americana
        else if (pos >= 17) marca = "REL";  // Rebaixamento

        std::cout << std::left
                  << std::setw(4)  << pos
                  << std::setw(22) << t->nome
                  << std::setw(5)  << t->pontos
                  << std::setw(5)  << t->vitorias
                  << std::setw(5)  << t->empates
                  << std::setw(5)  << t->derrotas
                  << std::setw(5)  << t->golsPro
                  << std::setw(5)  << t->golsContra
                  << std::setw(5)  << t->saldoGols()
                  << marca
                  << std::endl;
        pos++;
    });

    std::cout << "\nLIB = Libertadores | SUL = Sul-Americana | REL = Rebaixamento" << std::endl;
}

int main() {
    srand((unsigned)time(nullptr));

    // Monta a AVL com o comparador do Brasileirao
    AVL<Time*> tabela(compararTimes);
    for (int i = 0; i < NUM_TIMES; i++)
        tabela.insert(&times[i]);

    // Gera e simula o calendario completo
    Queue<Rodada*> calendario = gerarCalendario();
    std::cout << "Simulando temporada..." << std::endl;

    int totalGols = 0, totalPartidas = 0;

    while (!calendario.empty()) {
        Rodada* r = calendario.dequeue();
        for (int i = 0; i < r->numPartidas; i++) {
            // Remove os times da AVL antes de atualizar os stats
            tabela.remove(r->partidas[i]->timeCasa);
            tabela.remove(r->partidas[i]->timeVisitante);

            simularPartida(*r->partidas[i]);

            totalGols += r->partidas[i]->golsCasa + r->partidas[i]->golsVisitante;
            totalPartidas++;

            // Reinsere com stats atualizados
            tabela.insert(r->partidas[i]->timeCasa);
            tabela.insert(r->partidas[i]->timeVisitante);

            delete r->partidas[i];
        }
        delete r;
    }

    // Exibe tabela final
    exibirTabela(tabela);

    float media = (float)totalGols / totalPartidas;
    std::cout << "\nTotal de gols: " << totalGols
              << " | Media: " << std::fixed << std::setprecision(2) << media
              << " gols/partida" << std::endl;

    return 0;
}