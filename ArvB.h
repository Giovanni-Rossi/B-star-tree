#ifndef ARVB_H
#define ARVB_H

#define ORDEM 8 //número máximo de filhos

typedef struct NO* ArvB;

ArvB* arvB_cria();
void arvB_destroi(ArvB *raiz);
int arvB_insere(ArvB* raiz, int valor);
int arvB_remove(ArvB *raiz, int valor);
int arvB_busca(ArvB *raiz, int valor);
int arvB_qtd_nos(ArvB *raiz);
int arvB_qtd_chaves(ArvB *raiz);

void printChaves(ArvB *raiz);
int compara(const void *a, const void *b);
int NoFolha(ArvB *no);
void inicializa(struct NO* no);
#endif