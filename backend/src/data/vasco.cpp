#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarVasco(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Leo Jardim", 77, 77, 77));
    time.adicionarJogador(new Defensor(2, "Paulo Henrique", 73, 73, 73, 73));
    time.adicionarJogador(new Defensor(3, "Maicon", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(4, "Joao Victor", 77, 77, 77, 77));
    time.adicionarJogador(new Defensor(5, "Lucas Piton", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(6, "Puma Rodriguez", 75, 75, 75, 75));
    time.adicionarJogador(new JogadorDeCampo(7, "Hugo Moura", "VOL", 74, 74, 74, 74, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "JP", "VOL", 73, 73, 73, 73, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(9, "Matheus Carvalho", "MEI", 74, 74, 74, 74, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Sforza", "MEI", 75, 75, 75, 75, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Payet", "MEI", 77, 77, 77, 77, Agressividade::BAIXA));
    time.adicionarJogador(new Atacante(12, "Vegetti", 82, 82, 82, 82));
    time.adicionarJogador(new Atacante(13, "David", 77, 77, 77, 77));
    time.adicionarJogador(new Atacante(14, "Rayan", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(15, "GB", 73, 73, 73, 73));
}
