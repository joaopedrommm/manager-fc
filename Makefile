CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I src

SRC = src/main.cpp \
      src/models/Campeonato.cpp \
      src/models/Calendario.cpp \
      src/models/Simulacao.cpp \
      src/models/Formacoes.cpp

TARGET = manager-fc

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
