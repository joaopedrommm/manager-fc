#include "Calendario.h"
#include <iostream>
#include <iomanip>

// -----------------------------------------------------------------------
// Algoritmo round-robin para 20 times (19 rodadas de ida + 19 de volta)
//
// Ideia: fixa o time[0] e rotaciona os outros 19 a cada rodada.
// Em cada rodada forma-se 10 pares: (0 vs 19), (1 vs 18), ..., (9 vs 10)
// Na volta, casa e visitante sao invertidos.
// -----------------------------------------------------------------------
Queue<Rodada*> gerarCalendario() {
    Queue<Rodada*> fila;

    // Copia os indices dos times para rotacionar
    int idx[NUM_TIMES];
    for (int i = 0; i < NUM_TIMES; i++) idx[i] = i;

    // 19 rodadas de ida
    for (int r = 0; r < NUM_TIMES - 1; r++) {
        Rodada* rodada = new Rodada(r + 1);

        // Forma os 10 pares desta rodada
        for (int i = 0; i < NUM_TIMES / 2; i++) {
            int a = idx[i];
            int b = idx[NUM_TIMES - 1 - i];
            Partida* p = new Partida(&times[a], &times[b]);
            rodada->addPartida(p);
        }

        fila.enqueue(rodada);

        // Rotaciona: fixa idx[0], move os demais uma posicao para a direita
        int ultimo = idx[NUM_TIMES - 1];
        for (int i = NUM_TIMES - 1; i > 1; i--) idx[i] = idx[i - 1];
        idx[1] = ultimo;
    }

    // 19 rodadas de volta (invertendo casa/visitante)
    for (int r = 0; r < NUM_TIMES - 1; r++) {
        // Recria a rodada de ida equivalente para inverter
        int idx2[NUM_TIMES];
        for (int i = 0; i < NUM_TIMES; i++) idx2[i] = i;
        for (int rot = 0; rot < r; rot++) {
            int ultimo = idx2[NUM_TIMES - 1];
            for (int i = NUM_TIMES - 1; i > 1; i--) idx2[i] = idx2[i - 1];
            idx2[1] = ultimo;
        }

        Rodada* rodada = new Rodada(NUM_TIMES + r);

        for (int i = 0; i < NUM_TIMES / 2; i++) {
            int a = idx2[i];
            int b = idx2[NUM_TIMES - 1 - i];
            // Volta: visitante vira casa e vice-versa
            Partida* p = new Partida(&times[b], &times[a]);
            rodada->addPartida(p);
        }

        fila.enqueue(rodada);
    }

    return fila;
}

void exibirRodada(const Rodada* r) {
    std::cout << "\n=== Rodada " << r->numero << " ===" << std::endl;
    for (int i = 0; i < r->numPartidas; i++) {
        const Partida* p = r->partidas[i];
        std::cout << std::left
                  << std::setw(22) << p->timeCasa->nome
                  << " x  "
                  << p->timeVisitante->nome
                  << std::endl;
    }
}
