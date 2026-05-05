#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarFluminense(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Fabio", 79, 79, 79));
    time.adicionarJogador(new Defensor(2, "Samuel Xavier", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(3, "Thiago Santos", 77, 77, 77, 77));
    time.adicionarJogador(new Defensor(4, "Thiago Silva", 82, 82, 82, 82));
    time.adicionarJogador(new Defensor(5, "Marcelo", 77, 77, 77, 77));
    time.adicionarJogador(new Defensor(6, "Diogo Barbosa", 76, 76, 76, 76));
    time.adicionarJogador(new JogadorDeCampo(7, "Lima", "VOL", 76, 76, 76, 76, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Paulo Baya", "VOL", 73, 73, 73, 73, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(9, "Martinelli", "MEI", 80, 80, 80, 80, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Jhon Arias", "MEI", 83, 83, 83, 83, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(11, "Ganso", "MEI", 78, 78, 78, 78, Agressividade::BAIXA));
    time.adicionarJogador(new Atacante(12, "Kaua Elias", 78, 78, 78, 78));
    time.adicionarJogador(new Atacante(13, "German Cano", 81, 81, 81, 81));
    time.adicionarJogador(new Atacante(14, "Serna", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(15, "Lele", 74, 74, 74, 74));
}
