parametrosCompilacao=-Wall #-Wshadow
nomeAula=aula20

all: $(nomeAula)

$(nomeAula): main.o Fila.hpp
	g++ -o $(nomeAula) main.o Fila.hpp $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomeAula)
