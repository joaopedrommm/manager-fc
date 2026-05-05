#include "Campeonato.h"

Time times[NUM_TIMES] = {
    Time( 1, "Flamengo", "FLA", 82, 180.0f, "4-2-3-1"),
    Time( 2, "Atletico Mineiro", "CAM", 79, 160.0f, "4-3-3"),
    Time( 3, "Palmeiras", "PAL", 81, 200.0f, "4-4-2"),
    Time( 4, "Fluminense", "FLU", 78, 120.0f, "4-2-3-1"),
    Time( 5, "Athletico Paranaense", "CAP", 76, 100.0f, "4-3-3"),
    Time( 6, "Internacional", "INT", 77, 110.0f, "4-4-2"),
    Time( 7, "Sao Paulo", "SAO", 78, 130.0f, "3-5-2"),
    Time( 8, "Gremio", "GRE", 77, 105.0f, "4-3-3"),
    Time( 9, "Botafogo", "BOT", 79, 140.0f, "4-3-3"),
    Time(10, "Vasco da Gama", "VAS", 76, 90.0f, "4-4-2"),
    Time(11, "Corinthians", "COR", 77, 115.0f, "4-2-3-1"),
    Time(12, "Cruzeiro", "CRU", 76, 95.0f, "4-3-3"),
    Time(13, "Bahia", "BAH", 76, 70.0f, "4-4-2"),
    Time(14, "Santos", "SAN", 75, 100.0f, "4-3-3"),
    Time(15, "Bragantino", "RBB", 76, 80.0f, "4-3-3"),
    Time(16, "Chapecoense", "CHA", 72, 50.0f, "4-4-2"),
    Time(17, "Coritiba", "CFC", 73, 55.0f, "4-3-3"),
    Time(18, "Vitoria", "VIT", 73, 42.0f, "4-4-2"),
    Time(19, "Mirassol", "MIR", 72, 45.0f, "4-3-3"),
    Time(20, "Remo", "REM", 70, 40.0f, "4-4-2")
};

Time* buscarTimePorId(int id) {
    for (int i = 0; i < NUM_TIMES; i++)
        if (times[i].getId() == id) return &times[i];
    return nullptr;
}

Time* buscarTimePorNome(const std::string& nome) {
    for (int i = 0; i < NUM_TIMES; i++)
        if (times[i].getNome() == nome) return &times[i];
    return nullptr;
}
