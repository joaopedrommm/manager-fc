#pragma once
#include "Partida.h"



class Simulacao {
public:
    // Gera todos os eventos e atualiza o placar
    void simularPartida(Partida& p);
    // Mostra o resultado das outras partidas da rodada
    void exibirResultado(const Partida& p);
    // Exibe o log completo minuto a minuto
    void exibirPartidaAoVivo(const Partida& p);
};