#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Flamengo — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarFlamengo(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Rossi", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Agustín Rossi", 70, 70, 70));
    time.adicionarJogador(new Goleiro(3, "Matheus Cunha", 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Léo Ortiz", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Léo Pereira", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Danilo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Alex Sandro", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Ayrton Lucas", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Varela", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Wesley", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Pulgar", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Allan", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Jorginho", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "De La Cruz", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Saúl", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Arrascaeta", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Everton Cebolinha", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Bruno Henrique", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Luiz Araújo", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Pedro", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Gonzalo Plata", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(22, "Carrascal", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(23, "Juninho", 70, 70, 70, 70));
}
