#include "Simulacao.h"
#include "Formacoes.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

float Simulacao::forcaEfetiva(const Time* time, const Time* adversario) {
    int mod = Formacoes::getModificador(time->getFormacao(), adversario->getFormacao());
    return time->getForca() * (1.0f + mod / 100.0f);
}

float Simulacao::probGolPorMinuto(const Time* atacante, const Time* defensor) {
    float fAtacante = forcaEfetiva(atacante, defensor);
    float fDefensor = forcaEfetiva(defensor, atacante);
    float forcaRel  = fAtacante / (fAtacante + fDefensor);
    float prob      = 0.01556f * (forcaRel / 0.5f);
    if (prob < 0.004f) prob = 0.004f;
    if (prob > 0.055f) prob = 0.055f;
    return prob;
}

void Simulacao::simularPartida(Partida& p) {
    p.setGolsCasa(0);
    p.setGolsVisitante(0);

    for (int minuto = 1; minuto <= 90; minuto++) {
        float probCasa  = probGolPorMinuto(p.getTimeCasa(), p.getTimeVisitante());
        float randCasa  = (rand() % 10000) / 10000.0f;
        if (randCasa < probCasa) p.addGolCasa();

        float probVisit = probGolPorMinuto(p.getTimeVisitante(), p.getTimeCasa());
        float randVisit = (rand() % 10000) / 10000.0f;
        if (randVisit < probVisit) p.addGolVisitante();
    }

    p.setSimulada(true);

    Time* casa  = p.getTimeCasa();
    Time* visit = p.getTimeVisitante();
    int gc = p.getGolsCasa(), gv = p.getGolsVisitante();

    if (gc > gv)      { casa->addVitoria();  visit->addDerrota(); }
    else if (gc < gv) { visit->addVitoria(); casa->addDerrota();  }
    else              { casa->addEmpate();   visit->addEmpate();  }

    casa->addGolsPro(gc);     casa->addGolsContra(gv);
    visit->addGolsPro(gv);    visit->addGolsContra(gc);
}

void Simulacao::exibirResultado(const Partida& p) {
    std::cout << std::left
              << std::setw(22) << p.getTimeCasa()->getNome()
              << p.getGolsCasa() << " x " << p.getGolsVisitante()
              << "  " << p.getTimeVisitante()->getNome()
              << std::endl;
}