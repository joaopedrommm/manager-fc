#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Athletico-PR — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarAthleticoPr(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Mycael", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Léo Linck", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Belezi", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Aguilar", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Habraão", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Léo Pereira", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Esquivel", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Léo Godoy", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Patrick", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(10, "Fernandinho", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Felipinho", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Christian", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Falcão", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Zapelli", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Raul", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Bruno Zapelli", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Julimar", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Luiz Fernando", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Mastriani", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Alan Kardec", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Dudu", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Renan Peixoto", 70, 70, 70, 70));
}
