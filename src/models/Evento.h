#pragma once
#include <string>
#include <cstdlib>

class Time;

class Evento {
protected:
    int   minuto;
    Time* time;
public:
    Evento(int minuto, Time* time) : minuto(minuto), time(time) {}
    virtual ~Evento() {}

    virtual std::string getDescricao() const = 0;
    virtual std::string getTipo()      const = 0;

    int   getMinuto() const { return minuto; }
    Time* getTime()   const { return time; }
};

class EventoGol : public Evento {
private:
    std::string nomeJogador;
public:
    EventoGol(int minuto, Time* time, const std::string& nomeJogador)
        : Evento(minuto, time), nomeJogador(nomeJogador) {}

    std::string getTipo() const override { return "GOL"; }

    std::string getDescricao() const override {
        const char* frases[] = {
            "Que golaco!",
            "Chute certeiro no canto!",
            "Cabecada no angulo!",
            "Bomba de fora da area!",
            "Toque preciso e bola nas redes!",
            "Penalti convertido com categoria!",
            "Jogada individual e gol!"
        };
        return nomeJogador + " marca! " + frases[rand() % 7];
    }
};

class EventoCartaoAmarelo : public Evento {
private:
    std::string nomeJogador;
public:
    EventoCartaoAmarelo(int minuto, Time* time, const std::string& nomeJogador)
        : Evento(minuto, time), nomeJogador(nomeJogador) {}

    std::string getTipo() const override { return "AMARELO"; }

    std::string getDescricao() const override {
        const char* frases[] = {
            "Entrada atrasada.",
            "Reclamacao com o arbitro.",
            "Falta dura no meio-campo.",
            "Cotovelada punida.",
            "Simulacao detectada pelo arbitro."
        };
        return nomeJogador + " - cartao amarelo. " + frases[rand() % 5];
    }
};

class EventoCartaoVermelho : public Evento {
private:
    std::string nomeJogador;
public:
    EventoCartaoVermelho(int minuto, Time* time, const std::string& nomeJogador)
        : Evento(minuto, time), nomeJogador(nomeJogador) {}

    std::string getTipo() const override { return "VERMELHO"; }

    std::string getDescricao() const override {
        const char* frases[] = {
            "Entrada violenta - expulso de campo!",
            "Segundo amarelo - tchau!",
            "Falta brutal - cartao vermelho direto!",
            "Discussao com o arbitro - expulso!"
        };
        return nomeJogador + " EXPULSO! " + frases[rand() % 4];
    }
};

class EventoIntervalo : public Evento {
private:
    int golsCasa;
    int golsVisitante;
public:
    EventoIntervalo(int minuto, int golsCasa, int golsVisitante)
        : Evento(minuto, nullptr), golsCasa(golsCasa), golsVisitante(golsVisitante) {}

    std::string getTipo() const override { return "INTERVALO"; }

    std::string getDescricao() const override {
        return "Placar parcial: " + std::to_string(golsCasa)
             + " x " + std::to_string(golsVisitante);
    }
};