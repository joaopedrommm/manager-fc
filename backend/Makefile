CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I src -I/opt/homebrew/opt/sqlite/include
LDFLAGS  = -L/opt/homebrew/opt/sqlite/lib -lsqlite3

# Fontes do jogo (compartilhadas entre terminal e servidor)
SHARED = src/models/Campeonato.cpp \
         src/models/Calendario.cpp \
         src/models/Simulacao.cpp  \
         src/models/Formacoes.cpp  \
         src/Database.cpp

# ── Terminal (modo original) ──────────────────────────────────
all: manager-fc

manager-fc: src/main.cpp $(SHARED)
	$(CXX) $(CXXFLAGS) -o manager-fc src/main.cpp $(SHARED) $(LDFLAGS)

run: manager-fc
	./manager-fc

# ── Servidor Web ──────────────────────────────────────────────
server: src/server.cpp $(SHARED)
	$(CXX) $(CXXFLAGS) -o manager-fc-server src/server.cpp $(SHARED) $(LDFLAGS) -lpthread

run-server: server
	./manager-fc-server

# ── Limpeza ───────────────────────────────────────────────────
clean:
	rm -f manager-fc manager-fc-server manager-fc.exe manager-fc-server.exe