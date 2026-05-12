#pragma once
#include "Time.h"
#include "Evento.h"
#include "../colecoes/LinkedList.h"

const int PARTIDAS_POR_RODADA = 10;

// A classe Partida representa um jogo entre dois times, com seus gols e eventos ocorridos e armazena os eventos da partida na Linked List

class Partida {
private:
    Time* timeCasa;
    Time* timeVisitante;
    int   golsCasa;
    int   golsVisitante;
    // Status da partida
    bool  simulada;

    LinkedList<Evento*> log; // todos os eventos ocorridos na partida

public:
    // Construtor
    Partida(Time* casa, Time* visitante)
        : timeCasa(casa), timeVisitante(visitante),
          golsCasa(0), golsVisitante(0), simulada(false) {}

    // Destrutor
    ~Partida() {
        log.forEach([](Evento* const& e) {
            delete e;
        });
    }

    // Getters
    Time* getTimeCasa()                    const { return timeCasa; }
    Time* getTimeVisitante()               const { return timeVisitante; }
    int   getGolsCasa()                    const { return golsCasa; }
    int   getGolsVisitante()               const { return golsVisitante; }
    bool  isSimulada()                     const { return simulada; }
    const LinkedList<Evento*>& getLog()    const { return log; }

    // Setters
    void setGolsCasa(int g)      { golsCasa = g; }
    void setGolsVisitante(int g) { golsVisitante = g; }
    void setSimulada(bool s)     { simulada = s; }
    void addGolCasa()            { golsCasa++; }
    void addGolVisitante()       { golsVisitante++; }
    void addEvento(Evento* e)    { log.pushBack(e); }
};

class Rodada {
private:
    int      numero;
    Partida* partidas[PARTIDAS_POR_RODADA];
    int      numPartidas;

public:
    Rodada(int num) : numero(num), numPartidas(0) {}

    // Getters
    int      getNumero()       const { return numero; }
    int      getNumPartidas()  const { return numPartidas; }
    Partida* getPartida(int i) const { return partidas[i]; }

    // Adiciona uma partida à rodada
    void addPartida(Partida* p) {
        if (numPartidas < PARTIDAS_POR_RODADA)
            partidas[numPartidas++] = p;
    }
};