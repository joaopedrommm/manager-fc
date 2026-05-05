#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarSantos(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Joao Paulo", 79, 79, 79));
    time.adicionarJogador(new Defensor(2, "Escobar", 74, 74, 74, 74));
    time.adicionarJogador(new Defensor(3, "Gil", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(4, "Messias", 73, 73, 73, 73));
    time.adicionarJogador(new Defensor(5, "Joao Basso", 73, 73, 73, 73));
    time.adicionarJogador(new Defensor(6, "Kevyson", 72, 72, 72, 72));
    time.adicionarJogador(new JogadorDeCampo(7, "Diego Pituca", "VOL", 77, 77, 77, 77, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Giuliano", "VOL", 75, 75, 75, 75, Agressividade::BAIXA));
    time.adicionarJogador(new JogadorDeCampo(9, "Soteldo", "MEI", 79, 79, 79, 79, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Sandry", "MEI", 76, 76, 76, 76, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Miguelito", "MEI", 74, 74, 74, 74, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Furch", 75, 75, 75, 75));
    time.adicionarJogador(new Atacante(13, "Guilherme", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(14, "Lucas Barbosa", 73, 73, 73, 73));
    time.adicionarJogador(new Atacante(15, "Willian Bigode", 73, 73, 73, 73));
}
