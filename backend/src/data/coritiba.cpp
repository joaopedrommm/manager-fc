#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarCoritiba(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Gabriel", 72, 72, 72));
    time.adicionarJogador(new Defensor(2, "Natanael", 73, 73, 73, 73));
    time.adicionarJogador(new Defensor(3, "Henrique", 74, 74, 74, 74));
    time.adicionarJogador(new Defensor(4, "Thalisson", 72, 72, 72, 72));
    time.adicionarJogador(new Defensor(5, "Guilherme Biro", 71, 71, 71, 71));
    time.adicionarJogador(new Defensor(6, "Bruno Melo", 71, 71, 71, 71));
    time.adicionarJogador(new JogadorDeCampo(7, "Jesus Trindade", "VOL", 73, 73, 73, 73, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Robinho", "VOL", 72, 72, 72, 72, Agressividade::BAIXA));
    time.adicionarJogador(new JogadorDeCampo(9, "Andrey", "MEI", 73, 73, 73, 73, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Sebastiao Gomez", "MEI", 74, 74, 74, 74, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Mattheus Oliveira", "MEI", 72, 72, 72, 72, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Leo Gamalho", 73, 73, 73, 73));
    time.adicionarJogador(new Atacante(13, "Alef Manga", 74, 74, 74, 74));
    time.adicionarJogador(new Atacante(14, "Ivan Angulo", 73, 73, 73, 73));
    time.adicionarJogador(new Atacante(15, "Vini Dantas", 71, 71, 71, 71));
}
