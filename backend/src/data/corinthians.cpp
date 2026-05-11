#include "../models/Jogador.h"
#include "../models/JogadorDeCampo.h"
#include "../models/Goleiro.h"
#include "../models/Time.h"

void criarCorinthians(Time& time) {
    time.adicionarJogador(new Goleiro(1, "Hugo Souza", 78, 78, 78));
    time.adicionarJogador(new Defensor(2, "Matheuzinho", 75, 75, 75, 75));
    time.adicionarJogador(new Defensor(3, "Andre Ramalho", 78, 78, 78, 78));
    time.adicionarJogador(new Defensor(4, "Caca", 79, 79, 79, 79));
    time.adicionarJogador(new Defensor(5, "Matheus Bidu", 75, 75, 75, 75));
    time.adicionarJogador(new Defensor(6, "Fagner", 72, 72, 72, 72));
    time.adicionarJogador(new JogadorDeCampo(7, "Raniele", "VOL", 76, 76, 76, 76, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(8, "Charles", "VOL", 77, 77, 77, 77, Agressividade::ALTA));
    time.adicionarJogador(new JogadorDeCampo(9, "Igor Coronado", "MEI", 78, 78, 78, 78, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(10, "Rodrigo Garro", "MEI", 81, 81, 81, 81, Agressividade::MEDIA));
    time.adicionarJogador(new JogadorDeCampo(11, "Breno Bidon", "MEI", 74, 74, 74, 74, Agressividade::MEDIA));
    time.adicionarJogador(new Atacante(12, "Yuri Alberto", 82, 82, 82, 82));
    time.adicionarJogador(new Atacante(13, "Memphis Depay", 82, 82, 82, 82));
    time.adicionarJogador(new Atacante(14, "Talles Magno", 77, 77, 77, 77));
    time.adicionarJogador(new Atacante(15, "Pedro Raul", 75, 75, 75, 75));
}
