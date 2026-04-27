// =============================================================================
// Simulacao.cpp  —  Motor de simulação estilo FIFA do Manager FC.
//
// FLUXO DE simularPartida():
//   Para cada minuto (1 a 90 + acréscimos):
//     1. fator_fase  — multiplica P_gol conforme o momento do jogo
//     2. Intervalo   — registra placar do 1º tempo no minuto 45
//     3. Cartão VERMELHO — sorteia jogador ativo, verifica P_expulsao
//     4. Cartão AMARELO  — sorteia outro jogador, verifica prob menor
//     5. Gol         — calcula P_gol com fórmula do PDF × fator_fase
//
// POLIMORFISMO EM AÇÃO:
//   ContextoPartida chama calcularContribuicao() (virtual) em cada Jogador*
//   ativo — o C++ decide em tempo de execução se é Goleiro, Atacante etc.
//   Após uma expulsão, o setor afetado perde força automaticamente:
//   o próximo cálculo de P_gol já considera um jogador a menos.
// =============================================================================

#include "Simulacao.h"
#include "Evento.h"
#include "Formacoes.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

// Constante do algoritmo: calibrada para ~2.5 gols/partida em média.
static const float CONST_GOL = 2.9f;

// Helper: gera um float aleatório entre 0.0 e 1.0
static float randFloat() {
    return (rand() % 10000) / 10000.0f;
}

// =============================================================================
// calcularProbGol()
//
// Implementa a fórmula do algoritmo de simulação:
//   P_gol = CONST_GOL × fator_ataque / fator_defesa_adv   (em porcentagem)
//
// O modificador de formação é aplicado como bônus adicional, mantendo
// o sistema tático já existente.
//
// Retorna a probabilidade por minuto (0.0 a 1.0).
// =============================================================================
float Simulacao::calcularProbGol(const ContextoPartida& ctx,
                                  int ti, bool ehMandante) const {
    float fAtaque = ctx.calcularFatorAtaque(ti, ehMandante);

    // Adversário é o outro índice
    int  adversario    = (ti == ContextoPartida::CASA)
                          ? ContextoPartida::VISIT
                          : ContextoPartida::CASA;
    bool advEhMandante = (adversario == ContextoPartida::CASA);
    float fDefesaAdv   = ctx.calcularFatorDefesa(adversario, advEhMandante);

    if (fDefesaAdv < 0.001f) fDefesaAdv = 0.001f; // evita divisão por zero

    // Fórmula principal (resultado em porcentagem → dividir por 100)
    float pGol = (CONST_GOL * fAtaque / fDefesaAdv) / 100.0f;

    // Modificador tático: certas formações batem em outras (sistema original mantido)
    int mod = Formacoes::getModificador(
        ctx.getTime(ti)->getFormacao(),
        ctx.getTime(adversario)->getFormacao()
    );
    pGol *= (1.0f + mod / 100.0f);

    // Limites de sanidade
    if (pGol < 0.003f) pGol = 0.003f;
    if (pGol > 0.120f) pGol = 0.120f;

    return pGol;
}

