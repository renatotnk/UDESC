parametrosCompilacao=-Wall #-Wshadow

all: aula12

aula12: main.o Pessoa.o Disciplina.o
	g++ -o3 -o aula12 main.o Pessoa.o Disciplina.o  $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Pessoa.o: Pessoa.hpp Pessoa.cpp
	g++ -c Pessoa.cpp $(parametrosCompilacao)

Disciplina.o: Disciplina.hpp Disciplina.cpp
	g++ -c Disciplina.cpp $(parametrosCompilacao)

clean:
	rm *.o aula12
