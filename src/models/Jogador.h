#pragma once
#include <string>

// =============================================================================
// Jogador.h  —  Classe base abstrata que representa um jogador de futebol.
//
// CONCEITO OOP: HERANÇA + POLIMORFISMO
//   Esta é a classe "pai" (base). Ela define a interface comum a todo jogador.
//   As classes filhas (Goleiro, JogadorDeCampo) herdam de Jogador e implementam
//   o método virtual puro calcularContribuicao(), cada uma do seu jeito.
//
//   Isso é polimorfismo: o mesmo método produz comportamentos diferentes
//   dependendo do tipo concreto do objeto apontado pelo ponteiro Jogador*.
// =============================================================================

// =============================================================================
// CONCEITO OOP: ENUM CLASS
//   Agrupa constantes relacionadas em um tipo próprio com escopo, evitando
//   colisões de nomes e tornando o código mais legível e seguro.
//   Usado aqui para modelar o nível de agressividade individual do jogador,
//   que influencia a probabilidade de receber cartões durante a partida.
// =============================================================================
enum class Agressividade {
    BAIXA,  // jogador cauteloso  → menor chance de cartão
    MEDIA,  // jogador equilibrado
    ALTA    // jogador impulsivo  → maior chance de cartão
};

class Jogador {
protected:
    // --- Atributos protegidos: visíveis para as classes filhas ---
    int          id;
    std::string  nome;
    std::string  posicao;      // ex.: "GOL", "ZAG", "MEI", "ATA"
    int          habilidade;   // nota geral do jogador (0–100)
    Agressividade agressividade; // nível de agressividade (afeta cartões)

public:
    // -------------------------------------------------------------------------
    // Construtor: agressividade tem valor padrão MEDIA para manter
    // compatibilidade com código já existente que não passou esse parâmetro.
    // -------------------------------------------------------------------------
    Jogador(int id, const std::string& nome, const std::string& posicao,
            int habilidade, Agressividade agr = Agressividade::MEDIA)
        : id(id), nome(nome), posicao(posicao),
          habilidade(habilidade), agressividade(agr) {}

    // Destrutor virtual — OBRIGATÓRIO em classes base com polimorfismo.
    // Garante que ao deletar um Jogador* que aponta para Goleiro, o destrutor
    // correto (Goleiro::~Goleiro) seja chamado.
    virtual ~Jogador() {}

    // -------------------------------------------------------------------------
    // MÉTODO VIRTUAL PURO — define a "interface" de contribuição do jogador.
    // Cada classe filha DEVE reimplementar este método.
    //
    // forcaBase: força média do time (0–100)
    // Retorna: um valor que representa o quanto o jogador contribui para a
    //          força efetiva do time naquela posição.
    // -------------------------------------------------------------------------
    virtual float calcularContribuicao(float forcaBase) const = 0;

    // Método virtual (não puro) — pode ser sobrescrito, mas tem implementação padrão.
    // Retorna uma descrição textual do tipo do jogador.
    virtual std::string getTipo() const { return "Jogador"; }

    // -------------------------------------------------------------------------
    // getPExpulsao() — probabilidade POR MINUTO de receber cartão vermelho.
    // Valores calibrados para média real de ~0.25 vermelhos/partida.
    // Conforme especificação do algoritmo de simulação.
    // -------------------------------------------------------------------------
    float getPExpulsao() const {
        switch (agressividade) {
            case Agressividade::BAIXA: return 0.007f;
            case Agressividade::MEDIA: return 0.0135f;
            case Agressividade::ALTA:  return 0.020f;
        }
        return 0.0135f;
    }

    // -------------------------------------------------------------------------
    // getPCartaoAmarelo() — probabilidade POR MINUTO de receber cartão amarelo.
    // Menor que a do vermelho (conforme design do jogo).
    // -------------------------------------------------------------------------
    float getPCartaoAmarelo() const {
        return getPExpulsao() * 0.5f;
    }

    // --- Getters ---
    int                getId()           const { return id; }
    const std::string& getNome()         const { return nome; }
    const std::string& getPosicao()      const { return posicao; }
    int                getHabilidade()   const { return habilidade; }
    Agressividade      getAgressividade() const { return agressividade; }

    // Setter
    void setHabilidade(int h) { habilidade = h; }
};
