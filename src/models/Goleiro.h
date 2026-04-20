#pragma once
#include "Jogador.h"

// =============================================================================
// Goleiro.h  —  Classe filha (derivada) de Jogador.
//
// CONCEITO OOP: HERANÇA
//   Goleiro herda TODOS os atributos e métodos de Jogador (id, nome, posicao,
//   habilidade, getters...). Só precisamos adicionar o que é específico do
//   goleiro: reflexos e defesas penaltis.
//
// CONCEITO OOP: POLIMORFISMO (override)
//   Goleiro reimplementa calcularContribuicao() e getTipo(). Quando tivermos
//   um ponteiro Jogador* apontando para um Goleiro, e chamarmos
//   calcularContribuicao(), o C++ vai chamar a versão do Goleiro.
// =============================================================================

class Goleiro : public Jogador {
private:
    int reflexos;       // qualidade dos reflexos (0–100)
    int defesasPenalti; // especialidade em pênaltis (0–100)

public:
    // -------------------------------------------------------------------------
    // Construtor: chama o construtor da classe pai com ':  Jogador(...)'
    // agressividade tem padrão BAIXA — goleiros raramente recebem cartão por
    // jogar agressivo. O valor pode ser alterado individualmente se necessário.
    // -------------------------------------------------------------------------
    Goleiro(int id, const std::string& nome, int habilidade, int reflexos, int defesasPenalti,
            Agressividade agr = Agressividade::BAIXA)
        : Jogador(id, nome, "GOL", habilidade, agr),
          reflexos(reflexos), defesasPenalti(defesasPenalti) {}

    // -------------------------------------------------------------------------
    // Override de calcularContribuicao()
    //
    // O goleiro contribui principalmente para a DEFESA do time.
    // Sua contribuição é calculada com peso maior nos reflexos.
    // -------------------------------------------------------------------------
    float calcularContribuicao(float forcaBase) const override {
        // Fórmula: média ponderada entre habilidade geral e reflexos,
        // ajustada em relação à força base do time.
        float mediaGoleiro = (habilidade * 0.5f + reflexos * 0.5f);
        return forcaBase * (mediaGoleiro / 100.0f);
    }

    // Override de getTipo()
    std::string getTipo() const override { return "Goleiro"; }

    // Getters específicos do Goleiro
    int getReflexos()        const { return reflexos; }
    int getDefesasPenalti()  const { return defesasPenalti; }
};
