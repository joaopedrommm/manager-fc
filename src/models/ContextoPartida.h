#pragma once
#include "Time.h"
#include "Jogador.h"
#include "Formacoes.h"
#include <cstdlib>

class ContextoPartida {
private:
    Time* timeCasa;
    Time* timeVisitante;

    bool expulsosCasa[TAM_ELENCO];
    bool expulsosVisit[TAM_ELENCO];

    int numAtivosCasa;
    int numAtivosVisit;

    bool isCasa(Time* t) const { return t == timeCasa; }

    float calcularForcaAtivos(Time* time) const {
        // const bool* — correto porque o método é const
        const bool* expulsos = isCasa(time) ? expulsosCasa : expulsosVisit;

        float total = 0.0f;
        int   count = 0;

        for (int i = 0; i < time->getNumJogadores(); i++) {
            if (!expulsos[i]) {
                total += time->getJogador(i)->calcularContribuicao((float)time->getForca());
                count++;
            }
        }
        return (count > 0) ? (total / count) : (float)time->getForca() * 0.3f;
    }

public:
    ContextoPartida(Time* casa, Time* visitante)
        : timeCasa(casa), timeVisitante(visitante),
          numAtivosCasa(TAM_ELENCO), numAtivosVisit(TAM_ELENCO) {
        for (int i = 0; i < TAM_ELENCO; i++) {
            expulsosCasa[i]  = false;
            expulsosVisit[i] = false;
        }
    }

    Jogador* getJogadorAleatorio(Time* time) {
        bool* expulsos = isCasa(time) ? expulsosCasa : expulsosVisit;
        int   num      = time->getNumJogadores();

        int ativos[TAM_ELENCO];
        int count = 0;
        for (int i = 0; i < num; i++)
            if (!expulsos[i]) ativos[count++] = i;

        if (count == 0) return nullptr;
        int idx = ativos[rand() % count];
        return const_cast<Jogador*>(time->getJogador(idx));
    }

    void expulsarJogador(Time* time, Jogador* jogador) {
        bool* expulsos = isCasa(time) ? expulsosCasa : expulsosVisit;
        int&  ativos   = isCasa(time) ? numAtivosCasa : numAtivosVisit;

        for (int i = 0; i < time->getNumJogadores(); i++) {
            if (time->getJogador(i) == jogador && !expulsos[i]) {
                expulsos[i] = true;
                ativos--;
                break;
            }
        }
    }

    float calcularProbGol(Time* atacante, Time* defensor) const {
        float fa = calcularForcaAtivos(atacante);
        float fd = calcularForcaAtivos(defensor);
        if (fd < 1.0f) fd = 1.0f;

        int mod = Formacoes::getModificador(atacante->getFormacao(),
                                            defensor->getFormacao());
        fa *= (1.0f + mod / 100.0f);

        const float CONST_GOL = 0.0150f;
        float prob = CONST_GOL * (fa / fd);

        if (prob < 0.003f) prob = 0.003f;
        if (prob > 0.055f) prob = 0.055f;
        return prob;
    }

    int getNumAtivosCasa()  const { return numAtivosCasa; }
    int getNumAtivosVisit() const { return numAtivosVisit; }
};