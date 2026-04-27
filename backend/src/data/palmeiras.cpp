#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Palmeiras — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarPalmeiras(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Weverton", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Carlos Miguel", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Gustavo Gómez", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Murilo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Bruno Fuchs", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Micael", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Piquerez", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Marcos Rocha", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Mayke", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Khellven", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Aníbal Moreno", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Lucas Evangelista", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Emiliano Martínez", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Raphael Veiga", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Maurício", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Felipe Anderson", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(17, "Allan", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Estêvão", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Vitor Roque", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Flaco López", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Bruno Rodrigues", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Facundo Torres", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(23, "Paulinho", 70, 70, 70, 70));
}
