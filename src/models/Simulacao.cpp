#include "Simulacao.h"
#include "Formacoes.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

// =============================================================================
// forcaEfetiva()
//
// Calcula a força efetiva de um time contra um adversário específico,
// levando em conta:
//   1. A força do elenco, calculada via polimorfismo (calcularForcaElenco)
//   2. O modificador tático entre as duas formações escolhidas
// =============================================================================
float Simulacao::forcaEfetiva(const Time* time, const Time* adversario) {
    // POLIMORFISMO EM AÇÃO: calcularForcaElenco() percorre o array de Jogador*
    // e chama calcularContribuicao() em cada um — Goleiro usa reflexos,
    // Atacante usa chute, Defensor usa habilidade... cada um do seu jeito.
    float forcaElenco = time->calcularForcaElenco();

    // Modificador tático: certas formações batem em outras
    int mod = Formacoes::getModificador(time->getFormacao(), adversario->getFormacao());

    return forcaElenco * (1.0f + mod / 100.0f);
}

// =============================================================================
// probGolPorMinuto()
//
// Calcula a probabilidade de um time marcar em um determinado minuto.
// Baseado na força relativa dos dois times.
// =============================================================================
float Simulacao::probGolPorMinuto(const Time* atacante, const Time* defensor) {
    float fAtacante = forcaEfetiva(atacante, defensor);
    float fDefensor = forcaEfetiva(defensor, atacante);
    float forcaRel  = fAtacante / (fAtacante + fDefensor);

    // Calibrado para uma média de ~2.8 gols/partida no Brasileirão
    float prob = 0.01556f * (forcaRel / 0.5f);

    // Limita para evitar resultados absurdos
    if (prob < 0.004f) prob = 0.004f;
    if (prob > 0.055f) prob = 0.055f;

    return prob;
}

// =============================================================================
// simularPartida()
//
// Simula os 90 minutos de uma partida, minuto a minuto.
// Cada minuto tem uma chance de gol para cada time (aleatoriedade controlada).
// Ao final, atualiza as estatísticas dos dois times.
// =============================================================================
void Simulacao::simularPartida(Partida& p) {
    p.setGolsCasa(0);
    p.setGolsVisitante(0);

    for (int minuto = 1; minuto <= 90; minuto++) {
        // Sorteio para o time da casa
        float probCasa = probGolPorMinuto(p.getTimeCasa(), p.getTimeVisitante());
        float randCasa = (rand() % 10000) / 10000.0f;
        if (randCasa < probCasa) p.addGolCasa();

        // Sorteio para o time visitante
        float probVisit = probGolPorMinuto(p.getTimeVisitante(), p.getTimeCasa());
        float randVisit = (rand() % 10000) / 10000.0f;
        if (randVisit < probVisit) p.addGolVisitante();
    }

    p.setSimulada(true);

    // Atualiza estatísticas dos times
    Time* casa  = p.getTimeCasa();
    Time* visit = p.getTimeVisitante();
    int gc = p.getGolsCasa(), gv = p.getGolsVisitante();

    if (gc > gv)      { casa->addVitoria();  visit->addDerrota(); }
    else if (gc < gv) { visit->addVitoria(); casa->addDerrota();  }
    else              { casa->addEmpate();   visit->addEmpate();  }

    casa->addGolsPro(gc);     casa->addGolsContra(gv);
    visit->addGolsPro(gv);    visit->addGolsContra(gc);
}

// =============================================================================
// exibirResultado()
//
// Exibe no terminal o resultado de uma partida já simulada.
// =============================================================================
void Simulacao::exibirResultado(const Partida& p) {
    std::cout << std::left
              << std::setw(22) << p.getTimeCasa()->getNome()
              << p.getGolsCasa() << " x " << p.getGolsVisitante()
              << "  " << p.getTimeVisitante()->getNome()
              << std::endl;
}
