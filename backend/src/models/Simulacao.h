#pragma once
#include "Partida.h"

class Simulacao {
private:
    float forcaEfetiva(const Time* time, const Time* adversario);
    float probGolPorMinuto(const Time* atacante, const Time* defensor);

public:
    void simularPartida(Partida& p);
    void exibirResultado(const Partida& p);
};