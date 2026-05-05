#include "Formacoes.h"

namespace Formacoes {

    int indice(const std::string& formacao) {
        for (int i = 0; i < NUM_FORMACOES; i++)
            if (NOMES[i] == formacao) return i;
        return -1;
    }

    int getModificador(const std::string& atacante, const std::string& defensor) {
        int i = indice(atacante);
        int j = indice(defensor);
        if (i == -1 || j == -1) return 0;
        return MODIFICADOR[i][j];
    }

}
