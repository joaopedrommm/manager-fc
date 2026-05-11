#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarCruzeiro(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Cassio", 80, 80, 80));
    time.adicionarJogador(new Defensor(2, "William", 75, 75, 75, 75));
    time.adicionarJogador(new Defensor(3, "Ze Ivaldo", 78, 78, 78, 78));
    time.adicionarJogador(new Defensor(4, "Joao Marcelo", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(5, "Marlon", 74, 74, 74, 74));
    time.adicionarJogador(new Defensor(6, "Kaiki Bruno", 73, 73, 73, 73));
    time.adicionarJogador(new JogadorDeCampo(7, "Lucas Silva", "VOL", 74, 74, 74, 74, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Walace", "VOL", 76, 76, 76, 76, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Matheus Henrique", "MEI", 79, 79, 79, 79, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Alvaro Barreal", "MEI", 78, 78, 78, 78, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Ramiro", "MEI", 73, 73, 73, 73, Agressividade::ALTA));
    time.adicionarJogador(new Atacante(12, "Gabigol", 83, 83, 83, 83));
    time.adicionarJogador(new Atacante(13, "Arthur Gomes", 75, 75, 75, 75));
    time.adicionarJogador(new Atacante(14, "Mateus Vital", 75, 75, 75, 75));
    time.adicionarJogador(new Atacante(15, "Lautaro Diaz", 75, 75, 75, 75));
}
