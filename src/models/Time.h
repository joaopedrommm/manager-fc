#pragma once
#include <string>

class Time {
private:
    int id;
    std::string nome;
    std::string sigla;
    int forca;
    float orcamento;
    std::string formacao;

    // Estatisticas da temporada
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int golsPro;
    int golsContra;

public:
    Time() : id(0), forca(0), orcamento(0.0f),
             pontos(0), vitorias(0), empates(0),
             derrotas(0), golsPro(0), golsContra(0) {}

    Time(int id, const std::string& nome, const std::string& sigla,
         int forca, float orcamento, const std::string& formacao)
        : id(id), nome(nome), sigla(sigla), forca(forca),
          orcamento(orcamento), formacao(formacao),
          pontos(0), vitorias(0), empates(0),
          derrotas(0), golsPro(0), golsContra(0) {}

    // Getters
    int getId()                      const { return id; }
    const std::string& getNome()     const { return nome; }
    const std::string& getSigla()    const { return sigla; }
    int getForca()                   const { return forca; }
    float getOrcamento()             const { return orcamento; }
    const std::string& getFormacao() const { return formacao; }
    int getPontos()                  const { return pontos; }
    int getVitorias()                const { return vitorias; }
    int getEmpates()                 const { return empates; }
    int getDerrotas()                const { return derrotas; }
    int getGolsPro()                 const { return golsPro; }
    int getGolsContra()              const { return golsContra; }
    int getSaldoGols()               const { return golsPro - golsContra; }

    // Setters
    void setFormacao(const std::string& f) { formacao = f; }
    void setForca(int f)                   { forca = f; }
    void setOrcamento(float o)             { orcamento = o; }

    // Atualizacao de estatisticas
    void addVitoria()         { vitorias++; pontos += 3; }
    void addEmpate()          { empates++;  pontos += 1; }
    void addDerrota()         { derrotas++; }
    void addGolsPro(int g)    { golsPro    += g; }
    void addGolsContra(int g) { golsContra += g; }

    // Reseta estatisticas para nova temporada
    void resetStats() {
        pontos = vitorias = empates = derrotas = golsPro = golsContra = 0;
    }
};
