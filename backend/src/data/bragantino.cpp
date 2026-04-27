#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Bragantino — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarBragantino(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Cleiton", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Lucão", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Léo Ortiz", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Eduardo Santos", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Pedro Henrique", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Andrés Hurtado", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Guilherme Lopes", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Juninho Capixaba", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Nathan Mendes", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(10, "Lucas Evangelista", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Matheus Fernandes", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Praxedes", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Eric Ramires", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Jadsom Silva", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Lucas Barbosa", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Vinicinho", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Helinho", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Eduardo Sasha", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Vitinho", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Thiago Borbas", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Laquintana", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Mosquera", 70, 70, 70, 70));
}
