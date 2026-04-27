#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do São Paulo — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarSaoPaulo(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Rafael", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Young", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Arboleda", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Alan Franco", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Ferraresi", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Sabino", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Cédric", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Wendell", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Enzo Díaz", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Maik", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Alisson", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Bobadilla", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Pablo Maia", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Marcos Antônio", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Oscar", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Lucas Moura", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(17, "Luciano", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(18, "Rodriguinho", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Ferreira", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "André Silva", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Calleri", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Juan", 70, 70, 70, 70));
}
