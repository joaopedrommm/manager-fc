#pragma once
#include "Partida.h"
#include "Campeonato.h"
#include "../structures/Queue.h"

const int NUM_RODADAS = 38;

// Gera o calendario completo de 38 rodadas (algoritmo round-robin)
// e devolve uma fila pronta para ser consumida rodada a rodada
Queue<Rodada*> gerarCalendario();

// Exibe no terminal as partidas de uma rodada
void exibirRodada(const Rodada* r);
