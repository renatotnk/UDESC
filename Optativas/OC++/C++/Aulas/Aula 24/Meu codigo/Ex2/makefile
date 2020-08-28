parametrosCompilacao=-Wall #-Wshadow
nomeAula=aula23

all: $(nomeAula)

$(nomeAula): main.o Ponto.o Trajeto.o DistanciaEuclidiana.o DistanciaManhattan.o
	g++ -o $(nomeAula) main.o Ponto.o Trajeto.o DistanciaEuclidiana.o DistanciaManhattan.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Pessoa.o: Ponto.hpp Ponto.cpp
	g++ -c Ponto.cpp $(parametrosCompilacao)

Trajeto.o: Trajeto.hpp Trajeto.cpp
	g++ -c Trajeto.cpp $(parametrosCompilacao)

DistanciaEuclidiana.o:
	g++ -c DistanciaEuclidiana.cpp $(parametrosCompilacao)
DistanciaManhattan.o:
	g++ -c DistanciaManhattan.cpp $(parametrosCompilacao)
clean:
	rm -f *.o *.gch $(nomeAula)
