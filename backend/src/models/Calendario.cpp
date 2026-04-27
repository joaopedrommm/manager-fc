#include "Calendario.h"
#include <iostream>
#include <iomanip>

Queue<Rodada*> gerarCalendario() {
    Queue<Rodada*> fila;
    int idx[NUM_TIMES];
    for (int i = 0; i < NUM_TIMES; i++) idx[i] = i;

    for (int r = 0; r < NUM_TIMES - 1; r++) {
        Rodada* rodada = new Rodada(r + 1);
        for (int i = 0; i < NUM_TIMES / 2; i++) {
            int a = idx[i], b = idx[NUM_TIMES - 1 - i];
            rodada->addPartida(new Partida(&times[a], &times[b]));
        }
        fila.enqueue(rodada);
        int ultimo = idx[NUM_TIMES - 1];
        for (int i = NUM_TIMES - 1; i > 1; i--) idx[i] = idx[i - 1];
        idx[1] = ultimo;
    }

    for (int r = 0; r < NUM_TIMES - 1; r++) {
        int idx2[NUM_TIMES];
        for (int i = 0; i < NUM_TIMES; i++) idx2[i] = i;
        for (int rot = 0; rot < r; rot++) {
            int ultimo = idx2[NUM_TIMES - 1];
            for (int i = NUM_TIMES - 1; i > 1; i--) idx2[i] = idx2[i - 1];
            idx2[1] = ultimo;
        }
        Rodada* rodada = new Rodada(NUM_TIMES + r);
        for (int i = 0; i < NUM_TIMES / 2; i++) {
            int a = idx2[i], b = idx2[NUM_TIMES - 1 - i];
            rodada->addPartida(new Partida(&times[b], &times[a]));
        }
        fila.enqueue(rodada);
    }

    return fila;
}

void exibirRodada(const Rodada* r) {
    std::cout << "\n=== Rodada " << r->getNumero() << " ===" << std::endl;
    for (int i = 0; i < r->getNumPartidas(); i++) {
        const Partida* p = r->getPartida(i);
        std::cout << std::left
                  << std::setw(22) << p->getTimeCasa()->getNome()
                  << " x  "
                  << p->getTimeVisitante()->getNome()
                  << std::endl;
    }
}