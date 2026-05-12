#pragma once
#include <string>

// Classe abstrata para a entidade jogador, com os atributos e métodos comuns a todas as posições

enum class Agressividade {
    BAIXA,
    MEDIA,
    ALTA
};

class Jogador {
private:
    int           id;
    std::string   nome;
    std::string   posicao;
    int           habilidade;
    Agressividade agressividade;

public:
    // Construtor
    Jogador(int id, const std::string& nome, const std::string& posicao,
            int habilidade, Agressividade agressividade)
        : id(id), nome(nome), posicao(posicao),
          habilidade(habilidade), agressividade(agressividade) {}

    // Destrutor
    virtual ~Jogador() {}

    // Método virtual para calcular a contribuição do jogador
    virtual float       calcularContribuicao(float forcaBase) const = 0;
    virtual std::string getTipo() const { return "Jogador"; }

    // Retorna a probabilidade de receber um cartão vermelho de acordo com a agressividade
    float getProbExpulsao() const {
        switch (agressividade) {
            case Agressividade::BAIXA: return 0.0005f;
            case Agressividade::MEDIA: return 0.0010f;
            case Agressividade::ALTA:  return 0.0018f;
            default:                   return 0.0010f;
        }
    }

    // Retorna a probabilidade de receber um cartão amarelo de acordo com a agressividade
    float getProbAmarelo() const {
        switch (agressividade) {
            case Agressividade::BAIXA: return 0.008f;
            case Agressividade::MEDIA: return 0.015f;
            case Agressividade::ALTA:  return 0.022f;
            default:                   return 0.015f;
        }
    }

    // Getters
    int                   getId()            const { return id; }
    const std::string&    getNome()          const { return nome; }
    const std::string&    getPosicao()       const { return posicao; }
    int                   getHabilidade()    const { return habilidade; }
    Agressividade         getAgressividade() const { return agressividade; }

    // Setter
    void setHabilidade(int h) { habilidade = h; }
};