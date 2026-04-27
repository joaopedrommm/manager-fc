#pragma once
#include "Partida.h"
#include "ContextoPartida.h"

class Simulacao {
private:
    float calcularProbGol(const ContextoPartida& ctx,
                          int ti, bool ehMandante) const;
public:
    void simularPartida(Partida& partida);
    void exibirResultado(const Partida& partida) const;
    void exibirEventos(const Partida& partida) const;
};
