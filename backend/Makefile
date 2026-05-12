CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I src

# Fontes do jogo (compartilhadas entre terminal e servidor)
SHARED = src/models/Campeonato.cpp \
         src/models/Calendario.cpp \
         src/models/Simulacao.cpp  \
         src/models/Formacoes.cpp  \
         src/data/flamengo.cpp     \
         src/data/atletico_mg.cpp  \
         src/data/palmeiras.cpp    \
         src/data/fluminense.cpp   \
         src/data/athletico_pr.cpp \
         src/data/internacional.cpp\
         src/data/sao_paulo.cpp    \
         src/data/gremio.cpp       \
         src/data/botafogo.cpp     \
         src/data/vasco.cpp        \
         src/data/corinthians.cpp  \
         src/data/cruzeiro.cpp     \
         src/data/bahia.cpp        \
         src/data/santos.cpp       \
         src/data/bragantino.cpp   \
         src/data/chapecoense.cpp  \
         src/data/coritiba.cpp     \
         src/data/vitoria.cpp      \
         src/data/mirassol.cpp     \
         src/data/remo.cpp

# ── Terminal (modo original) ──────────────────────────────────
all: manager-fc

manager-fc: src/main.cpp $(SHARED)
	$(CXX) $(CXXFLAGS) -o manager-fc src/main.cpp $(SHARED)

run: manager-fc
	./manager-fc

# ── Servidor Web ──────────────────────────────────────────────
# Windows (MinGW): usa -lws2_32
# Linux/Mac: troque -lws2_32 por -lpthread
server: src/server.cpp $(SHARED)
	$(CXX) $(CXXFLAGS) -o manager-fc-server src/server.cpp $(SHARED) -lws2_32

run-server: server
	./manager-fc-server

# ── Limpeza ───────────────────────────────────────────────────
clean:
	rm -f manager-fc manager-fc-server manager-fc.exe manager-fc-server.exe