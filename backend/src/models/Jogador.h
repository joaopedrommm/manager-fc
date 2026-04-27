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

class Jogador {
protected:
    // --- Atributos protegidos: visíveis para as classes filhas ---
    int         id;
    std::string nome;
    std::string posicao;   // ex.: "GOL", "ZAG", "MEI", "ATA"
    int         habilidade; // nota geral do jogador (0–100)

public:
    // Construtor
    Jogador(int id, const std::string& nome, const std::string& posicao, int habilidade)
        : id(id), nome(nome), posicao(posicao), habilidade(habilidade) {}

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

    // --- Getters ---
    int                getId()        const { return id; }
    const std::string& getNome()      const { return nome; }
    const std::string& getPosicao()   const { return posicao; }
    int                getHabilidade() const { return habilidade; }

    // Setter
    void setHabilidade(int h) { habilidade = h; }
};
