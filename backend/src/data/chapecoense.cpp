#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarChapecoense(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Joao Carlos", 71, 71, 71));
    time.adicionarJogador(new Defensor(2, "Ruan", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Dirceu", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Anderson", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Jonathan Cafu", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Felipe", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(7, "Indio", "VOL", 71, 71, 71, 71, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Bovio", "VOL", 70, 70, 70, 70, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(9, "Moises", "MEI", 72, 72, 72, 72, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Perotti", "MEI", 72, 72, 72, 72, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Guilherme Poague", "MEI", 71, 71, 71, 71, Agressividade::BAIXA));
    time.adicionarJogador(new Atacante(12, "Anselmo Ramon", 74, 74, 74, 74));
    time.adicionarJogador(new Atacante(13, "Mike", 72, 72, 72, 72));
    time.adicionarJogador(new Atacante(14, "Marquinhos Gabriel", 71, 71, 71, 71));
    time.adicionarJogador(new Atacante(15, "Perri", 70, 70, 70, 70));
}
