#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

// Jogadores do Botafogo — Brasileirão Série A 2026
// OVERs definidos como 70 por padrão. Ajuste conforme necessário.

void criarBotafogo(Time& time) {
    time.adicionarJogador(new Goleiro(1, "John", 70, 70, 70));
    time.adicionarJogador(new Goleiro(2, "Lucas Perri", 70, 70, 70));
    time.adicionarJogador(new Defensor(3, "Bastos", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(4, "Barboza", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(5, "Jair", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(6, "Kaio Fernando", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(7, "Alex Telles", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(8, "Cuiabano", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(9, "Vitinho", 70, 70, 70, 70));
    time.adicionarJogador(new Defensor(10, "Mateo Ponte", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(11, "Marlon Freitas", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(12, "Allan", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(13, "Danilo Barbosa", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(14, "Newton", "VOL", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(15, "Savarino", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new JogadorDeCampo(16, "Almada", "MEI", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(17, "Luiz Henrique", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(18, "Jeffinho", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(19, "Igor Jesus", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(20, "Tiquinho Soares", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(21, "Mastriani", 70, 70, 70, 70));
    time.adicionarJogador(new Atacante(22, "Matheus Martins", 70, 70, 70, 70));
}
