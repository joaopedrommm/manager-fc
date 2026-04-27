#pragma once
#include "Jogador.h"

// =============================================================================
// JogadorDeCampo.h  —  Jogadores de campo + subclasses Atacante e Defensor
// =============================================================================

class JogadorDeCampo : public Jogador {
private:
    int velocidade;
    int passe;
    int chute;

public:
    // Agressividade agr = MEDIA: parâmetro opcional — quem não passar usa MEDIA.
    // Volantes no main.cpp passarão ALTA explicitamente.
    JogadorDeCampo(int id, const std::string& nome, const std::string& posicao,
                   int habilidade, int velocidade, int passe, int chute,
                   Agressividade agr = Agressividade::MEDIA)
        : Jogador(id, nome, posicao, habilidade, agr),
          velocidade(velocidade), passe(passe), chute(chute) {}

    float calcularContribuicao(float forcaBase) const override {
        float media = (habilidade * 0.4f + velocidade * 0.2f
                     + passe * 0.2f      + chute * 0.2f);
        return forcaBase * (media / 100.0f);
    }

    std::string getTipo() const override { return "Jogador de Campo (" + posicao + ")"; }

    int getVelocidade() const { return velocidade; }
    int getPasse()      const { return passe; }
    int getChute()      const { return chute; }
};

// =============================================================================
// Atacante — herda de JogadorDeCampo. Agressividade MEDIA (hardcoded).
// =============================================================================
class Atacante : public JogadorDeCampo {
public:
    Atacante(int id, const std::string& nome, int habilidade,
             int velocidade, int passe, int chute)
        : JogadorDeCampo(id, nome, "ATA", habilidade, velocidade, passe, chute,
                         Agressividade::MEDIA) {}

    float calcularContribuicao(float forcaBase) const override {
        float media = (getHabilidade() * 0.3f + getVelocidade() * 0.3f
                     + getPasse() * 0.1f        + getChute() * 0.3f);
        return forcaBase * (media / 100.0f);
    }

    std::string getTipo() const override { return "Atacante"; }
};

// =============================================================================
// Defensor — herda de JogadorDeCampo. Agressividade ALTA (hardcoded).
// Zagueiros são os mais agressivos do time — refletido na probabilidade de expulsão.
// =============================================================================
class Defensor : public JogadorDeCampo {
public:
    Defensor(int id, const std::string& nome, int habilidade,
             int velocidade, int passe, int chute)
        : JogadorDeCampo(id, nome, "ZAG", habilidade, velocidade, passe, chute,
                         Agressividade::ALTA) {}

    float calcularContribuicao(float forcaBase) const override {
        float media = (getHabilidade() * 0.5f + getVelocidade() * 0.2f
                     + getPasse() * 0.3f);
        return forcaBase * (media / 100.0f);
    }

    std::string getTipo() const override { return "Defensor"; }
};