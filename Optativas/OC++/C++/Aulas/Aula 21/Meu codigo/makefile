parametrosCompilacao=-Wall #-Wshadow
nomeAula=aula21

all: $(nomeAula)

$(nomeAula): main.o Pilha.hpp
	g++ -o $(nomeAula) main.o Pilha.hpp $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomeAula)
