#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Cruzeiro — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarCruzeiro(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Cássio", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Léo Aragão", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Villalba", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Fabrício Bruno", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "João Marcelo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Jonathan Jesus", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "William", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Marlon", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Kaiki", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(10, "Lucas Romero", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Walace", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Matheus Henrique", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Christian", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Eduardo", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Matheus Pereira", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(16, "Wanderson", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Gabigol", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Kaio Jorge", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Bolasie", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Lautaro Díaz", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Sinisterra", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(22, "Fagner", 70, 70, 70, 70));
}
