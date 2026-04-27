#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Mirassol — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarMirassol(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Walter", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Muralha", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "João Victor", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Reinaldo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Lucas Ramon", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Daniel Borges", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(7, "Yuri", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(8, "Neto Moura", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(9, "Danielzinho", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(10, "Gabriel", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Chico da Costa", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(12, "Iury Castilho", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(13, "Cristian", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(14, "Reinaldo Mineiro", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Fernandinho", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(16, "Edson Carioca", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Negueba", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Renato Marques", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(19, "Camilo", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(20, "Felipe Jonatan", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Léo Gamalho", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(22, "Paulo Vitor", 70, 70, 70, 70));
}
