#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDJ.h"


void inicializacao(CDJ *l,int t){
  l->tamInfo = t;
  l->cabeca = NULL;
  l->qtd = 0;
}

Membro *aloca_elemento(void *x, int t){
  Membro *novo = malloc(sizeof(Membro));
  if(novo == NULL){
    return NULL;
  }
  novo->info = malloc(t);
    if(novo->info == NULL){
      free(novo);
     return NULL;
  }
  memcpy(novo->info,x,t);
  return novo;
}

int insereNoInicio(CDJ *l, void *info){
  Membro *novo = aloca_elemento(info, l->tamInfo);
  if(novo == NULL){
    printf("Erro na inserção!\n");
    return 0;    //Erro na alocaçao
  }

  novo->ant = NULL;
  novo->suc = l->cabeca;
  l->cabeca = novo;
  if(novo->suc != NULL){
    novo->suc->ant = novo;
  }
  l->qtd++;
  return 1;     //sucesso!
}

int insereNoFim(CDJ *l, void *info){
  if(l->cabeca == NULL){
    return insereNoInicio(l,info);
  }
  Membro *p = l->cabeca;
  Membro *novo = aloca_elemento(info, l->tamInfo);
  if(novo == NULL){
    return 0;  //Erro na alocacao
  }
  while(p->suc != NULL){
    p = p->suc;
  }
  novo->suc = NULL;
  novo->ant = p;
  p->suc = novo;
  l->qtd++;
  return 1;    //sucesso!
}

int removeDoInicio(CDJ *l,void *info){
  if(l->cabeca == NULL)
    return ERRO_LISTA_VAZIA;
  Membro *p = l->cabeca;
  l->cabeca = p->suc;
  if(l->cabeca != NULL){
    l->cabeca->ant = NULL;
  }
  memcpy(info,p->info,l->tamInfo);
  free(p->info);
  free(p);
  l->qtd--;
  return 1;   //sucesso
}

int removeDofim(CDJ *l, void *info){
  if(l->cabeca == NULL)
    return ERRO_LISTA_VAZIA;
  if(l->cabeca->suc == NULL)            //Só um elemento
    return removeDoInicio(l,info);
  Membro *p = l->cabeca;
  while(p->suc->suc != NULL){      //parar no penultimo
    p = p->suc;
  }
  memcpy(info, p->suc->info,l->tamInfo);
  free(p->suc->info);
  free(p->suc);
  p->suc = NULL;
  l->qtd--;
  return 1;           //sucesso!
}

int removeDaPos(CDJ *l,void *info,int pos){
  if(l->cabeca == NULL){
    return ERRO_LISTA_VAZIA;
  }if(pos < 0){
    return ERRO_POSICAO_INVALIDA;
  }if(pos == 0){
    return removeDoInicio(l,info);
  }
  Membro *p = l->cabeca;
  int cont = 0;
  while((cont < pos - 1) && (p->suc != NULL)){
    p = p->suc;
    cont++;
  }
  if(p->suc == NULL){
    return ERRO_POSICAO_INVALIDA;
  }
  Membro *x = p->suc;
  p->suc = x->suc;
  memcpy(info,x->info,l->tamInfo);
  free(x->info);
  free(x);
  if(p->suc != NULL){
    p->suc->ant = p;
  }
  l->qtd--;
  return 1;   //sucesso
}

Membro *pesquisa_membro(CDJ *l, void *info,int (*compara)(void *a,void *b)){
  Membro *p;
  CDJ *temp;
  Membro *m; 
    for(p = l->cabeca; p->suc != NULL; p = p->suc){
      memcpy(temp,p->info,sizeof(CDJ));
      for(m = temp->cabeca; m->suc != NULL; m = m->suc){
    	 if(compara(m->info, info) == 0){
    	    return m;
    	}else{
  	    return NULL;
	}
      }
    }
}

int remove_conjunto(CDJ *l,void *info,int (*compara)(void *a, void *b)){
  Membro *p;
  Membro *k;
  CDJ *temp;
  if(l->cabeca == NULL){
    return ERRO_LISTA_VAZIA;
  }
  for(p = l->cabeca; p->suc != NULL;p = p->suc){
    memcpy(temp,p->info,sizeof(CDJ));
    for(k = temp->cabeca; k->suc != NULL; k = k->suc){
      if(compara(k->info, info) == 0){
        free(k->info);
        free(k);
        if(p->ant == NULL){
          l->cabeca = p->suc;
        }if(p->suc->suc == NULL){
          p->suc = NULL;
          free(p->suc->info);
          free(p->suc);
        }
        p->ant->suc = p->suc;
        p->suc->ant = p->ant;
        free(p->info);
        free(p);
        return 1;
      }else{
        return 0;
      }
    }
  }
}

int desaloca_estrutura(CDJ *l){
  if(l->cabeca == NULL)
    return ERRO_LISTA_VAZIA;
  Membro *k;
  CDJ *temp;
  Membro *m;
  for(k = l->cabeca;k->suc != NULL; k = k->suc){
    memcpy(temp,k->info,sizeof(CDJ));
    for(m = temp->cabeca; m->suc != NULL; m = m->suc){
      free(m->info);
      free(m);
    }
  free(k->info);
  free(k);
  }
  return 1;
}

int mostra_conjuntos(CDJ *l){
  if(l->cabeca == NULL)
    return ERRO_LISTA_VAZIA;
  Membro *k;
  CDJ *temp;
  Membro *m;
  for(k = l->cabeca;k->suc != NULL; k = k->suc){
    memcpy(temp,k->info,sizeof(CDJ));
    for(m = temp->cabeca; m->suc != NULL; m = m->suc){
      printf("%c  ",m->info);
    }
  printf("\n");
  }
  return 1;
}

int une_conjuntos(CDJ *l, void *a, void *b,int (*compara)(void *a, void *b)){
  if(l->cabeca == NULL)
  return ERRO_LISTA_VAZIA;
  Membro *k;
  CDJ *temp;
  Membro *m;
  Membro *i;
  CDJ *temp2;
  Membro *n;
    for(k = l->cabeca;k->suc != NULL; k = k->suc){
      memcpy(temp,k->info,sizeof(CDJ));
      for(m = temp->cabeca; m->suc != NULL; m = m->suc){
        if(compara(m->info, a) == 0){
          for(i = l->cabeca;i->suc != NULL; i = i->suc){
            memcpy(temp2,i->info,sizeof(CDJ));
            for(n = temp2->cabeca; n->suc != NULL; n = n->suc){
              if(compara(n->info, b) == 0){
                m->suc = temp2->cabeca;
                remove_conjunto(l,b,compara);
              }
            }
          }
        }
      }
    }
  return 1;
}
