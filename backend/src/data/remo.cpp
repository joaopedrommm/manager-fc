#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Remo — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarRemo(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Marcelo Rangel", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Ygor Vinhas", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Klaus", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Kayky Almeida", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Reynaldo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Camutanga", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Marcelinho", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Sávio", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Igor Fernandes", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(10, "Pavani", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Jorge Henrique", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Caio Vinícius", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Ytalo", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Pedro Castro", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Janderson", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(16, "Felipe Vizeu", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Pedro Rocha", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Matheus Davó", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Dodô", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Adailton", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Echaporã", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Jaderson", 70, 70, 70, 70));
}
