#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarBotafogo(Time& time) {
    time.adicionarJogador(new Goleiro(1, "John", 80, 80, 80));
    time.adicionarJogador(new Defensor(2, "Mateo Ponte", 79, 79, 79, 79));
    time.adicionarJogador(new Defensor(3, "Bastos", 77, 77, 77, 77));
    time.adicionarJogador(new Defensor(4, "Alexander Barboza", 80, 80, 80, 80));
    time.adicionarJogador(new Defensor(5, "Cuiabano", 76, 76, 76, 76));
    time.adicionarJogador(new Defensor(6, "Vitinho", 74, 74, 74, 74));
    time.adicionarJogador(new JogadorDeCampo(7, "Marlon Freitas", "VOL", 82, 82, 82, 82, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Tche Tche", "VOL", 77, 77, 77, 77, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Tomas Almada", "MEI", 83, 83, 83, 83, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Eduardo", "MEI", 76, 76, 76, 76, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Savarino", "MEI", 81, 81, 81, 81, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Tiquinho Soares", 82, 82, 82, 82));
    time.adicionarJogador(new Atacante(13, "Igor Jesus", 80, 80, 80, 80));
    time.adicionarJogador(new Atacante(14, "Junior Santos", 78, 78, 78, 78));
    time.adicionarJogador(new Atacante(15, "Luis Henrique", 79, 79, 79, 79));
}
