#include <stdio.h>
#include "ArvB.h"

int main(){
    ArvB *raiz = arvB_cria();

    arvB_insere(raiz, 10);
    arvB_insere(raiz, 9);
    arvB_insere(raiz, 8);
    printChaves(raiz);
    arvB_insere(raiz, 7);
    printChaves(raiz);
    arvB_insere(raiz, 6);
    printChaves(raiz);
    arvB_insere(raiz, 5);
    printChaves(raiz);
    arvB_insere(raiz, 4);
    printChaves(raiz);
    arvB_insere(raiz, 3);
    printChaves(raiz);
    arvB_insere(raiz, 12);
    if (arvB_busca(raiz, 12)){
        printf("ACHOU\n");
    }

    
    return 0;
}