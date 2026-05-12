#pragma once
#include <string>
#include "Jogador.h"
using namespace std;

// =============================================================================
// Time.h  —  Representa um clube do Brasileirão Série A.
//
// CONCEITO OOP: ENCAPSULAMENTO
//   Todos os atributos são privados. O acesso externo é feito apenas pelos
//   getters e setters públicos — assim protegemos a integridade dos dados.
//
// CONCEITO OOP: COMPOSIÇÃO + POLIMORFISMO
//   O time tem um array de ponteiros Jogador*. Cada ponteiro pode apontar
//   para um Goleiro, um Atacante, um Defensor etc.
//   Quando chamamos elenco[i]->calcularContribuicao(), o C++ decide
//   automaticamente qual versão do método chamar — isso é polimorfismo!
// =============================================================================

const int TAM_ELENCO = 15;

class Time {
private:
    //Atributos básicos do time
    int         id;
    string nome;
    string sigla;
    int         forca;
    int         forcaInicial;
    float       orcamento;
    float       orcamentoInicial;
    string formacao;

    //Estatísticas do time
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int golsPro;
    int golsContra;

    // Elenco de jogadores (ponteiros para a classe base Jogador).

    Jogador* elenco[TAM_ELENCO];
    int      numJogadores; // quantos jogadores foram adicionados

public:
    // Construtor padrão
    Time() : id(0), forca(0), forcaInicial(0), orcamento(0.0f), orcamentoInicial(0.0f),
             pontos(0), vitorias(0), empates(0),
             derrotas(0), golsPro(0), golsContra(0),
             numJogadores(0) {
        for (int i = 0; i < TAM_ELENCO; i++) elenco[i] = nullptr;
    }

    // Construtor completo
    Time(int id, const string& nome, const string& sigla,
         int forca, float orcamento, const string& formacao)
        : id(id), nome(nome), sigla(sigla), forca(forca), forcaInicial(forca),
          orcamento(orcamento), orcamentoInicial(orcamento), formacao(formacao),
          pontos(0), vitorias(0), empates(0),
          derrotas(0), golsPro(0), golsContra(0),
          numJogadores(0) {
        for (int i = 0; i < TAM_ELENCO; i++) elenco[i] = nullptr;
    }

    // Destrutor
    ~Time() {
        for (int i = 0; i < numJogadores; i++) {
            delete elenco[i];
            elenco[i] = nullptr;
        }
    }

    // Rever a utilidade
    // Adiciona um jogador ao elenco.
    // Recebe Jogador* — pode ser Goleiro*, Atacante*, Defensor*, etc.
    void adicionarJogador(Jogador* j) {
        if (numJogadores < TAM_ELENCO)
            elenco[numJogadores++] = j;
    }

    // Calcula a força efetiva do time usando POLIMORFISMO.
    // Percorre o elenco e chama calcularContribuicao() em cada jogador.
    // O C++ chama a versão correta (Goleiro, Atacante, etc.) automaticamente.
    // Se o elenco estiver vazio, usa o valor fixo de 'forca'.

    float calcularForcaElenco() const {
        if (numJogadores == 0) return (float)forca;

        float total = 0.0f;
        for (int i = 0; i < numJogadores; i++)
            total += elenco[i]->calcularContribuicao((float)forca);

        return total / numJogadores;
    }

    // Getters
    int                getId()           const { return id; }
    const string& getNome()         const { return nome; }
    const string& getSigla()        const { return sigla; }
    int                getForca()        const { return forca; }
    float              getOrcamento()    const { return orcamento; }
    const string& getFormacao()     const { return formacao; }
    int                getPontos()       const { return pontos; }
    int                getVitorias()     const { return vitorias; }
    int                getEmpates()      const { return empates; }
    int                getDerrotas()     const { return derrotas; }
    int                getGolsPro()      const { return golsPro; }
    int                getGolsContra()   const { return golsContra; }
    int                getSaldoGols()    const { return golsPro - golsContra; }
    int                getNumJogadores() const { return numJogadores; }

    // Acesso ao elenco (somente leitura)
    const Jogador* getJogador(int i) const {
        return (i >= 0 && i < numJogadores) ? elenco[i] : nullptr;
    }

    // Setters
    void setFormacao(const string& f) { formacao = f; }
    void setForca(int f)                   { forca = f; }
    void setOrcamento(float o)             { orcamento = o; }

    // Atualização de estatísticas
    void addVitoria()         { vitorias++; pontos += 3; }
    void addEmpate()          { empates++;  pontos += 1; }
    void addDerrota()         { derrotas++; }
    void addGolsPro(int g)    { golsPro    += g; }
    void addGolsContra(int g) { golsContra += g; }

    // Reseta estatísticas para nova temporada
    void resetStats() {
        pontos = vitorias = empates = derrotas = golsPro = golsContra = 0;
        forca     = forcaInicial;
        orcamento = orcamentoInicial;
    }

    void melhorarJogadores(int delta) {
        for (int i = 0; i < numJogadores; i++)
            elenco[i]->setHabilidade(elenco[i]->getHabilidade() + delta);
    }

    void limparElenco() {
        for (int i = 0; i < numJogadores; i++) {
            delete elenco[i];
            elenco[i] = nullptr;
        }
        numJogadores = 0;
    }
};
