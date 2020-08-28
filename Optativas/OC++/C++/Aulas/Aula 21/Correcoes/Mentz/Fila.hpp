#ifndef _FILA_H_
#define _FILA_H_

#include <cstddef>
#include <list>

template <typename T = int, size_t MAX_FILA = 65536, typename U = std::list<T>>
class Fila {
public:
  Fila() : size{0} {}
  ~Fila() {}

  bool push(const T valor) {
    if (this->estaCheia())
      return false;
    this->size++;
    this->fila.push_back(valor);
    return true;
  }

  bool pop(T *const retorno) {
    if (this->estaVazia())
      return false;
    *retorno = this->fila.front();
    this->size--;
    this->fila.pop_front();
    return true;
  }

  bool estaCheia() const { return this->size >= MAX_FILA; }

  bool estaVazia() const { return this->size <= 0; }

private:
  size_t size;
  U fila;
};

#endif