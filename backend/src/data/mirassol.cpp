#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarMirassol(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Alex Muralha", 73, 73, 73));
    time.adicionarJogador(new Defensor(2, "Luis Otavio", 72, 72, 72, 72));
    time.adicionarJogador(new Defensor(3, "Caetano", 71, 71, 71, 71));
    time.adicionarJogador(new Defensor(4, "Thalisson Kelven", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Warley", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Daniel Felipe", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(7, "Neto Moura", "VOL", 73, 73, 73, 73, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Dalberto", "VOL", 70, 70, 70, 70, Agressividade::BAIXA));
    time.adicionarJogador(new JogadorDeCampo(9, "Danielzinho", "MEI", 75, 75, 75, 75, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Chico Kim", "MEI", 74, 74, 74, 74, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Fabricio Daniel", "MEI", 72, 72, 72, 72, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Iury Castilho", 76, 76, 76, 76));
    time.adicionarJogador(new Atacante(13, "Elvinho", 73, 73, 73, 73));
    time.adicionarJogador(new Atacante(14, "Gabriel Silva", 72, 72, 72, 72));
    time.adicionarJogador(new Atacante(15, "Paulo Sergio", 71, 71, 71, 71));
}
