#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarAthleticoPr(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Mycael", 76, 76, 76));
    time.adicionarJogador(new Defensor(2, "Madson", 74, 74, 74, 74));
    time.adicionarJogador(new Defensor(3, "Kaique Rocha", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(4, "Matheus Felipe", 75, 75, 75, 75));
    time.adicionarJogador(new Defensor(5, "Esquivel", 74, 74, 74, 74));
    time.adicionarJogador(new Defensor(6, "Orejuela", 73, 73, 73, 73));
    time.adicionarJogador(new JogadorDeCampo(7, "Fernandinho", "VOL", 79, 79, 79, 79, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Erick", "VOL", 75, 75, 75, 75, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Christian", "MEI", 78, 78, 78, 78, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Canobbio", "MEI", 80, 80, 80, 80, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Leo Cittadini", "MEI", 74, 74, 74, 74, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Vitinho", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(13, "Mastriani", 75, 75, 75, 75));
    time.adicionarJogador(new Atacante(14, "Di Yorio", 74, 74, 74, 74));
    time.adicionarJogador(new Atacante(15, "Romulo", 74, 74, 74, 74));
}
