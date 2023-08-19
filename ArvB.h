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

void inicializa(struct NO *no);
void printChaves(ArvB *raiz);
int compara(const void *a, const void *b);
int NoFolha(ArvB *no);
void inicializa(struct NO* no);
void reequilibra(ArvB* raiz, int pos_pai, int pos_filho);
void reequilibra_apos_remocao(ArvB* raiz, int pos_pai, int pos_filho);
void arvB_imprime(ArvB* raiz);

#endif