parametrosCompilacao=-Wall -O3
nomeAula=ex23

all: $(nomeAula)

$(nomeAula): main.o Forma.o Circulo.o Retangulo.o Triangulo.o
	g++ main.o Forma.o Circulo.o Retangulo.o Triangulo.o $(parametrosLinkedicao) -o $(nomeAula)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Forma.o: Forma.hpp Forma.cpp
	g++ -c Forma.cpp $(parametrosCompilacao)

Circulo.o: Circulo.hpp Circulo.cpp
	g++ -c Circulo.cpp $(parametrosCompilacao)

Retangulo.o: Retangulo.hpp Retangulo.cpp
	g++ -c Retangulo.cpp $(parametrosCompilacao)

Triangulo.o: Triangulo.hpp Triangulo.cpp
	g++ -c Triangulo.cpp $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomeAula)
