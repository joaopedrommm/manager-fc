#pragma once
#include "Jogador.h"

// =============================================================================
// JogadorDeCampo.h  —  Outra classe filha (derivada) de Jogador.
//
// CONCEITO OOP: HERANÇA MÚLTIPLA EM CADEIA (cadeia de herança)
//   JogadorDeCampo herda de Jogador.
//   Daqui ainda podemos derivar Atacante, Meio, Defensor — cada um com seu
//   próprio peso na contribuição.
//
// CONCEITO OOP: POLIMORFISMO
//   A versão de calcularContribuicao() aqui considera velocidade e passe,
//   atributos que não fazem sentido para um Goleiro.
// =============================================================================

class JogadorDeCampo : public Jogador {
private:
    int velocidade; // capacidade de movimentação (0–100)
    int passe;      // qualidade de passe (0–100)
    int chute;      // potência/precisão de chute (0–100)

public:
    JogadorDeCampo(int id, const std::string& nome, const std::string& posicao,
                   int habilidade, int velocidade, int passe, int chute)
        : Jogador(id, nome, posicao, habilidade),
          velocidade(velocidade), passe(passe), chute(chute) {}

    // -------------------------------------------------------------------------
    // Override de calcularContribuicao()
    //
    // Jogador de campo contribui de forma balanceada entre ataque e posse.
    // -------------------------------------------------------------------------
    float calcularContribuicao(float forcaBase) const override {
        // Média dos atributos específicos + habilidade geral
        float media = (habilidade * 0.4f + velocidade * 0.2f
                     + passe * 0.2f      + chute * 0.2f);
        return forcaBase * (media / 100.0f);
    }

    std::string getTipo() const override { return "Jogador de Campo (" + posicao + ")"; }

    // Getters específicos
    int getVelocidade() const { return velocidade; }
    int getPasse()      const { return passe; }
    int getChute()      const { return chute; }
};

// =============================================================================
// Atacante — herda de JogadorDeCampo.
// Demonstra cadeia de herança: Atacante → JogadorDeCampo → Jogador
// =============================================================================
class Atacante : public JogadorDeCampo {
public:
    Atacante(int id, const std::string& nome, int habilidade,
             int velocidade, int passe, int chute)
        : JogadorDeCampo(id, nome, "ATA", habilidade, velocidade, passe, chute) {}

    // Atacantes têm contribuição maior no chute e velocidade
    float calcularContribuicao(float forcaBase) const override {
        float media = (getHabilidade() * 0.3f + getVelocidade() * 0.3f
                     + getPasse() * 0.1f        + getChute() * 0.3f);
        return forcaBase * (media / 100.0f);
    }

    std::string getTipo() const override { return "Atacante"; }
};

// =============================================================================
// Defensor — herda de JogadorDeCampo.
// =============================================================================
class Defensor : public JogadorDeCampo {
public:
    Defensor(int id, const std::string& nome, int habilidade,
             int velocidade, int passe, int chute)
        : JogadorDeCampo(id, nome, "ZAG", habilidade, velocidade, passe, chute) {}

    // Defensores têm contribuição maior na habilidade geral e passe
    float calcularContribuicao(float forcaBase) const override {
        float media = (getHabilidade() * 0.5f + getVelocidade() * 0.2f
                     + getPasse() * 0.3f);
        return forcaBase * (media / 100.0f);
    }

    std::string getTipo() const override { return "Defensor"; }
};
