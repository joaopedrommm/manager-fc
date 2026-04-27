#pragma once
#include <cstdlib>   // rand()
#include "Time.h"
#include "Jogador.h"

// =============================================================================
// ContextoPartida.h  —  Estado dinâmico de uma partida em andamento.
//
// CONCEITO OOP: ENCAPSULAMENTO + POLIMORFISMO
//   Esta classe encapsula tudo que muda durante os 90 minutos:
//   quais jogadores foram expulsos e, portanto, quais setores do time
//   ficaram enfraquecidos.
//
//   O cálculo de força usa calcularContribuicao() (virtual) em cada Jogador*
//   ativo — o C++ chama a versão correta (Goleiro, Atacante, Defensor)
//   automaticamente. Isso é polimorfismo influenciando o resultado do jogo.
//
// Responsabilidades:
//   1. Rastrear jogadores expulsos por índice e time.
//   2. Calcular fator_ataque e fator_defesa conforme fórmula do algoritmo.
//   3. Sortear jogadores ativos para verificação de cartões.
//
// Índices dos times:
//   ContextoPartida::CASA  = 0
//   ContextoPartida::VISIT = 1
// =============================================================================

class ContextoPartida {
public:
    static const int CASA  = 0;
    static const int VISIT = 1;

private:
    const Time* times[2];           // ponteiros para os dois times
    bool expulso[2][TAM_ELENCO];    // expulso[timeIdx][jogadorIdx]

    // -------------------------------------------------------------------------
    // Soma calcularContribuicao(100) de todos os jogadores ATIVOS de um setor.
    //
    // POLIMORFISMO: percorre array de Jogador*, chama calcularContribuicao()
    // em cada um. O método virtual correto (Goleiro, Atacante, Defensor...)
    // é escolhido em tempo de execução — sem nenhum if/else de tipo.
    //
    // pos1, pos2: strings de posição que definem o setor
    //   ex.: "ATA", "" para atacantes
    //        "ZAG", "LAT" para defesa
    //        "VOL", "MEI" para meio
    // -------------------------------------------------------------------------
    float somaPorSetor(int ti, const std::string& pos1,
                       const std::string& pos2 = "") const {
        const Time* t = times[ti];
        float soma = 0.0f;
        for (int i = 0; i < t->getNumJogadores(); i++) {
            if (expulso[ti][i]) continue;
            const Jogador* j = t->getJogador(i);
            const std::string& pos = j->getPosicao();
            if (pos == pos1 || (!pos2.empty() && pos == pos2))
                soma += j->calcularContribuicao(100.0f);
        }
        return soma;
    }

    // Retorna a contribuição do goleiro ativo, ou 0 se estiver expulso.
    float forcaGoleiro(int ti) const {
        const Time* t = times[ti];
        for (int i = 0; i < t->getNumJogadores(); i++) {
            if (expulso[ti][i]) continue;
            const Jogador* j = t->getJogador(i);
            if (j->getPosicao() == "GOL")
                return j->calcularContribuicao(100.0f);
        }
        return 0.0f; // goleiro expulso — situação rara mas tratada
    }

public:
    // -------------------------------------------------------------------------
    // Construtor: inicializa o contexto com os dois times e nenhum expulso.
    // -------------------------------------------------------------------------
    ContextoPartida(const Time* casa, const Time* visit) {
        times[CASA]  = casa;
        times[VISIT] = visit;
        for (int t = 0; t < 2; t++)
            for (int i = 0; i < TAM_ELENCO; i++)
                expulso[t][i] = false;
    }

    // -------------------------------------------------------------------------
    // sortearAtivo: retorna o ÍNDICE de um jogador ativo aleatório do time ti.
    // Retorna -1 se não houver nenhum.
    // Usado em Simulacao.cpp para escolher quem é verificado para cartão.
    // -------------------------------------------------------------------------
    int sortearAtivo(int ti) const {
        const Time* t = times[ti];
        int candidatos[TAM_ELENCO];
        int n = 0;
        for (int i = 0; i < t->getNumJogadores(); i++)
            if (!expulso[ti][i]) candidatos[n++] = i;
        if (n == 0) return -1;
        return candidatos[rand() % n];
    }

    // -------------------------------------------------------------------------
    // expulsar: marca o jogador no índice idx como expulso.
    // Retorna o nome do jogador expulso (para exibir no evento).
    // O recálculo das forças é automático: somaPorSetor() já ignora expulsos.
    // -------------------------------------------------------------------------
    std::string expulsar(int ti, int idx) {
        expulso[ti][idx] = true;
        return times[ti]->getJogador(idx)->getNome();
    }

    // Acesso somente-leitura a um jogador pelo índice (para pegar atributos).
    const Jogador* getJogador(int ti, int idx) const {
        return times[ti]->getJogador(idx);
    }

    // Acesso ao time (para pegar formação, nome etc.)
    const Time* getTime(int ti) const { return times[ti]; }

    // Quantidade de jogadores ainda em campo para o time ti.
    int jogadoresAtivos(int ti) const {
        int count = 0;
        for (int i = 0; i < times[ti]->getNumJogadores(); i++)
            if (!expulso[ti][i]) count++;
        return count;
    }

    // -------------------------------------------------------------------------
    // calcularFatorAtaque — fórmula do algoritmo de simulação:
    //   fator_ataque = (forca_ataque * 0.40 + forca_meio * 0.20) / 10
    //
    // ehMandante: aplica bônus de 10% de vantagem em casa.
    // -------------------------------------------------------------------------
    float calcularFatorAtaque(int ti, bool ehMandante) const {
        float fAtaque = somaPorSetor(ti, "ATA");
        float fMeio   = somaPorSetor(ti, "VOL", "MEI");
        float fator   = (fAtaque * 0.40f + fMeio * 0.20f) / 10.0f;
        if (ehMandante) fator *= 1.10f;
        return fator;
    }

    // -------------------------------------------------------------------------
    // calcularFatorDefesa — fórmula do algoritmo de simulação:
    //   fator_defesa = (forca_defesa * 0.30 + forca_meio * 0.15) / 10
    //                + forca_goleiro * 0.15
    //
    // O goleiro tem peso direto na defesa (sem divisão por 10).
    // -------------------------------------------------------------------------
    float calcularFatorDefesa(int ti, bool ehMandante) const {
        float fDefesa  = somaPorSetor(ti, "ZAG", "LAT");
        float fMeio    = somaPorSetor(ti, "VOL", "MEI");
        float fGoleiro = forcaGoleiro(ti);
        float fator    = (fDefesa * 0.30f + fMeio * 0.15f) / 10.0f
                        + fGoleiro * 0.15f;
        if (ehMandante) fator *= 1.10f;
        return fator;
    }
};
