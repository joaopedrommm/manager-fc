#pragma once
#include "Time.h"

const int NUM_TIMES = 20;

// Declaracao do array de times (definido em Campeonato.cpp)
extern Time times[NUM_TIMES];

// Retorna ponteiro para o time pelo id (retorna nullptr se nao encontrado)
Time* buscarTimePorId(int id);

// Retorna ponteiro para o time pelo nome
Time* buscarTimePorNome(const std::string& nome);
