#pragma once
#include <string>

enum class Agressividade {
    BAIXA,
    MEDIA,
    ALTA
};

class Jogador {
protected:
    int           id;
    std::string   nome;
    std::string   posicao;
    int           habilidade;
    Agressividade agressividade;

public:
    Jogador(int id, const std::string& nome, const std::string& posicao,
            int habilidade, Agressividade agressividade)
        : id(id), nome(nome), posicao(posicao),
          habilidade(habilidade), agressividade(agressividade) {}

    virtual ~Jogador() {}

    virtual float       calcularContribuicao(float forcaBase) const = 0;
    virtual std::string getTipo() const { return "Jogador"; }

    // Vermelho: evento RARO (~1 por 4 jogos no total)
    float getProbExpulsao() const {
        switch (agressividade) {
            case Agressividade::BAIXA: return 0.0005f;
            case Agressividade::MEDIA: return 0.0010f;
            case Agressividade::ALTA:  return 0.0018f;
            default:                   return 0.0010f;
        }
    }

    // Amarelo: evento COMUM (~3 por jogo no total)
    float getProbAmarelo() const {
        switch (agressividade) {
            case Agressividade::BAIXA: return 0.008f;
            case Agressividade::MEDIA: return 0.015f;
            case Agressividade::ALTA:  return 0.022f;
            default:                   return 0.015f;
        }
    }

    int                   getId()            const { return id; }
    const std::string&    getNome()          const { return nome; }
    const std::string&    getPosicao()       const { return posicao; }
    int                   getHabilidade()    const { return habilidade; }
    Agressividade         getAgressividade() const { return agressividade; }

    void setHabilidade(int h) { habilidade = h; }
};