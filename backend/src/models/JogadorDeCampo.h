#pragma once
#include "Jogador.h"
using namespace std;

// Classe filha (derivada) de Jogador, adiciona os atributos e métodos para os jogadores de linha

class JogadorDeCampo : public Jogador {
private:
    // Atributos específicos para jogadores de linha, que influenciam na contribuição do jogador para o time
    int velocidade;
    int passe;
    int chute;

public:
    // Jogador base é o meio campista, então equilibra os atributos e agressividade
    // Construtor
    JogadorDeCampo(int id, const string& nome, const string& posicao,
                   int habilidade, int velocidade, int passe, int chute,
                   Agressividade agr = Agressividade::MEDIA)
        : Jogador(id, nome, posicao, habilidade, agr),
          velocidade(velocidade), passe(passe), chute(chute) {}
    // Cálculo da contribuição do jogador de meio campo
    float calcularContribuicao(float forcaBase) const override {
        float media = (getHabilidade() * 0.4f + velocidade * 0.2f
                     + passe * 0.2f      + chute * 0.2f);
        return forcaBase * (media / 100.0f);
    }

    string getTipo() const override { return "Jogador de Campo (" + getPosicao() + ")"; }

    // Getters
    int getVelocidade() const { return velocidade; }
    int getPasse()      const { return passe; }
    int getChute()      const { return chute; }
};


class Atacante : public JogadorDeCampo {
public:
    // Construtor
    Atacante(int id, const string& nome, int habilidade,
             int velocidade, int passe, int chute)
        : JogadorDeCampo(id, nome, "ATA", habilidade, velocidade, passe, chute,
                         Agressividade::MEDIA) {}
    // Ajuste no cálculo de contribuição para pesar na qualidade chute e da velocidade
    float calcularContribuicao(float forcaBase) const override {
        float media = (getHabilidade() * 0.3f + getVelocidade() * 0.3f
                     + getPasse() * 0.1f        + getChute() * 0.3f);
        return forcaBase * (media / 100.0f);
    }

    string getTipo() const override { return "Atacante"; }
};


class Defensor : public JogadorDeCampo {
public:
    // Ajuste na agressividade, pois defensores costumam fazer mais faltas
    Defensor(int id, const string& nome, int habilidade,
             int velocidade, int passe, int chute)
        : JogadorDeCampo(id, nome, "ZAG", habilidade, velocidade, passe, chute,
                         Agressividade::ALTA) {}
    //  Ajuste no cálculo de contribuição para pesar mais na habilidade e passe
    float calcularContribuicao(float forcaBase) const override {
        float media = (getHabilidade() * 0.5f + getVelocidade() * 0.2f
                     + getPasse() * 0.3f);
        return forcaBase * (media / 100.0f);
    }

    string getTipo() const override { return "Defensor"; }
};