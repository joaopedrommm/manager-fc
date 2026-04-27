#pragma once
#include "Partida.h"

// =============================================================================
// Simulacao.h  —  Declaração da classe de simulação
//
// simularPartida()       → gera todos os eventos e atualiza o placar
// exibirResultado()      → linha compacta (usada nas outras partidas da rodada)
// exibirPartidaAoVivo()  → exibe o log completo minuto a minuto (jogo do jogador)
// =============================================================================

class Simulacao {
public:
    void simularPartida(Partida& p);
    void exibirResultado(const Partida& p);
    void exibirPartidaAoVivo(const Partida& p);
};