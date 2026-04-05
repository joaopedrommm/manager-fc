#include "Campeonato.h"

Time times[NUM_TIMES] = {
    Time( 1, "Flamengo",            "FLA", 88, 180.0f, "4-2-3-1"),
    Time( 2, "Atletico Mineiro",    "CAM", 85, 160.0f, "4-3-3"  ),
    Time( 3, "Palmeiras",           "PAL", 87, 200.0f, "4-4-2"  ),
    Time( 4, "Fluminense",          "FLU", 80, 120.0f, "4-2-3-1"),
    Time( 5, "Atletico Paranaense", "CAP", 79, 100.0f, "4-3-3"  ),
    Time( 6, "Internacional",       "INT", 78, 110.0f, "4-4-2"  ),
    Time( 7, "Sao Paulo",           "SAO", 77, 130.0f, "3-5-2"  ),
    Time( 8, "Gremio",              "GRE", 76, 105.0f, "4-3-3"  ),
    Time( 9, "Botafogo",            "BOT", 82, 140.0f, "4-3-3"  ),
    Time(10, "Vasco da Gama",       "VAS", 72,  90.0f, "4-4-2"  ),
    Time(11, "Corinthians",         "COR", 74, 115.0f, "4-2-3-1"),
    Time(12, "Cruzeiro",            "CRU", 73,  95.0f, "4-3-3"  ),
    Time(13, "Bahia",               "BAH", 68,  70.0f, "4-4-2"  ),
    Time(14, "Fortaleza",           "FOR", 70,  75.0f, "4-4-2"  ),
    Time(15, "Bragantino",          "RBB", 71,  80.0f, "4-3-3"  ),
    Time(16, "Cuiaba",              "CUI", 58,  45.0f, "4-4-2"  ),
    Time(17, "Criciuma",            "CRI", 60,  40.0f, "4-3-3"  ),
    Time(18, "Vitoria",             "VIT", 59,  42.0f, "4-4-2"  ),
    Time(19, "Juventude",           "JUV", 61,  48.0f, "3-5-2"  ),
    Time(20, "Atletico Goianiense", "ACG", 62,  50.0f, "4-3-3"  )
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