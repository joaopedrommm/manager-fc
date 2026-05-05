#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarGremio(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Gabriel Grando", 76, 76, 76));
    time.adicionarJogador(new Defensor(2, "Joao Pedro", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(3, "Kannemann", 79, 79, 79, 79));
    time.adicionarJogador(new Defensor(4, "Gustavo Martins", 77, 77, 77, 77));
    time.adicionarJogador(new Defensor(5, "Reinaldo", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(6, "Mayk", 73, 73, 73, 73));
    time.adicionarJogador(new JogadorDeCampo(7, "Villasanti", "VOL", 79, 79, 79, 79, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Edenilson", "VOL", 76, 76, 76, 76, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Pepe", "MEI", 81, 81, 81, 81, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Cristaldo", "MEI", 82, 82, 82, 82, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Du Queiroz", "MEI", 74, 74, 74, 74, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Braithwaite", 79, 79, 79, 79));
    time.adicionarJogador(new Atacante(13, "Everton Galdino", 77, 77, 77, 77));
    time.adicionarJogador(new Atacante(14, "Diego Costa", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(15, "Nathan Fernandes", 74, 74, 74, 74));
}
