#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarInternacional(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Rochet", 83, 83, 83));
    time.adicionarJogador(new Defensor(2, "Bustos", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(3, "Mercado", 75, 75, 75, 75));
    time.adicionarJogador(new Defensor(4, "Vitao", 78, 78, 78, 78));
    time.adicionarJogador(new Defensor(5, "Rene", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(6, "Robert Renan", 77, 77, 77, 77));
    time.adicionarJogador(new JogadorDeCampo(7, "Thiago Maia", "VOL", 77, 77, 77, 77, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Bruno Henrique", "VOL", 77, 77, 77, 77, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Fernando", "MEI", 79, 79, 79, 79, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Alan Patrick", "MEI", 81, 81, 81, 81, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Carlos de Pena", "MEI", 75, 75, 75, 75, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Enner Valencia", 79, 79, 79, 79));
    time.adicionarJogador(new Atacante(13, "Rafael Borre", 80, 80, 80, 80));
    time.adicionarJogador(new Atacante(14, "Wanderson", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(15, "Alario", 73, 73, 73, 73));
}
