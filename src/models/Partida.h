#pragma once
#include "Time.h"
#include "Evento.h"
#include "../structures/LinkedList.h"

const int PARTIDAS_POR_RODADA = 10;

// =============================================================================
// Partida.h  —  Representa uma partida entre dois times
//
// NOVIDADE: LinkedList<Evento*> log
//   Durante a simulação, cada gol/cartão/intervalo vira um objeto Evento
//   e é inserido nessa lista. O main.cpp pode depois exibir o log completo.
//
// GERENCIAMENTO DE MEMÓRIA:
//   O destrutor percorre o log e deleta cada Evento* (alocado com 'new'
//   em Simulacao.cpp). A LinkedList só deleta os nós — nós deletamos os dados.
// =============================================================================

class Partida {
private:
    Time* timeCasa;
    Time* timeVisitante;
    int   golsCasa;
    int   golsVisitante;
    bool  simulada;

    LinkedList<Evento*> log; // todos os eventos ocorridos na partida

public:
    Partida(Time* casa, Time* visitante)
        : timeCasa(casa), timeVisitante(visitante),
          golsCasa(0), golsVisitante(0), simulada(false) {}

    // Destrutor: deleta cada objeto Evento antes de a lista liberar seus nós
    ~Partida() {
        log.forEach([](Evento* const& e) {
            delete e;
        });
    }

    // --- Getters ---
    Time* getTimeCasa()                    const { return timeCasa; }
    Time* getTimeVisitante()               const { return timeVisitante; }
    int   getGolsCasa()                    const { return golsCasa; }
    int   getGolsVisitante()               const { return golsVisitante; }
    bool  isSimulada()                     const { return simulada; }
    const LinkedList<Evento*>& getLog()    const { return log; }

    // --- Setters ---
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

    int      getNumero()       const { return numero; }
    int      getNumPartidas()  const { return numPartidas; }
    Partida* getPartida(int i) const { return partidas[i]; }

    void addPartida(Partida* p) {
        if (numPartidas < PARTIDAS_POR_RODADA)
            partidas[numPartidas++] = p;
    }
};