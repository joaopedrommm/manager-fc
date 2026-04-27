#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Atlético-MG — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarAtleticoMg(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Everson", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Gabriel Delfim", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Lyanco", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Junior Alonso", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Vitor Hugo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Bruno Fuchs", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Saravia", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Natanael", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Guilherme Arana", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Caio Maia", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Otávio", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Igor Gomes", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Alan Franco", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Fausto Vera", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Alexsander", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Bernard", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(17, "Gustavo Scarpa", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Rony", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Hulk", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Cuello", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Cristian Pavón", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Biel", 70, 70, 70, 70));
}
