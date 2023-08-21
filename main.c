#include "arvB.h"
#include <stdio.h>

int main(void) {
  ArvB *raiz = arvB_cria();
  arvB_insere(raiz, 20);
  arvB_insere(raiz, 10);
  arvB_insere(raiz, 19);
  arvB_insere(raiz, 9);
  arvB_insere(raiz, 18);
  arvB_insere(raiz, 8);
  arvB_imprime(raiz);
  arvB_insere(raiz, 17);
  arvB_insere(raiz, 7);
  arvB_insere(raiz, 24);
  arvB_imprime(raiz);
  arvB_insere(raiz, 21);
  arvB_insere(raiz, 22);
  arvB_insere(raiz, 23);
  arvB_imprime(raiz);
  arvB_insere(raiz, 27);
  arvB_imprime(raiz);
  arvB_insere(raiz, 12);
  arvB_imprime(raiz);
  arvB_insere(raiz, 13);
  arvB_imprime(raiz);
  /*
  arvB_insere(raiz, 9);
  arvB_insere(raiz, 8);
  arvB_insere(raiz, 7);
  arvB_insere(raiz, 6);
  arvB_insere(raiz, 5);
  arvB_insere(raiz, 4);
  arvB_insere(raiz, 3);
  printf("Qtd de Nos: %d\n", arvB_qtd_nos(raiz));
  printf("Qtd de Chaves: %d\n", arvB_qtd_chaves(raiz));
  if (arvB_busca(raiz, 10))
    printf("O elemento 10 esta presente na arvore B*!\n");
  else
    printf("O elemento 10 nao esta presente na arvore B*!\n");

  arvB_imprime(raiz);
  arvB_insere(raiz, 11);
  arvB_insere(raiz, 12);
  arvB_insere(raiz, 13);
  arvB_insere(raiz, 14);
  arvB_imprime(raiz);
  arvB_insere(raiz, 15);
  arvB_insere(raiz, 16);
  arvB_imprime(raiz);
  arvB_insere(raiz, 17);
  arvB_insere(raiz, 18);
  arvB_imprime(raiz);
  */
  /*
  arvB_remove(raiz, 10);
  arvB_qtd_nos(raiz);

  arvB_imprime(raiz);

  if (arvB_busca(raiz, 10))
    printf("O elemento 10 esta presente na arvore B*!\n");
  else
    printf("O elemento 10 nao esta presente na arvore B*!\n");


  if (arvB_busca(raiz, 20))
    printf("O elemento 20 esta presente na arvore B*!\n");
  else
    printf("O elemento 20 nao esta presente na arvore B*!\n");

  arvB_insere(raiz, 19);
  arvB_imprime(raiz);*/
  return 0;
}