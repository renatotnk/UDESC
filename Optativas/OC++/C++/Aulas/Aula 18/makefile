parametrosCompilacao=-Wall #-Wshadow

all: aula18

aula18: main.o Pessoa.o Disciplina.o SalaAula.o ConteudoMinistrado.o
	g++ -o aula18 main.o Pessoa.o Disciplina.o SalaAula.o ConteudoMinistrado.o  $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Pessoa.o: Pessoa.hpp Pessoa.cpp
	g++ -c Pessoa.cpp $(parametrosCompilacao)

Disciplina.o: Disciplina.hpp Disciplina.cpp
	g++ -c Disciplina.cpp $(parametrosCompilacao)

SalaAula.o: SalaAula.hpp SalaAula.cpp
	g++ -c SalaAula.cpp $(parametrosCompilacao)

ConteudoMinistrado.o: ConteudoMinistrado.hpp ConteudoMinistrado.cpp
	g++ -c ConteudoMinistrado.cpp $(parametrosCompilacao)

clean:
	rm *.o aula18
