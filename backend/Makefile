CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I src

# Fontes do jogo (compartilhadas entre terminal e servidor)
SHARED = src/models/Campeonato.cpp \
         src/models/Calendario.cpp \
         src/models/Simulacao.cpp  \
         src/models/Formacoes.cpp

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