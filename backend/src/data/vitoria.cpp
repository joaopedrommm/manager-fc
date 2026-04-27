#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Vitória — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarVitoria(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Lucas Arcanjo", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Thiago Couto", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Edu", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Wagner Leonardo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Camutanga", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Halter", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Raúl Cáceres", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Jamerson", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Lucas Esteves", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Ramon", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Willian Oliveira", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Pepê", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Ronald", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Baralhas", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Matheuzinho", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Wellington Rato", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(17, "Cantalapiedra", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Erick", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Janderson", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Renato Kayzer", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Romarinho", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Fabri", 70, 70, 70, 70));
}
