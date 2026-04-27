#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Grêmio — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarGremio(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Tiago Volpi", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Grando", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Kannemann", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Wagner Leonardo", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Jemerson", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Rodrigo Ely", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "João Pedro", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Marlon", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Lucas Esteves", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Igor Serrote", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Villasanti", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Dodi", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Camilo", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Edenilson", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Cristaldo", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Monsalve", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(17, "Pavón", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Aravena", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Braithwaite", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Amuzu", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Carballo", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Arezo", 70, 70, 70, 70));
}
