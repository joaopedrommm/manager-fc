#pragma once
#include "Time.h"

struct Partida {
    Time* timeCasa;
    Time* timeVisitante;
    int golsCasa;
    int golsVisitante;
    bool simulada;

    Partida(Time* casa, Time* visitante)
        : timeCasa(casa), timeVisitante(visitante),
          golsCasa(0), golsVisitante(0), simulada(false) {}
};

// Uma rodada tem 10 partidas (20 times / 2)
const int PARTIDAS_POR_RODADA = 10;

struct Rodada {
    int numero;
    Partida* partidas[PARTIDAS_POR_RODADA];
    int numPartidas;

    Rodada(int num) : numero(num), numPartidas(0) {}

    void addPartida(Partida* p) {
        if (numPartidas < PARTIDAS_POR_RODADA)
            partidas[numPartidas++] = p;
    }
};
