#pragma once
#include <string>
#include <cstdlib>   // rand()
#include "Time.h"

// =============================================================================
// Evento.h  —  Hierarquia de eventos que ocorrem durante uma partida.
//
// CONCEITO OOP: HERANÇA + POLIMORFISMO
//   Evento é a classe base abstrata. Cada tipo de lance (gol, cartão,
//   intervalo) é uma classe filha que herda os atributos comuns (minuto,
//   time) e reimplementa getDescricao() com sua própria narrativa.
//
//   Em Simulacao.cpp, todos os eventos são guardados como Evento* numa
//   LinkedList. Ao exibir, chamamos getDescricao() sem saber o tipo real —
//   o C++ escolhe a versão certa automaticamente. Isso é polimorfismo puro.
//
// Hierarquia:
//   Evento  (base abstrata)
//   ├── EventoGol
//   ├── EventoCartaoAmarelo
//   ├── EventoCartaoVermelho
//   └── EventoIntervalo
// =============================================================================

class Evento {
protected:
    int   minuto;
    Time* time;   // time envolvido (nullptr para EventoIntervalo)

public:
    Evento(int min, Time* t) : minuto(min), time(t) {}

    // Destrutor virtual obrigatório para classes polimórficas.
    virtual ~Evento() {}

    // -------------------------------------------------------------------------
    // MÉTODO VIRTUAL PURO: cada subclasse define sua própria descrição.
    // É o ponto central do polimorfismo desta hierarquia.
    // -------------------------------------------------------------------------
    virtual std::string getDescricao() const = 0;

    // Getters comuns a todos os eventos
    int   getMinuto() const { return minuto; }
    Time* getTime()   const { return time; }
};

// =============================================================================
// EventoGol — registra um gol marcado durante a partida.
// =============================================================================
class EventoGol : public Evento {
    int fraseIdx; // índice sorteado no construtor para descrição estável

public:
    EventoGol(int min, Time* t)
        : Evento(min, t), fraseIdx(rand() % 6) {}

    // As frases ficam como static local dentro do método — solução correta
    // para arrays constantes em arquivos de cabeçalho.
    std::string getDescricao() const override {
        static const char* frases[] = {
            "Golaco de fora da area!",
            "Cabeceio certeiro no angulo!",
            "Contra-ataque mortal!",
            "Chute colocado, sem chances para o goleiro!",
            "Ela entrou!",
            "Jogada individual genial!"
        };
        std::string desc = std::to_string(minuto) + "' [GOL] ";
        if (time) desc += time->getNome() + " - ";
        desc += frases[fraseIdx];
        return desc;
    }
};

// =============================================================================
// EventoCartaoAmarelo — registra uma advertência amarela.
// =============================================================================
class EventoCartaoAmarelo : public Evento {
    std::string nomeJogador;
    int         fraseIdx;

public:
    EventoCartaoAmarelo(int min, Time* t, const std::string& nome)
        : Evento(min, t), nomeJogador(nome), fraseIdx(rand() % 5) {}

    std::string getDescricao() const override {
        static const char* frases[] = {
            "Falta dura no meio-campo.",
            "Entrada atrasada.",
            "Protestou demais com o arbitro.",
            "Derrubou o adversario na area.",
            "Falta tatica para parar o contra-ataque."
        };
        std::string desc = std::to_string(minuto) + "' [AMARELO] ";
        if (time) desc += "[" + time->getSigla() + "] ";
        desc += nomeJogador + " - " + frases[fraseIdx];
        return desc;
    }
};

// =============================================================================
// EventoCartaoVermelho — registra uma expulsão.
// Além da narração, impacta o jogo: o time fica com um jogador a menos,
// e as forças por setor são recalculadas automaticamente no ContextoPartida.
// =============================================================================
class EventoCartaoVermelho : public Evento {
    std::string nomeJogador;
    int         fraseIdx;

public:
    EventoCartaoVermelho(int min, Time* t, const std::string& nome)
        : Evento(min, t), nomeJogador(nome), fraseIdx(rand() % 4) {}

    std::string getDescricao() const override {
        static const char* frases[] = {
            "Entrada violenta! Expulso!",
            "Vermelho direto - falta gravissima.",
            "Segundo amarelo, esta fora do jogo!",
            "Agrediu o adversario, sem apelacao!"
        };
        std::string desc = std::to_string(minuto) + "' [VERMELHO] ";
        if (time) desc += "[" + time->getSigla() + "] ";
        desc += nomeJogador + " - " + frases[fraseIdx];
        return desc;
    }
};

// =============================================================================
// EventoIntervalo — marca o fim do primeiro tempo com o placar parcial.
// =============================================================================
class EventoIntervalo : public Evento {
    int   golsCasa;
    int   golsVisit;
    Time* timeVisit;

public:
    EventoIntervalo(int gc, int gv, Time* casa, Time* visit)
        : Evento(45, casa), golsCasa(gc), golsVisit(gv), timeVisit(visit) {}

    std::string getDescricao() const override {
        std::string nomeCasa  = time      ? time->getNome()      : "?";
        std::string nomeVisit = timeVisit ? timeVisit->getNome() : "?";
        return "--- INTERVALO: " + nomeCasa + " " +
               std::to_string(golsCasa) + " x " +
               std::to_string(golsVisit) + " " + nomeVisit + " ---";
    }
};
