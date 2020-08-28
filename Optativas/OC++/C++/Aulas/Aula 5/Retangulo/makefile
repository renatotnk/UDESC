parametrosCompilacao=-Wall #-Wshadow

all: retangulo

retangulo: main.o Retangulo.o
	g++ -o3 -o retangulo main.o Retangulo.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Retangulo.o: Retangulo.hpp Retangulo.cpp
	g++ -c  Retangulo.cpp $(parametrosCompilacao)

clean:
	rm *.o retangulo
