#pragma once
#include <string>

namespace Formacoes {

    const int NUM_FORMACOES = 10;

    const std::string NOMES[NUM_FORMACOES] = {
        "3-4-3", "3-5-2", "4-3-3", "4-2-3-1", "4-4-2",
        "4-2-4", "4-1-2-1-2", "5-4-1", "5-3-2", "5-2-3"
    };

    // modificador[i][j] = bonus percentual de i contra j
    // Range: +8 a +11 (vantagem) / -8 a -11 (desvantagem)
    const int MODIFICADOR[NUM_FORMACOES][NUM_FORMACOES] = {
    //        3-4-3  3-5-2  4-3-3  4-2-3-1  4-4-2  4-2-4  4-1-2-1-2  5-4-1  5-3-2  5-2-3
    /* 3-4-3     */ {  0,    -9,    -8,     0,     9,   -10,    -9,    10,    11,     0 },
    /* 3-5-2     */ {  9,     0,    10,    -9,    11,     0,    -8,    -9,     0,   -10 },
    /* 4-3-3     */ {  8,   -10,     0,    -9,    10,     9,    11,    -8,     0,     0 },
    /* 4-2-3-1   */ {  0,     9,     9,     0,   -10,     0,    -9,   -10,    11,    -8 },
    /* 4-4-2     */ { -9,   -11,   -10,    10,     0,     9,     8,     0,    -9,    11 },
    /* 4-2-4     */ { 10,     0,    -9,     0,    -9,     0,    -8,   -11,     8,    10 },
    /* 4-1-2-1-2 */ {  9,     8,   -11,     9,    -8,     8,     0,     0,   -10,    -9 },
    /* 5-4-1     */ {-10,     9,     8,    10,     0,    11,     0,     0,    -9,    -8 },
    /* 5-3-2     */ {-11,     0,     0,   -11,     9,    -8,    10,     9,     0,    -9 },
    /* 5-2-3     */ {  0,    10,     0,     8,   -11,   -10,     9,     8,     9,     0 }
    };

    int indice(const std::string& formacao);
    int getModificador(const std::string& atacante, const std::string& defensor);

}
