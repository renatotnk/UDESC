#ifndef _PILHA_H_
#define _PILHA_H_

#include <cstddef>
#include <list>

template <typename T = int, size_t MAX_PILHA = 65536, typename U = std::list<T>>
class Pilha {
public:
  Pilha() : size{0} {}
  ~Pilha() {}

  bool push(const T valor) {
    if (this->estaCheia())
      return false;
    this->size++;
    this->pilha.push_back(valor);
    return true;
  }

  bool pop(T *const retorno) {
    if (this->estaVazia())
      return false;
    *retorno = this->pilha.back();
    this->pilha.pop_back();
    this->size--;
    return true;
  }

  bool estaCheia() const { return this->size >= MAX_PILHA; }

  bool estaVazia() const { return this->size <= 0; }

private:
  size_t size;
  U pilha;
};

#endif