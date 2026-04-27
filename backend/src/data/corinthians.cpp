#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Corinthians — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarCorinthians(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Hugo Souza", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Felipe Longo", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Cacá", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Félix Torres", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "André Ramalho", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Gustavo Henrique", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Matheuzinho", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Léo Maná", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Hugo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Fabrizio Angileri", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Raniele", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Charles", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "José Martínez", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Carrillo", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Rodrigo Garro", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Igor Coronado", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(17, "Maycon", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Memphis Depay", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Yuri Alberto", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Talles Magno", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Romero", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Gui Negão", 70, 70, 70, 70));
}
