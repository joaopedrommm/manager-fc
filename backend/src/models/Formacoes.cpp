#include "Formacoes.h"
using namespace std;

// Aplicação da vantagem tática entre as formações
namespace Formacoes {

    int indice(const string& formacao) {
        for (int i = 0; i < NUM_FORMACOES; i++)
            if (NOMES[i] == formacao) return i;
        return -1;
    }

    int getModificador(const string& atacante, const string& defensor) {
        int i = indice(atacante);
        int j = indice(defensor);
        if (i == -1 || j == -1) return 0;
        return MODIFICADOR[i][j];
    }

}
