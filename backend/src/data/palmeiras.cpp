#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarPalmeiras(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Weverton", 86, 86, 86));
    time.adicionarJogador(new Defensor(2, "Marcos Rocha", 78, 78, 78, 78));
    time.adicionarJogador(new Defensor(3, "Gustavo Gomez", 87, 87, 87, 87));
    time.adicionarJogador(new Defensor(4, "Murilo", 82, 82, 82, 82));
    time.adicionarJogador(new Defensor(5, "Piquerez", 82, 82, 82, 82));
    time.adicionarJogador(new Defensor(6, "Mayke", 77, 77, 77, 77));
    time.adicionarJogador(new JogadorDeCampo(7, "Ze Rafael", "VOL", 79, 79, 79, 79, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Atuesta", "VOL", 77, 77, 77, 77, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Raphael Veiga", "MEI", 86, 86, 86, 86, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Richard Rios", "MEI", 82, 82, 82, 82, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Gabriel Menino", "MEI", 80, 80, 80, 80, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Flaco Lopez", 83, 83, 83, 83));
    time.adicionarJogador(new Atacante(13, "Rony", 79, 79, 79, 79));
    time.adicionarJogador(new Atacante(14, "Mauricio", 80, 80, 80, 80));
    time.adicionarJogador(new Atacante(15, "Breno Lopes", 76, 76, 76, 76));
}
