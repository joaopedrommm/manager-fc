#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarAtleticoMg(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Everson", 83, 83, 83));
    time.adicionarJogador(new Defensor(2, "Saravia", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(3, "Junior Alonso", 80, 80, 80, 80));
    time.adicionarJogador(new Defensor(4, "Guilherme Arana", 81, 81, 81, 81));
    time.adicionarJogador(new Defensor(5, "Natan", 77, 77, 77, 77));
    time.adicionarJogador(new Defensor(6, "Mariano", 76, 76, 76, 76));
    time.adicionarJogador(new JogadorDeCampo(7, "Fausto Vera", "VOL", 78, 78, 78, 78, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Igor Gomes", "VOL", 76, 76, 76, 76, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(9, "Otavio", "MEI", 84, 84, 84, 84, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Gustavo Scarpa", "MEI", 80, 80, 80, 80, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Bernard", "MEI", 80, 80, 80, 80, Agressividade::BAIXA));
    time.adicionarJogador(new Atacante(12, "Paulinho", 85, 85, 85, 85));
    time.adicionarJogador(new Atacante(13, "Eduardo Vargas", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(14, "Cadu", 74, 74, 74, 74));
    time.adicionarJogador(new Atacante(15, "Palacios", 75, 75, 75, 75));
}
