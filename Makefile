CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I src

SHARED_SRC = src/models/Campeonato.cpp \
             src/models/Calendario.cpp \
             src/models/Simulacao.cpp  \
             src/models/Formacoes.cpp

DATA_SRC = $(wildcard src/data/*.cpp)

all: manager-fc manager-fc-server

manager-fc: src/main.cpp $(SHARED_SRC) $(DATA_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

manager-fc-server: src/server.cpp $(SHARED_SRC) $(DATA_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lws2_32 -lmswsock

clean:
	rm -f manager-fc manager-fc-server

run:
	./manager-fc

run-server:
	./manager-fc-server