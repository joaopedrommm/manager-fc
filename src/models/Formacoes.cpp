#include "Formacoes.h"

int indiceDaFormacao(const std::string& formacao) {
    for (int i = 0; i < NUM_FORMACOES; i++) {
        if (FORMACOES[i] == formacao) return i;
    }
    return -1;
}

int getModificador(const std::string& atacante, const std::string& defensor) {
    int i = indiceDaFormacao(atacante);
    int j = indiceDaFormacao(defensor);
    if (i == -1 || j == -1) return 0;
    return MODIFICADOR_TATICO[i][j];
}
