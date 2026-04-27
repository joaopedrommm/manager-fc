#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Coritiba — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarCoritiba(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Pedro Morisco", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Pedro Rocha", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Bruno Melo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Maurício Antônio", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Maurício", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Henrique", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Alex Silva", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Bruno Melo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Zeca", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(10, "Filipe Machado", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Josué", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Sebá", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Geovane", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Wallisson", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Robson", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Lucas Ronier", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Iago Dias", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Dellatorre", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Gustavo Coutinho", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Clayson", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Lucas Ramon", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Hélio Borges", 70, 70, 70, 70));
}
