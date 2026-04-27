#pragma once
#include "Time.h"
#include "Evento.h"
#include "../structures/LinkedList.h"

const int PARTIDAS_POR_RODADA = 10;

// =============================================================================
// Partida.h  -  Representa uma partida entre dois times.
//
// NOVIDADE: alem do placar, a Partida agora guarda uma LinkedList<Evento*>
// com todos os lances que ocorreram durante a simulacao (gols, cartoes,
// intervalo). O polimorfismo de Evento permite guardar qualquer tipo de
// lance no mesmo container sem precisar saber o tipo concreto.
//
// GERENCIAMENTO DE MEMORIA:
//   A Partida e a "dona" dos objetos Evento. O destrutor percorre a lista
//   e deleta cada Evento* antes de a LinkedList limpar seus proprios nos.
// =============================================================================

class Partida {
private:
    Time* timeCasa;
    Time* timeVisitante;
    int   golsCasa;
    int   golsVisitante;
    bool  simulada;

    // Lista encadeada de eventos (Evento* pode ser qualquer subtipo)
    LinkedList<Evento*> eventos;

public:
    Partida(Time* casa, Time* visitante)
        : timeCasa(casa), timeVisitante(visitante),
          golsCasa(0), golsVisitante(0), simulada(false) {}

    // Destrutor: deleta cada Evento* antes que a LinkedList limpe seus nos.
    ~Partida() {
        eventos.forEach([](Evento* const& e) { delete e; });
    }

    // Getters de placar e status
    Time* getTimeCasa()      const { return timeCasa; }
    Time* getTimeVisitante() const { return timeVisitante; }
    int   getGolsCasa()      const { return golsCasa; }
    int   getGolsVisitante() const { return golsVisitante; }
    bool  isSimulada()       const { return simulada; }

    // Setters de placar
    void setGolsCasa(int g)      { golsCasa = g; }
    void setGolsVisitante(int g) { golsVisitante = g; }
    void setSimulada(bool s)     { simulada = s; }
    void addGolCasa()            { golsCasa++; }
    void addGolVisitante()       { golsVisitante++; }

    // Eventos: adiciona um lance ao log da partida.
    // Recebe Evento* - pode ser EventoGol*, EventoCartaoVermelho*, etc.
    void addEvento(Evento* e)                     { eventos.pushBack(e); }
    const LinkedList<Evento*>& getEventos() const { return eventos; }
};

class Rodada {
private:
    int numero;
    Partida* partidas[PARTIDAS_POR_RODADA];
    int numPartidas;

public:
    Rodada(int num) : numero(num), numPartidas(0) {}

    int getNumero()      const { return numero; }
    int getNumPartidas() const { return numPartidas; }
    Partida* getPartida(int i) const { return partidas[i]; }

    void addPartida(Partida* p) {
        if (numPartidas < PARTIDAS_POR_RODADA)
            partidas[numPartidas++] = p;
    }
};
