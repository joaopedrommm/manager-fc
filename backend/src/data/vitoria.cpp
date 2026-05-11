#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarVitoria(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Lucas Arcanjo", 73, 73, 73));
    time.adicionarJogador(new Defensor(2, "Camutanga", 71, 71, 71, 71));
    time.adicionarJogador(new Defensor(3, "Wagner Leonardo", 74, 74, 74, 74));
    time.adicionarJogador(new Defensor(4, "Neris", 72, 72, 72, 72));
    time.adicionarJogador(new Defensor(5, "Lucas Esteves", 72, 72, 72, 72));
    time.adicionarJogador(new Defensor(6, "Willean Lepo", 73, 73, 73, 73));
    time.adicionarJogador(new JogadorDeCampo(7, "Luan", "VOL", 73, 73, 73, 73, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Caio Vinicius", "VOL", 72, 72, 72, 72, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(9, "Matheusinho", "MEI", 75, 75, 75, 75, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Leo Naldi", "MEI", 74, 74, 74, 74, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "PK", "MEI", 71, 71, 71, 71, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Janderson", 75, 75, 75, 75));
    time.adicionarJogador(new Atacante(13, "Osvaldo", 73, 73, 73, 73));
    time.adicionarJogador(new Atacante(14, "Alerrandro", 77, 77, 77, 77));
    time.adicionarJogador(new Atacante(15, "Ze Hugo", 72, 72, 72, 72));
}
