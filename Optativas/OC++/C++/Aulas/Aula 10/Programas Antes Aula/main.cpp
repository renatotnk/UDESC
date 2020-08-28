#include <iostream>
#include <list>

#include "Pessoa.hpp"

int main(){
	std::list<int> lista;
	std::list<int>::iterator itInt;
	std::list<Pessoa*>::iterator itPes;

	lista.push_back(10);
	lista.push_back(20);
	lista.push_front(30);

	for(itInt = lista.begin(); itInt!= lista.end(); itInt++)
		std::cout << *itInt << std::endl;

	std::cout << std::endl;

	lista.remove(20);

	for(itInt = lista.begin(); itInt!= lista.end(); itInt++)
		std::cout << *itInt << std::endl;

	std::cout << std::endl;

	std::list<Pessoa*> pessoas;
	pessoas.push_back(new Pessoa{"Joao", 15});
	pessoas.push_back(new Pessoa{"Maria", 16});
	Pessoa* p3{new Pessoa{"Pedro", 20}};
	pessoas.push_front(p3);

	for(itPes = pessoas.begin(); itPes != pessoas.end(); itPes++)//a lista contém ponteiros para pessoas, e não pessoas
		std::cout << (*itPes)->getNome() << std::endl;//o itPes é um ponteiro que aponta pra um ponteiro de pessoa!)

	std::cout << std::endl;

	for(itPes = pessoas.begin(); itPes != pessoas.end(); itPes++)
		if((*itPes)->getNome() == "Pedro")//continua até encontrar Pedro
			break;

	if(itPes != pessoas.end()){//encontrou ou chegou no final da lista?
		delete *itPes;//removendo a pessoa da memória
		pessoas.erase(itPes);//removendo o ponteiro da pessoa removida da lista
	}

	for(itPes = pessoas.begin(); itPes != pessoas.end(); itPes++)//a lista contém ponteiros para pessoas, e não pessoas
		std::cout << (*itPes)->getNome() << std::endl;//o itPes é um ponteiro que aponta pra um ponteiro de pessoa!)

	std::cout << std::endl;


	//removendo todas referências a João
	for(itPes = pessoas.begin(); itPes != pessoas.end(); itPes++)
		if((*itPes)->getNome() == "Joao"){
			delete *itPes;
			itPes = pessoas.erase(itPes);//itPes recebe o próximo item válido da lista
		}


	for(itPes = pessoas.begin(); itPes != pessoas.end(); itPes++)//a lista contém ponteiros para pessoas, e não pessoas
		std::cout << (*itPes)->getNome() << std::endl;//o itPes é um ponteiro que aponta pra um ponteiro de pessoa!)


	//Removendo as demais pessoas da memória
	for(itPes = pessoas.begin(); itPes != pessoas.end(); itPes++)
		delete *itPes;

	//agora a lista ainda possui os ponteiros, que apontam para endereços inválidos
	//para limpar a lista, basta
	pessoas.clear();
	
	std::list<double>* ptrLista{new std::list<double>};
	ptrLista->push_back(3.14);
	ptrLista->push_back(23456);

	for(auto& it: *ptrLista)
                std::cout << it << std::endl;

	delete ptrLista;


	return 0;
}
