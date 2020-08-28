#ifndef FILAGENERICA_H
#define FILAGENERICA_H
#define ERRO_FILA_VAZIA -1
#define ERRO_FILA_CHEIA -2

typedef struct {
  void **dados;
  int inicio;
  int fim;
  int capacidade;
  int quantidade;
  int tam_info;
}FilaGenerica;

void inicializa_fila(FilaGenerica *p, int c,int t);
int inserir(FilaGenerica *p,void *info);
void mostra_fila(FilaGenerica f,void (*mostra)(void *));
int remover(FilaGenerica *p,void *info);
void desaloca_fila(FilaGenerica *f);
int fila_cheia(FilaGenerica f);
int fila_vazia(FilaGenerica f);
void processa_fila(FilaGenerica *f,void(*processa)(void *));

#endif
