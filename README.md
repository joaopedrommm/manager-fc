# ⚽ Manager FC

Simulador do Campeonato Brasileiro Série A 2026, desenvolvido como projeto da disciplina de **Estruturas de Dados e Orientação a Objetos (EDOO)** — CIn/UFPE.

O projeto é dividido em dois processos independentes: um **backend em C++** que roda como servidor HTTP e um **frontend em React/Vite** que consome a API REST.

---

## Sumário

- [Visão Geral](#visão-geral)
- [Tecnologias](#tecnologias)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Conceitos de OOP Aplicados](#conceitos-de-oop-aplicados)
- [Estruturas de Dados](#estruturas-de-dados)
- [Hierarquia de Classes](#hierarquia-de-classes)
- [API REST](#api-rest)
- [Sistema de Simulação](#sistema-de-simulação)
- [Os 20 Times](#os-20-times)
- [Como Rodar](#como-rodar)
- [Equipe](#equipe)

---

## Visão Geral

O Manager FC permite ao jogador escolher um dos 20 clubes do Brasileirão 2026 e disputar uma temporada completa de 38 rodadas. Cada rodada é simulada minuto a minuto, com gols, cartões amarelos e vermelhos sendo gerados de forma probabilística com base na força, formação tática e agressividade dos jogadores.

**Funcionalidades:**
- Seleção de clube com força e orçamento reais
- Simulação minuto a minuto com narração de eventos
- Tabela de classificação com zonas de Libertadores, Sul-Americana e rebaixamento
- Troca de formação tática entre 8 esquemas diferentes
- Melhora de elenco com gasto de orçamento
- Tela de créditos
- Tela de fim de temporada com campeão e rebaixados

---

## Tecnologias

**Backend:**
- C++17
- [httplib.h](https://github.com/yhirose/cpp-httplib) — servidor HTTP single-header
- JSON serializado manualmente (zero dependências externas além do httplib)
- Compilado com g++ (MinGW no Windows)

**Frontend:**
- React 18
- Vite
- Tailwind CSS

---

## Estrutura do Projeto

```
manager-fc/
├── backend/
│   └── src/
│       ├── server.cpp              # Ponto de entrada do servidor HTTP
│       ├── main.cpp                # Versão terminal (sem frontend)
│       ├── httplib.h               # Biblioteca HTTP single-header
│       ├── models/
│       │   ├── Jogador.h           # Classe base abstrata
│       │   ├── Goleiro.h           # Classe filha de Jogador
│       │   ├── JogadorDeCampo.h    # Classe filha + Atacante + Defensor
│       │   ├── Time.h              # Encapsula elenco e estatísticas
│       │   ├── Partida.h           # Partida + Rodada
│       │   ├── Campeonato.h/.cpp   # Array dos 20 times
│       │   ├── Calendario.h/.cpp   # Geração das 38 rodadas
│       │   ├── Simulacao.h/.cpp    # Motor de simulação minuto a minuto
│       │   ├── ContextoPartida.h   # Estado dinâmico durante a partida
│       │   ├── Evento.h            # Hierarquia de eventos (GOL, cartões)
│       │   └── Formacoes.h/.cpp    # Matriz de modificadores táticos
│       ├── colecoes/
│       │   ├── AVL.h               # Árvore AVL genérica (template)
│       │   ├── LinkedList.h        # Lista encadeada genérica (template)
│       │   └── Queue.h             # Fila genérica (template)
│       └── data/
│           ├── elencos.h           # Declarações das funções de elenco
│           ├── flamengo.cpp        # Elenco real do Flamengo 2026
│           ├── palmeiras.cpp       # Elenco real do Palmeiras 2026
│           └── ...                 # (20 arquivos, um por time)
└── frontend/
    └── src/
        ├── App.jsx
        └── components/
            ├── MenuPrincipal.jsx
            ├── SelecaoClube.jsx
            ├── Dashboard.jsx
            ├── Simulação.jsx
            ├── Pos-jogo.jsx
            ├── FimTemporada.jsx
            └── Creditos.jsx
```

---

## Conceitos de OOP Aplicados

### Abstração
`Jogador` é uma classe abstrata com o método puro `calcularContribuicao()`. Nunca instanciamos um `Jogador` diretamente — apenas suas subclasses concretas.

### Herança
```
Jogador  (abstrata)
├── Goleiro
└── JogadorDeCampo
    ├── Atacante
    └── Defensor
```

### Polimorfismo
O método `calcularContribuicao(float forcaBase)` é reimplementado em cada subclasse com pesos diferentes:

| Tipo | Habilidade | Velocidade | Passe | Chute | Reflexos |
|------|-----------|-----------|-------|-------|---------|
| Goleiro | 50% | — | — | — | 50% |
| JogadorDeCampo | 40% | 20% | 20% | 20% | — |
| Atacante | 30% | 30% | 10% | 30% | — |
| Defensor | 50% | 20% | 30% | — | — |

Em `Time::calcularForcaElenco()`, o loop chama `elenco[i]->calcularContribuicao()` sem saber o tipo real de cada jogador — o C++ resolve automaticamente qual versão executar.

### Encapsulamento
Todos os atributos são `private`. O acesso externo é feito exclusivamente por getters e setters públicos.

### Composição
`Time` tem um array de `Jogador*`. `Partida` tem uma `LinkedList<Evento*>`. `ContextoPartida` recebe dois `Time*` e gerencia o estado dinâmico da partida.

---

## Estruturas de Dados

Todas as estruturas são genéricas (templates) e ficam na pasta `colecoes/`.

### AVL\<T\>
Árvore AVL auto-balanceada usada para manter a tabela de classificação sempre ordenada. O comparador é passado no construtor, permitindo qualquer critério de ordenação. No projeto, a ordenação segue as regras do Brasileirão: pontos → vitórias → saldo de gols → gols pró.

### LinkedList\<T\>
Lista encadeada simples usada para o log de eventos de cada partida (`LinkedList<Evento*>`). Inserção no final em O(1).

### Queue\<T\>
Fila FIFO usada para o calendário de rodadas (`Queue<Rodada*>`). As 38 rodadas são geradas e enfileiradas; a cada ciclo de jogo uma é removida da frente.

---

## Hierarquia de Classes

### Jogador (abstrata)
Atributos: `id`, `nome`, `posicao`, `habilidade`, `agressividade` (enum BAIXA/MEDIA/ALTA).

O enum `Agressividade` controla as probabilidades de cartão de cada jogador:
- Cartão amarelo: BAIXA=0.8%, MEDIA=1.5%, ALTA=2.2% por minuto
- Cartão vermelho: BAIXA=0.05%, MEDIA=0.10%, ALTA=0.18% por minuto

### Goleiro
Adiciona `reflexos` e `defesasPenalti`. Agressividade sempre `BAIXA`.

### JogadorDeCampo
Adiciona `velocidade`, `passe` e `chute`. Agressividade configurável (padrão `MEDIA`).

### Atacante
Herda de `JogadorDeCampo`. Posição `"ATA"`, agressividade `MEDIA` hardcoded.

### Defensor
Herda de `JogadorDeCampo`. Posição `"ZAG"`, agressividade `ALTA` hardcoded.

### Evento (abstrata)
Hierarquia de eventos do jogo:
- `EventoGol` — sorteia uma frase de narração entre 6 opções
- `EventoCartaoAmarelo` — registra jogador e motivo da falta
- `EventoCartaoVermelho` — registra expulsão e atualiza o `ContextoPartida`
- `EventoIntervalo` — exibe placar parcial ao fim do 1º tempo

### ContextoPartida
Gerencia o estado dinâmico de uma partida em andamento: rastreia jogadores expulsos, recalcula a força efetiva dos times com menos jogadores e aplica o modificador tático da formação via `Formacoes::getModificador()`.

---

## API REST

O servidor sobe na porta `8080`. O frontend consome via proxy configurado no Vite.

| Método | Rota | Descrição |
|--------|------|-----------|
| GET | `/api/times` | Lista os 20 times com força, formação e orçamento |
| POST | `/api/iniciar` | Inicia o jogo com o time escolhido `{ id: N }` |
| GET | `/api/estado` | Retorna rodada atual, pontos e dados do meu time |
| GET | `/api/tabela` | Classificação completa em ordem decrescente |
| GET | `/api/elenco` | Jogadores do meu time com tipo e habilidade |
| POST | `/api/jogar-rodada` | Simula a rodada e retorna eventos + resultados |
| POST | `/api/formacao` | Muda a formação tática `{ formacao: "4-3-3" }` |
| POST | `/api/melhorar` | Gasta orçamento para aumentar força `{ quantidade: N }` |

---

## Sistema de Simulação

A simulação segue um loop minuto a minuto de 1 a 90, com acréscimos aleatórios de 1 a 5 minutos.

**Fases do jogo** — multiplicadores de probabilidade de gol:
- Início (1–30 min): ×0.8
- Meio (31–60 min): ×1.0
- Final (61–90+ min): ×1.3

**Vantagem do mandante:** o time da casa tem +10% de chance de marcar.

**Modificador tático:** a matriz `Formacoes::MODIFICADOR[10][10]` define bônus e penalidades entre os 10 esquemas táticos disponíveis (range de -11% a +11%).

**Expulsões:** quando um jogador é expulso, o `ContextoPartida` o marca como inativo e a força efetiva do time é recalculada excluindo sua contribuição.

---

## Os 20 Times

Cada time tem um arquivo `.cpp` dedicado em `backend/src/data/` com 15 jogadores reais da temporada 2026 (1 GOL, 5 DEF, 5 MEI, 4 ATA), cadastrados manualmente a partir de dados públicos.

| Time | Sigla | Força |
|------|-------|-------|
| Flamengo | FLA | 82 |
| Palmeiras | PAL | 81 |
| Botafogo | BOT | 79 |
| Atlético Mineiro | CAM | 79 |
| Fluminense | FLU | 78 |
| São Paulo | SAO | 78 |
| Internacional | INT | 77 |
| Corinthians | COR | 77 |
| Grêmio | GRE | 77 |
| Athletico PR | CAP | 76 |
| Vasco | VAS | 76 |
| Cruzeiro | CRU | 76 |
| Bahia | BAH | 76 |
| Bragantino | RBB | 76 |
| Santos | SAN | 75 |
| Vitória | VIT | 73 |
| Coritiba | CFC | 73 |
| Mirassol | MIR | 72 |
| Chapecoense | CHA | 72 |
| Remo | REM | 70 |

---

## Como Rodar

### Pré-requisitos
- g++ com suporte a C++17
- Node.js 18+
- Windows (flags `-lws2_32 -lmswsock` para o httplib)

### 1. Compilar o backend

```bash
cd backend
g++ -o manager-fc-server src/server.cpp src/models/Simulacao.cpp src/models/Formacoes.cpp src/models/Campeonato.cpp src/models/Calendario.cpp src/data/flamengo.cpp src/data/palmeiras.cpp src/data/atletico_mg.cpp src/data/botafogo.cpp src/data/fluminense.cpp src/data/sao_paulo.cpp src/data/internacional.cpp src/data/corinthians.cpp src/data/gremio.cpp src/data/athletico_pr.cpp src/data/vasco.cpp src/data/cruzeiro.cpp src/data/bahia.cpp src/data/bragantino.cpp src/data/santos.cpp src/data/vitoria.cpp src/data/coritiba.cpp src/data/mirassol.cpp src/data/chapecoense.cpp src/data/remo.cpp -I src -lws2_32 -lmswsock
```

### 2. Rodar o servidor

```bash
.\manager-fc-server.exe
```

O servidor sobe em `http://localhost:8080`.

### 3. Rodar o frontend

Em outro terminal:

```bash
cd frontend
npm install   # apenas na primeira vez
npm run dev
```

### 4. Acessar

Abra `http://localhost:5173` no navegador.

---

## Equipe

Desenvolvido por Davi Mello, João Pedro Medeiros, João Luiz Siqueira e Vitor Nunes do 2º período de Sistemas da Informação — CIn/UFPE, 2026.
