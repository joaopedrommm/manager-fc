#pragma once
#include "Partida.h"

// Simula uma partida minuto a minuto (90 iteracoes)
// Preenche golsCasa, golsVisitante e marca simulada = true
void simularPartida(Partida& p);

// Exibe o resultado de uma partida
void exibirResultado(const Partida& p);