// =============================================================================
// simularPartida()
//
// Loop minuto a minuto com eventos, fases do jogo e acréscimos.
// =============================================================================
void Simulacao::simularPartida(Partida& partida) {
    partida.setGolsCasa(0);
    partida.setGolsVisitante(0);

    // Contexto dinâmico: rastreia expulsões e calcula forças por setor
    ContextoPartida ctx(partida.getTimeCasa(), partida.getTimeVisitante());

    // Sorteia acréscimos (1 a 5 minutos)
    int acrescimos   = 1 + (rand() % 5);
    int totalMinutos = 90 + acrescimos;

    for (int minuto = 1; minuto <= totalMinutos; minuto++) {

        // -----------------------------------------------------------------
        // 1. FATOR DE FASE DO JOGO (3 momentos distintos)
        //    Times cautelosos no início, pressionando no fim.
        // -----------------------------------------------------------------
        float fatorFase;
        if      (minuto <= 15) fatorFase = 0.8f;  // início: cauteloso
        else if (minuto <= 75) fatorFase = 1.0f;  // meio: normal
        else                   fatorFase = 1.3f;  // final: pressão total

        // -----------------------------------------------------------------
        // 2. INTERVALO (minuto 45)
        // -----------------------------------------------------------------
        if (minuto == 45) {
            partida.addEvento(new EventoIntervalo(
                partida.getGolsCasa(),
                partida.getGolsVisitante(),
                partida.getTimeCasa(),
                partida.getTimeVisitante()
            ));
        }

        // -----------------------------------------------------------------
        // 3 e 4. CARTÕES — verificados para cada time por turno
        // -----------------------------------------------------------------
        for (int ti = 0; ti < 2; ti++) {
            Time* timeAtual = (ti == ContextoPartida::CASA)
                                ? partida.getTimeCasa()
                                : partida.getTimeVisitante();

            // --- CARTÃO VERMELHO ---
            // Mantém pelo menos 7 jogadores em campo (regra do futebol).
            if (ctx.jogadoresAtivos(ti) > 7) {
                int idx = ctx.sortearAtivo(ti);
                if (idx >= 0) {
                    float pVerm = ctx.getJogador(ti, idx)->getPExpulsao();
                    if (randFloat() < pVerm) {
                        // Expulsa: força do setor cai automaticamente
                        // no próximo cálculo de P_gol (ContextoPartida atualiza)
                        std::string nome = ctx.expulsar(ti, idx);
                        partida.addEvento(
                            new EventoCartaoVermelho(minuto, timeAtual, nome)
                        );
                    }
                }
            }

            // --- CARTÃO AMARELO (prob menor, jogador diferente) ---
            {
                int idx = ctx.sortearAtivo(ti);
                if (idx >= 0) {
                    float pAm = ctx.getJogador(ti, idx)->getPCartaoAmarelo();
                    if (randFloat() < pAm) {
                        std::string nome = ctx.getJogador(ti, idx)->getNome();
                        partida.addEvento(
                            new EventoCartaoAmarelo(minuto, timeAtual, nome)
                        );
                    }
                }
            }
        }

        // -----------------------------------------------------------------
        // 5. GOL — verificado para cada time
        // -----------------------------------------------------------------
        for (int ti = 0; ti < 2; ti++) {
            bool  ehCasa   = (ti == ContextoPartida::CASA);
            Time* timeAtual = ehCasa ? partida.getTimeCasa()
                                     : partida.getTimeVisitante();

            // P_gol usa forças por setor (com expulsões) × fator_fase
            float pGol = calcularProbGol(ctx, ti, ehCasa) * fatorFase;

            if (randFloat() < pGol) {
                if (ehCasa) partida.addGolCasa();
                else        partida.addGolVisitante();
                partida.addEvento(new EventoGol(minuto, timeAtual));
            }
        }
    }

    partida.setSimulada(true);

    // Atualiza estatísticas dos times no campeonato
    Time* casa  = partida.getTimeCasa();
    Time* visit = partida.getTimeVisitante();
    int   gc    = partida.getGolsCasa();
    int   gv    = partida.getGolsVisitante();

    if      (gc > gv) { casa->addVitoria();  visit->addDerrota(); }
    else if (gc < gv) { visit->addVitoria(); casa->addDerrota();  }
    else              { casa->addEmpate();   visit->addEmpate();  }

    casa->addGolsPro(gc);    casa->addGolsContra(gv);
    visit->addGolsPro(gv);   visit->addGolsContra(gc);
}

// =============================================================================
// exibirResultado() — placar final no terminal
// =============================================================================
void Simulacao::exibirResultado(const Partida& partida) const {
    std::cout << std::left
              << std::setw(22) << partida.getTimeCasa()->getNome()
              << partida.getGolsCasa() << " x " << partida.getGolsVisitante()
              << "  " << partida.getTimeVisitante()->getNome()
              << std::endl;
}

// =============================================================================
// exibirEventos() — log lance a lance de uma partida
//
// POLIMORFISMO: percorre LinkedList<Evento*> e chama getDescricao() em cada
// elemento. O C++ chama a versão correta (EventoGol, EventoCartaoVermelho...)
// sem nenhum if/switch de tipo — polimorfismo puro em tempo de execução.
// =============================================================================
void Simulacao::exibirEventos(const Partida& partida) const {
    partida.getEventos().forEach([](Evento* const& e) {
        std::cout << "  " << e->getDescricao() << std::endl;
    });
}
