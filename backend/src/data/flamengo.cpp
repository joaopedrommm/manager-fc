#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarFlamengo(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Agustin Rossi", 84, 84, 84));
    time.adicionarJogador(new Defensor(2, "Leo Ortiz", 82, 82, 82, 82));
    time.adicionarJogador(new Defensor(3, "Fabricio Bruno", 83, 83, 83, 83));
    time.adicionarJogador(new Defensor(4, "Leo Pereira", 81, 81, 81, 81));
    time.adicionarJogador(new Defensor(5, "Wesley", 79, 79, 79, 79));
    time.adicionarJogador(new Defensor(6, "Ayrton Lucas", 80, 80, 80, 80));
    time.adicionarJogador(new JogadorDeCampo(7, "Gerson", "VOL", 86, 86, 86, 86, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Erick Pulgar", "VOL", 78, 78, 78, 78, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Arrascaeta", "MEI", 88, 88, 88, 88, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "De la Cruz", "MEI", 84, 84, 84, 84, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Allan", "MEI", 76, 76, 76, 76, Agressividade::ALTA));
    time.adicionarJogador(new Atacante(12, "Pedro", 89, 89, 89, 89));
    time.adicionarJogador(new Atacante(13, "Everton Cebolinha", 82, 82, 82, 82));
    time.adicionarJogador(new Atacante(14, "Luiz Araujo", 80, 80, 80, 80));
    time.adicionarJogador(new Atacante(15, "Michael", 78, 78, 78, 78));
}
