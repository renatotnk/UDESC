parametrosCompilacao=-Wall #-Wshadow
nomeAula=aula16

all: $(nomeAula)

$(nomeAula): main.o Pessoa.o Disciplina.o SalaAula.o ConteudoMinistrado.o Console.o
	g++ -o $(nomeAula) main.o Pessoa.o Disciplina.o SalaAula.o ConteudoMinistrado.o Console.o $(parametrosCompilacao)

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

Console.o: Console.hpp Console.cpp
	g++ -c Console.hpp Console.cpp $(paramentrosCompilacao)

clean:
	rm *.o *.gch $(nomeAula)
