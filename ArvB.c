#include <stdio.h>
#include <stdlib.h>
#include "arvB.h"
//ordem = 8
struct NO{
    int qtd;
    int chaves[ORDEM - 1];
    struct NO* filhos[ORDEM];
    struct NO* pai;
};

ArvB* arvB_cria(){
    ArvB* raiz = (ArvB*) malloc(sizeof(ArvB));

    if(raiz != NULL){
        *raiz = (ArvB) malloc(sizeof(struct NO));
        if(*raiz != NULL){
            (*raiz)->qtd = 0;
            for(int i = 0; i < ORDEM; i++)
                (*raiz)->filhos[i] = NULL;
            (*raiz)->pai = NULL;
        }
        else{
            free(raiz);
            raiz = NULL;
        }
    }
    
    return raiz;
}

void arvB_destroi(ArvB *raiz);

int arvB_insere(ArvB* raiz, int valor){
    //1-insercao padrao: sem split ou overflow em nó folha
    if((*raiz)->qtd < ORDEM-1 && NoFolha(raiz))
    {
        (*raiz)->chaves[(*raiz)->qtd] = valor;
        (*raiz)->qtd++;
        qsort((*raiz)->chaves, (size_t)(*raiz)->qtd, sizeof(int), compara);
    }
    //2 - Overflow da raiz -> sugestao: arrumar a condição verificando se tem um ponteiro null para pai(precisaria criar)
    else if((*raiz)->qtd == ORDEM - 1) {
        if((*raiz)->pai == NULL){
            int vetAux[ORDEM+1];
            for (int i = 0; i < (*raiz)->qtd; i++) {
                vetAux[i] = (*raiz)->chaves[i];
            }
            vetAux[(*raiz)->qtd] = valor;
            qsort(vetAux, (size_t)((*raiz)->qtd + 1), sizeof(int), compara);

            struct NO *filho1 = malloc(sizeof(struct NO));
            struct NO *filho2 = malloc(sizeof(struct NO));

            //atualizar os valores de filho como zerar qtde, filhos = null, etc
            inicializa(filho1);
            inicializa(filho2);
            // Copiar chaves para filho1
            for (int i = 0; i < ORDEM / 2; i++) {
                (filho1)->chaves[i] = vetAux[i];
                (filho1)->qtd++;
            }

            // Copiar chaves para filho2
            for (int i = (ORDEM / 2)+1, j = 0; i < ORDEM; i++, j++) {
                (filho2)->chaves[j] = vetAux[i];
                (filho2)->qtd++;
            }

            // Copiar chave mediana para a raiz
            (*raiz)->qtd = 1;
            (*raiz)->chaves[0] = vetAux[ORDEM / 2];

            // Atualizar os ponteiros dos filhos da raiz
            (*raiz)->filhos[0] = filho1;
            (*raiz)->filhos[1] = filho2;

            filho1->pai = (*raiz);
            filho2->pai = (*raiz);

            printChaves(&filho1);
            printChaves(&filho2);
        }

    }
    //3 - Insercao padrao
    for(int j = 0; j < (*raiz)->qtd;j ++)
    {
        if(valor < (*raiz)->chaves[j] && (*raiz)->filhos[j] != NULL)
        {
            if((*raiz)->filhos[j]->qtd == ORDEM-1 && (*raiz)->filhos[j+1]->qtd == ORDEM-1)
                split2to3((*raiz), j, j+1, valor);
            else
                arvB_insere(&(*raiz)->filhos[j], valor);
        }
            

        else if(valor > (*raiz)->chaves[(*raiz)->qtd-1] && (*raiz)->filhos[j+1] != NULL)
        {
            if((*raiz)->filhos[j]->qtd == ORDEM-1 && (*raiz)->filhos[j+1]->qtd == ORDEM-1)
                split2to3((*raiz), j, j+1, valor);
            else
                arvB_insere(&(*raiz)->filhos[j], valor);
        }
    }

    return 1;
}
void printChaves(ArvB *raiz){
    for(int i = 0; i < (*raiz)->qtd; i++)
        printf("%d ", (*raiz)->chaves[i]);
    printf("\n");
    printf("QUANTIDADE NO NO: %d\n", (*raiz)->qtd);
}
int arvB_remove(ArvB *raiz, int valor);

int arvB_busca(ArvB *raiz, int valor);

int arvB_qtd_nos(ArvB *raiz);

int arvB_qtd_chaves(ArvB *raiz);

int compara(const void *a, const void *b){
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x > y)
        return 1;
    else if (x == y)
        return 0;
    else
        return -1;
}

int NoFolha(ArvB *no)
{
    if((*no)->filhos[0] == NULL)
        return 1;
    else
        return 0; //passou pela verificacao
}
void inicializa(struct NO* no){
    //DEIXA COMO NULL OS FILHOS DO NOVO NO
    for(int i = 0; i < ORDEM-1; i++)
        no->filhos[i] = NULL;
    //ZERA A QTDE
    no->qtd = 0;
}

int arvB_busca(ArvB *raiz, int valor) {
  if (*raiz == NULL){
    return 0; // Árvore vazia
  }

  int i = 0;
  while (i < (*raiz)->qtd && valor > (*raiz)->chaves[i]){
    i++;
  }

  if (i < (*raiz)->qtd && valor == (*raiz)->chaves[i]){
    return 1; // Valor encontrado
  }

  if ((*raiz)->filhos[i] != NULL)
    return arvB_busca(&((*raiz)->filhos[i]), valor); 

  return 0; // Valor não encontrado
}

int split2to3(struct NO* raiz, int idxF1, int idxF2,  int valor){
    int total = 2*ORDEM+ 2;
    int auxiliar[total];
    int i = 0, j = 0;

    //OBS: idxF1 = indice do primeiro filho e idx2 do segundo
    //passa o primeiro filho pro auxiliar
    for(;i < raiz->filhos[idxF1]->qtd; i++)
        auxiliar[i] = raiz->filhos[idxF1]->chaves[i];
    
    //insere as chaves da raiz
    auxiliar[i] = raiz->chaves[0];
    i++;

    //passa o segundo filho pro auxiliar
    for(j = 0; j < raiz->filhos[idxF2]->qtd; i++, j++)
        auxiliar[i] = raiz->filhos[idxF2]->chaves[j];

    //passa a chave e ordena
    auxiliar[i] = valor;
    i++;
    qsort(auxiliar, (size_t)2*ORDEM+2, sizeof(int), compara);

    int divisor = total/3;
    raiz->chaves[0] = auxiliar[divisor-1];
    raiz->chaves[1] = auxiliar[(divisor*2)-1];
    raiz->qtd = 3;

    struct NO* filho3 = malloc(sizeof(struct NO));
    
    raiz->filhos[0] = raiz->filhos[idxF1];
    raiz->filhos[1] = raiz->filhos[idxF2];
    raiz->filhos[3] = filho3;

    raiz->filhos[idxF1]->qtd = 0;
    for(i = 0; i < divisor-1; i++, raiz->filhos[idxF1]->qtd++)
        raiz->filhos[idxF1]->chaves[i] = auxiliar[i];

    i++;
    raiz->filhos[idxF2]->qtd = 0;
    for(j = 0; i < (divisor*2)-1; i++, raiz->filhos[idxF2]->qtd++, j++)
        raiz->filhos[idxF2]->chaves[j] = auxiliar[i];
    
    i++;
    filho3->qtd = 0;
    for(j = 0; i < total; i++, filho3->qtd++, j++)
        filho3->chaves[j] = auxiliar[i];
    
    return 1;
} 