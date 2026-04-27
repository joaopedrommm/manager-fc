#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Internacional — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarInternacional(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Sergio Rochet", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Anthoni", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Vitão", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Mercado", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Juninho", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Clayton Sampaio", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Aguirre", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Bruno Tabata", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Bernabei", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Ramon", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Fernando", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Thiago Maia", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Bruno Henrique", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Luis Otávio", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Alan Patrick", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Wesley", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(17, "Vitinho", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Borré", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Wanderson", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Carbonero", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Valencia", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Ricardo Mathias", 70, 70, 70, 70));
}
