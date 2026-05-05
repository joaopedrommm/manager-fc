#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarBragantino(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Cleiton", 80, 80, 80));
    time.adicionarJogador(new Defensor(2, "Andres Hurtado", 75, 75, 75, 75));
    time.adicionarJogador(new Defensor(3, "Eduardo Santos", 74, 74, 74, 74));
    time.adicionarJogador(new Defensor(4, "Pedro Henrique", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(5, "Juninho Capixaba", 75, 75, 75, 75));
    time.adicionarJogador(new Defensor(6, "Nathan Mendes", 73, 73, 73, 73));
    time.adicionarJogador(new JogadorDeCampo(7, "Eric Ramires", "VOL", 76, 76, 76, 76, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Lincoln", "VOL", 75, 75, 75, 75, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Jhon Jhon", "MEI", 77, 77, 77, 77, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Lucas Evangelista", "MEI", 77, 77, 77, 77, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Gustavinho", "MEI", 73, 73, 73, 73, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Vinicinho", 78, 78, 78, 78));
    time.adicionarJogador(new Atacante(13, "Henry Mosquera", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(14, "Eduardo Sasha", 75, 75, 75, 75));
    time.adicionarJogador(new Atacante(15, "Helinho", 77, 77, 77, 77));
}
