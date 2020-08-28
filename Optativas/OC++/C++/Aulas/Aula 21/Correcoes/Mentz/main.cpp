#include <iostream>

#include "Fila.hpp"
#include "Pilha.hpp"

#include <deque>

int main(int argc, char *argv[]) {
  Fila<int> f1;
  f1.push(1);
  f1.push(2);
  f1.push(3);
  f1.push(4);

  Pilha<int, 8, std::deque<int>> p2;
  p2.push(1);
  p2.push(2);
  p2.push(3);
  p2.push(4);

  int *r1 = new int;

  while (!f1.estaVazia()) {
    f1.pop(r1);
    std::cout << "pop fila: " << *r1 << std::endl;
  }

  int *r2 = new int;

  while (!p2.estaVazia()) {
    p2.pop(r2);
    std::cout << "pop pilha: " << *r2 << std::endl;
  }

  return 0;
}