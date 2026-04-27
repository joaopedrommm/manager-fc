#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Fluminense — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarFluminense(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Fábio", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Vitor Eudes", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Thiago Silva", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Ignácio", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Manoel", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Thiago Santos", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Samuel Xavier", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Guga", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Renê", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Fuentes", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Hércules", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Martinelli", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Bernal", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Lima", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Ganso", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Nonato", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Arias", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Keno", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "John Kennedy", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Kauã Elias", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Cano", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Canobbio", 70, 70, 70, 70));
}
