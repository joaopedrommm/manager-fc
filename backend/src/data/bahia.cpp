#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Bahia — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarBahia(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Marcos Felipe", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Ronaldo", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Kanu", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Gabriel Xavier", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Ramos Mingo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "David Duarte", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Santiago Arias", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Gilberto", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Iago Borduchi", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Luciano Juba", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Jean Lucas", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Acevedo", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Caio Alexandre", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Cauly", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Everton Ribeiro", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Rodrigo Nestor", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Erick Pulga", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Lucho Rodríguez", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Willian José", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Ademir", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Tiago", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(22, "Michel Araújo", "MEI", 70, 70, 70, 70));
}
