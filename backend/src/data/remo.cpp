#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarRemo(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Vinicius", 70, 70, 70));
    time.adicionarJogador(new Defensor(2, "Kevem", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Ramos Ligan", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Pablo Roberto", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Leonan", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Rafael Jansen", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(7, "Wallace Lobo", "VOL", 71, 71, 71, 71, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(8, "Savio", "VOL", 70, 70, 70, 70, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Rodrigo Pimpao", "MEI", 72, 72, 72, 72, Agressividade::BAIXA));
    time.adicionarJogador(new JogadorDeCampo(10, "Ronald", "MEI", 71, 71, 71, 71, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Eduardo Ramos", "MEI", 70, 70, 70, 70, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Brenner", 71, 71, 71, 71));
    time.adicionarJogador(new Atacante(13, "Erick Flores", 71, 71, 71, 71));
    time.adicionarJogador(new Atacante(14, "Marco Antonio", 71, 71, 71, 71));
    time.adicionarJogador(new Atacante(15, "Lucas Siqueira", 70, 70, 70, 70));
}
