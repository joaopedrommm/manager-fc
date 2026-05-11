#include "Simulacao.h"
#include "ContextoPartida.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

// Sempre que usamos p. é um ponteiro que usamos para acessar Partida.h
// Sempre que usamos e. é um ponteiro que usamos para acessar Evento.h
// Sempre que usamos ctx. estamos referenciando uma probalidade contida no ContextoPartida.h

void Simulacao::simularPartida(Partida& p) {
    p.setGolsCasa(0);
    p.setGolsVisitante(0);

    //Referência para calcular as probabilidades de ContextoPartida.h com os times da partida
    ContextoPartida ctx(p.getTimeCasa(), p.getTimeVisitante());

    int acrescimos   = 1 + (rand() % 5);
    int duracaoTotal = 90 + acrescimos;
    
    // Algoritmo de simulação minuto a minuto
    for (int minuto = 1; minuto <= duracaoTotal; minuto++) {
        // Multiplicador da chance de gol de acordo com o momento do jogo
        float fatorFase;
        if      (minuto <= 15) fatorFase = 0.8f;
        else if (minuto <= 75) fatorFase = 1.0f;
        else                   fatorFase = 1.3f;

        if (minuto == 46)
            p.addEvento(new EventoIntervalo(45, p.getGolsCasa(), p.getGolsVisitante()));

        // Cartao Vermelho
        for (int t = 0; t < 2; t++) {
            Time*    time = (t == 0) ? p.getTimeCasa() : p.getTimeVisitante();
            Jogador* j    = ctx.getJogadorAleatorio(time);
            if (!j) continue;
            if ((rand() % 100000) / 100000.0f < j->getProbExpulsao()) {
                p.addEvento(new EventoCartaoVermelho(minuto, time, j->getNome()));
                ctx.expulsarJogador(time, j);
            }
        }

        // Cartao Amarelo 
        for (int t = 0; t < 2; t++) {
            Time*    time = (t == 0) ? p.getTimeCasa() : p.getTimeVisitante();
            Jogador* j    = ctx.getJogadorAleatorio(time);
            if (!j) continue;
            if ((rand() % 100000) / 100000.0f < j->getProbAmarelo()) {
                p.addEvento(new EventoCartaoAmarelo(minuto, time, j->getNome()));
            }
        }

        // Gol casa
        float probCasa = ctx.calcularProbGol(p.getTimeCasa(), p.getTimeVisitante())
                       * fatorFase * 1.10f;
        if ((rand() % 10000) / 10000.0f < probCasa) {
            Jogador* g   = ctx.getJogadorAleatorio(p.getTimeCasa());
            std::string n = g ? g->getNome() : "Jogador";
            p.addEvento(new EventoGol(minuto, p.getTimeCasa(), n));
            p.addGolCasa();
        }

        // Gol visitante
        float probVisit = ctx.calcularProbGol(p.getTimeVisitante(), p.getTimeCasa())
                        * fatorFase;
        if ((rand() % 10000) / 10000.0f < probVisit) {
            Jogador* g    = ctx.getJogadorAleatorio(p.getTimeVisitante());
            std::string n = g ? g->getNome() : "Jogador";
            p.addEvento(new EventoGol(minuto, p.getTimeVisitante(), n));
            p.addGolVisitante();
        }
    }

    p.setSimulada(true);

    // Lógica do placar final e atualização da tabela
    Time* casa  = p.getTimeCasa();
    Time* visit = p.getTimeVisitante();
    int gc = p.getGolsCasa(), gv = p.getGolsVisitante();

    if (gc > gv)      { casa->addVitoria();  visit->addDerrota(); }
    else if (gc < gv) { visit->addVitoria(); casa->addDerrota();  }
    else              { casa->addEmpate();   visit->addEmpate();  }

    casa->addGolsPro(gc);    casa->addGolsContra(gv);
    visit->addGolsPro(gv);   visit->addGolsContra(gc);
}

// Exibe o resultado final das outras partidas da rodada
void Simulacao::exibirResultado(const Partida& p) {
    std::cout << std::left
              << std::setw(22) << p.getTimeCasa()->getNome()
              << p.getGolsCasa() << " x " << p.getGolsVisitante()
              << "  " << p.getTimeVisitante()->getNome()
              << std::endl;
}


// Exibe os minutos do jogo em tempo real
void Simulacao::exibirPartidaAoVivo(const Partida& p) {
    int duracaoTotal = 90;
    p.getLog().forEach([&](Evento* const& e) {
        if (e->getMinuto() > duracaoTotal)
            duracaoTotal = e->getMinuto();
    });

    int acrescimos = duracaoTotal - 90;

    std::cout << "\n========================================" << std::endl;
    std::cout << "  " << p.getTimeCasa()->getNome()
              << "  vs  " << p.getTimeVisitante()->getNome() << std::endl;
    std::cout << "========================================\n" << std::endl;

    for (int minuto = 1; minuto <= duracaoTotal; minuto++) {

        // Aviso de acréscimos ao chegar no minuto 91
        if (minuto == 91) {
            std::cout << "\n  +++ " << acrescimos
                      << " minuto(s) de acrescimo! +++" << std::endl;
        }

        // Cada minuto em sua própria linha
        std::cout << std::right << std::setw(3) << minuto << "'";
        std::cout.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Verifica eventos nesse minuto
        bool temEvento = false;
        p.getLog().forEach([&](Evento* const& e) {
            if (e->getMinuto() != minuto) return;

            if (e->getTipo() == "INTERVALO") {
                std::cout << "\n" << std::endl;
                std::cout << "  --------- INTERVALO ---------" << std::endl;
                std::cout << "  " << e->getDescricao()         << std::endl;
                std::cout << "  ------------------------------\n" << std::endl;
            } else {
                std::cout << " >>> ";
                if      (e->getTipo() == "GOL")      std::cout << "[GOL]     ";
                else if (e->getTipo() == "AMARELO")  std::cout << "[AMARELO] ";
                else if (e->getTipo() == "VERMELHO") std::cout << "[VERMELHO]";

                if (e->getTime())
                    std::cout << " " << e->getTime()->getSigla() << " - ";

                std::cout << e->getDescricao();
            }
            temEvento = true;
        });

        // Sempre pula linha ao final do minuto (display vertical)
        std::cout << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "  RESULTADO FINAL: "
              << p.getTimeCasa()->getNome()     << " "
              << p.getGolsCasa()                << " x "
              << p.getGolsVisitante()           << " "
              << p.getTimeVisitante()->getNome() << std::endl;
    std::cout << "========================================" << std::endl;
}