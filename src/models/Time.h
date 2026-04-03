#pragma once
#include <string>

struct Time {
    int id;
    std::string nome;
    std::string sigla;
    int forca;           // 1-100
    float orcamento;     // em milhoes de reais
    std::string formacao; // ex: "4-3-3"

    // Estatisticas da temporada
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int golsPro;
    int golsContra;

    int saldoGols() const { return golsPro - golsContra; }
};
