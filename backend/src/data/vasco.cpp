#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Vasco — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarVasco(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Léo Jardim", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Daniel Fuzato", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Lucas Freitas", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Robert Renan", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Maurício Lemos", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "João Victor", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Paulo Henrique", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Lucas Piton", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Puma Rodríguez", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Lucas Oliveira", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Hugo Moura", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Mateus Carvalho", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Jair", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Tchê Tchê", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Coutinho", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Payet", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(17, "David", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Nuno Moreira", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Vegetti", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Rayan", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "GB", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Jean David", 70, 70, 70, 70));
}
