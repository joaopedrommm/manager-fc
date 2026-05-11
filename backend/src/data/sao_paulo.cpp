#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarSaoPaulo(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Rafael", 81, 81, 81));
    time.adicionarJogador(new Defensor(2, "Igor Vinicius", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(3, "Arboleda", 80, 80, 80, 80));
    time.adicionarJogador(new Defensor(4, "Alan Franco", 78, 78, 78, 78));
    time.adicionarJogador(new Defensor(5, "Welington", 78, 78, 78, 78));
    time.adicionarJogador(new Defensor(6, "Ferraresi", 77, 77, 77, 77));
    time.adicionarJogador(new JogadorDeCampo(7, "Alisson", "VOL", 77, 77, 77, 77, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(8, "Bobadilla", "VOL", 78, 78, 78, 78, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Lucas Moura", "MEI", 80, 80, 80, 80, Agressividade::BAIXA));
    time.adicionarJogador(new JogadorDeCampo(10, "Pablo Maia", "MEI", 79, 79, 79, 79, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Rodrigo Nestor", "MEI", 75, 75, 75, 75, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Calleri", 82, 82, 82, 82));
    time.adicionarJogador(new Atacante(13, "Luciano", 79, 79, 79, 79));
    time.adicionarJogador(new Atacante(14, "Wellington Rato", 77, 77, 77, 77));
    time.adicionarJogador(new Atacante(15, "Ferreirinha", 78, 78, 78, 78));
}
