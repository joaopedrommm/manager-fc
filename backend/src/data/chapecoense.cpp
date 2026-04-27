#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Chapecoense — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarChapecoense(Time& time) {
    time.adicionarJogador(new Goleiro(1, "João Paulo", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Léo Vieira", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Bruno Leonardo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Mancha", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Rafael Castro", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Wallace", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Maílton", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Eduardo Doma", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Victor Caetano", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(10, "Marcinho", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Walter Clar", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Giovanni Augusto", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Pedro Castro", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Eduardo", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Italo", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Perotti", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Mário Sérgio", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Neto Pessoa", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Ferrareis", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Ítalo", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Maranhão", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Rodrigo Vinícius", 70, 70, 70, 70));
}
