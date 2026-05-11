// Classe filha (derivada) de Jogador, adiciona os atributos e métodos para os jogadores de linha.

#pragma once
#include "Jogador.h"


class JogadorDeCampo : public Jogador {
private:
    int velocidade;
    int passe;
    int chute;

public:
    //Jogador base é o meio campista, então equilibra os atributos e agressividade.
    JogadorDeCampo(int id, const std::string& nome, const std::string& posicao,
                   int habilidade, int velocidade, int passe, int chute,
                   Agressividade agr = Agressividade::MEDIA)
        : Jogador(id, nome, posicao, habilidade, agr),
          velocidade(velocidade), passe(passe), chute(chute) {}

    float calcularContribuicao(float forcaBase) const override {
        float media = (getHabilidade() * 0.4f + velocidade * 0.2f
                     + passe * 0.2f      + chute * 0.2f);
        return forcaBase * (media / 100.0f);
    }

    std::string getTipo() const override { return "Jogador de Campo (" + getPosicao() + ")"; }

    int getVelocidade() const { return velocidade; }
    int getPasse()      const { return passe; }
    int getChute()      const { return chute; }
};


class Atacante : public JogadorDeCampo {
public:
    // Ajuste no cálculo de contribuição para pesar na qualidade chute e da velocidade.
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


class Defensor : public JogadorDeCampo {
public:
    // Ajuste na agressividade, pois defensores costumam fazer mais faltas e ajuste no cálculo de contribuição.
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