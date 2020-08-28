parametrosCompilacao=-Wall #-Wshadow

all: aula3

aula3: main.o Pessoa.o
	g++ -o3 -o aula3 main.o Pessoa.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Pessoa.o: Pessoa.hpp Pessoa.cpp
	g++ -c Pessoa.cpp $(parametrosCompilacao)

clean:
	rm *.o aula3
