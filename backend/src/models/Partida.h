#pragma once
#include "Time.h"

const int PARTIDAS_POR_RODADA = 10;

class Partida {
private:
    Time* timeCasa;
    Time* timeVisitante;
    int golsCasa;
    int golsVisitante;
    bool simulada;

public:
    Partida(Time* casa, Time* visitante)
        : timeCasa(casa), timeVisitante(visitante),
          golsCasa(0), golsVisitante(0), simulada(false) {}

    // Getters
    Time* getTimeCasa()        const { return timeCasa; }
    Time* getTimeVisitante()   const { return timeVisitante; }
    int getGolsCasa()          const { return golsCasa; }
    int getGolsVisitante()     const { return golsVisitante; }
    bool isSimulada()          const { return simulada; }

    // Setters
    void setGolsCasa(int g)        { golsCasa = g; }
    void setGolsVisitante(int g)   { golsVisitante = g; }
    void setSimulada(bool s)       { simulada = s; }
    void addGolCasa()              { golsCasa++; }
    void addGolVisitante()         { golsVisitante++; }
};

class Rodada {
private:
    int numero;
    Partida* partidas[PARTIDAS_POR_RODADA];
    int numPartidas;

public:
    Rodada(int num) : numero(num), numPartidas(0) {}

    // Getters
    int getNumero()      const { return numero; }
    int getNumPartidas() const { return numPartidas; }
    Partida* getPartida(int i) const { return partidas[i]; }

    void addPartida(Partida* p) {
        if (numPartidas < PARTIDAS_POR_RODADA)
            partidas[numPartidas++] = p;
    }
};
