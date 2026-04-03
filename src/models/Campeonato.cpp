#include "Campeonato.h"

// -----------------------------------------------------------------------
// Banco de dados dos 20 clubes da Serie A 2024
// Campos: id, nome, sigla, forca, orcamento (mi R$), formacao,
//         pontos, vitorias, empates, derrotas, golsPro, golsContra
// -----------------------------------------------------------------------
Time times[NUM_TIMES] = {
    { 1, "Flamengo",              "FLA", 88, 180.0f, "4-2-3-1", 0,0,0,0,0,0 },
    { 2, "Atletico Mineiro",      "CAM", 85, 160.0f, "4-3-3",   0,0,0,0,0,0 },
    { 3, "Palmeiras",             "PAL", 87, 200.0f, "4-4-2",   0,0,0,0,0,0 },
    { 4, "Fluminense",            "FLU", 80, 120.0f, "4-2-3-1", 0,0,0,0,0,0 },
    { 5, "Atletico Paranaense",   "CAP", 79, 100.0f, "4-3-3",   0,0,0,0,0,0 },
    { 6, "Internacional",         "INT", 78, 110.0f, "4-4-2",   0,0,0,0,0,0 },
    { 7, "Sao Paulo",             "SAO", 77, 130.0f, "3-5-2",   0,0,0,0,0,0 },
    { 8, "Gremio",                "GRE", 76, 105.0f, "4-3-3",   0,0,0,0,0,0 },
    { 9, "Botafogo",              "BOT", 82, 140.0f, "4-3-3",   0,0,0,0,0,0 },
    {10, "Vasco da Gama",         "VAS", 72, 90.0f,  "4-4-2",   0,0,0,0,0,0 },
    {11, "Corinthians",           "COR", 74, 115.0f, "4-2-3-1", 0,0,0,0,0,0 },
    {12, "Cruzeiro",              "CRU", 73, 95.0f,  "4-3-3",   0,0,0,0,0,0 },
    {13, "Bahia",                 "BAH", 68, 70.0f,  "4-4-2",   0,0,0,0,0,0 },
    {14, "Fortaleza",             "FOR", 70, 75.0f,  "4-4-2",   0,0,0,0,0,0 },
    {15, "Bragantino",            "RBB", 71, 80.0f,  "4-3-3",   0,0,0,0,0,0 },
    {16, "Cuiaba",                "CUI", 58, 45.0f,  "4-4-2",   0,0,0,0,0,0 },
    {17, "Criciuma",              "CRI", 60, 40.0f,  "4-3-3",   0,0,0,0,0,0 },
    {18, "Vitoria",               "VIT", 59, 42.0f,  "4-4-2",   0,0,0,0,0,0 },
    {19, "Juventude",             "JUV", 61, 48.0f,  "3-5-2",   0,0,0,0,0,0 },
    {20, "Atletico Goianiense",   "ACG", 62, 50.0f,  "4-3-3",   0,0,0,0,0,0 }
};

// -----------------------------------------------------------------------

Time* buscarTimePorId(int id) {
    for (int i = 0; i < NUM_TIMES; i++) {
        if (times[i].id == id) return &times[i];
    }
    return nullptr;
}

Time* buscarTimePorNome(const std::string& nome) {
    for (int i = 0; i < NUM_TIMES; i++) {
        if (times[i].nome == nome) return &times[i];
    }
    return nullptr;
}
