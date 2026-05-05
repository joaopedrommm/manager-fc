#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarBahia(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Marcos Felipe", 76, 76, 76));
    time.adicionarJogador(new Defensor(2, "Gilberto", 75, 75, 75, 75));
    time.adicionarJogador(new Defensor(3, "Kanu", 77, 77, 77, 77));
    time.adicionarJogador(new Defensor(4, "Gabriel Xavier", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(5, "Santi Arias", 74, 74, 74, 74));
    time.adicionarJogador(new Defensor(6, "Iago", 73, 73, 73, 73));
    time.adicionarJogador(new JogadorDeCampo(7, "Caio Alexandre", "VOL", 77, 77, 77, 77, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(8, "Jean Lucas", "VOL", 76, 76, 76, 76, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(9, "Everton Ribeiro", "MEI", 79, 79, 79, 79, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Thaciano", "MEI", 75, 75, 75, 75, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(11, "Ademir", "MEI", 74, 74, 74, 74, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Everaldo", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(13, "Luciano Juba", 77, 77, 77, 77));
    time.adicionarJogador(new Atacante(14, "Biel", 75, 75, 75, 75));
    time.adicionarJogador(new Atacante(15, "Cauly", 78, 78, 78, 78));
}
