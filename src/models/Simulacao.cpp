#include "Simulacao.h"
#include "Formacoes.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

// -----------------------------------------------------------------------
// Calcula a forca efetiva de um time considerando o modificador tático
// -----------------------------------------------------------------------
static float forcaEfetiva(const Time* time, const Time* adversario) {
    int mod = getModificador(time->formacao, adversario->formacao);
    return time->forca * (1.0f + mod / 100.0f);
}

// -----------------------------------------------------------------------
// Probabilidade de gol por minuto para um time
//
// Lógica:
//   - Base global calibrada para média ~2.8 gols/partida no total
//   - Cada time contribui com metade: ~1.4 gols esperados por time
//   - probBase = 1.4 / 90 ≈ 0.01556 para um time de forca 75 (media)
//   - A forca efetiva escala linearmente em torno da forca media (75)
//   - Times mais fortes que o adversario têm prob maior, e vice-versa
//
// forcaRel: razao entre forca efetiva do atacante e a soma das duas forcas
//   → se igual = 0.5 (equilíbrio), se muito superior → tende a 1.0
// -----------------------------------------------------------------------
static float probGolPorMinuto(const Time* atacante, const Time* defensor) {
    float fAtacante = forcaEfetiva(atacante, defensor);
    float fDefensor = forcaEfetiva(defensor, atacante);

    float forcaRel = fAtacante / (fAtacante + fDefensor); // 0.0 a 1.0

    // Base calibrada: forca relativa 0.5 → prob ≈ 0.01556 (1.4 gols esperados)
    // Escala: dobrar a dominancia dobra aprox a probabilidade
    float probBase = 0.01556f;
    float prob = probBase * (forcaRel / 0.5f);

    // Limita para nao gerar placares absurdos
    if (prob < 0.004f) prob = 0.004f;
    if (prob > 0.055f) prob = 0.055f;

    return prob;
}

// -----------------------------------------------------------------------
// Motor principal: simula os 90 minutos da partida
// -----------------------------------------------------------------------
void simularPartida(Partida& p) {
    p.golsCasa      = 0;
    p.golsVisitante = 0;

    for (int minuto = 1; minuto <= 90; minuto++) {
        // Sorteia gol para o time da casa
        float probCasa = probGolPorMinuto(p.timeCasa, p.timeVisitante);
        float randCasa = (rand() % 10000) / 10000.0f;
        if (randCasa < probCasa) p.golsCasa++;

        // Sorteia gol para o visitante
        float probVisit = probGolPorMinuto(p.timeVisitante, p.timeCasa);
        float randVisit = (rand() % 10000) / 10000.0f;
        if (randVisit < probVisit) p.golsVisitante++;
    }

    p.simulada = true;

    // Atualiza estatísticas dos times
    if (p.golsCasa > p.golsVisitante) {
        p.timeCasa->vitorias++;
        p.timeCasa->pontos += 3;
        p.timeVisitante->derrotas++;
    } else if (p.golsCasa < p.golsVisitante) {
        p.timeVisitante->vitorias++;
        p.timeVisitante->pontos += 3;
        p.timeCasa->derrotas++;
    } else {
        p.timeCasa->empates++;
        p.timeCasa->pontos++;
        p.timeVisitante->empates++;
        p.timeVisitante->pontos++;
    }

    p.timeCasa->golsPro      += p.golsCasa;
    p.timeCasa->golsContra   += p.golsVisitante;
    p.timeVisitante->golsPro      += p.golsVisitante;
    p.timeVisitante->golsContra   += p.golsCasa;
}

// -----------------------------------------------------------------------
// Exibe resultado de uma partida
// -----------------------------------------------------------------------
void exibirResultado(const Partida& p) {
    std::cout << std::left
              << std::setw(22) << p.timeCasa->nome
              << p.golsCasa << " x " << p.golsVisitante
              << "  " << p.timeVisitante->nome
              << std::endl;
}