#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Santos — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarSantos(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Brazão", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "João Paulo", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Zé Ivaldo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Luan Peres", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Adonis Frias", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "João Basso", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Aderlan", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Souza", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Escobar", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Kevyson", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "João Schmidt", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Tomás Rincón", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Diego Pituca", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Zé Rafael", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Rollheiser", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Gabriel Bontempo", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Lautaro Díaz", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Neymar", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Guilherme", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Barreal", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Tiquinho Soares", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Robinho Jr.", 70, 70, 70, 70));
}
