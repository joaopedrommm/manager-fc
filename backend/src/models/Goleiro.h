//Classe filha (derivada) de Jogador, adiciona os atributos e métodos específicos para os goleiros.

#pragma once
#include "Jogador.h"

// =============================================================================
// Goleiro.h  —  Classe filha (derivada) de Jogador.
// =============================================================================

class Goleiro : public Jogador {
private:
    int reflexos;
    int defesasPenalti;

public:
    // Única posição com agressividade baixa, por ser muito raro um goleiro ser expulso.
    Goleiro(int id, const std::string& nome, int habilidade, int reflexos, int defesasPenalti)
        : Jogador(id, nome, "GOL", habilidade, Agressividade::BAIXA),
          reflexos(reflexos), defesasPenalti(defesasPenalti) {}

    float calcularContribuicao(float forcaBase) const override {
        float mediaGoleiro = (getHabilidade() * 0.5f + reflexos * 0.5f);
        return forcaBase * (mediaGoleiro / 100.0f);
    }

    std::string getTipo() const override { return "Goleiro"; }

    int getReflexos()       const { return reflexos; }
    int getDefesasPenalti() const { return defesasPenalti; }
};