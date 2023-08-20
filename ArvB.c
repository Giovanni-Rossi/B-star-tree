#include "arvB.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct NO {
  int qtd;
  int chaves[ORDEM - 1];
  struct NO *filhos[ORDEM];
  struct NO *pai;
};

ArvB *arvB_cria() {
  ArvB *raiz = (ArvB *)malloc(sizeof(ArvB));

  if (raiz != NULL) {
    *raiz = (ArvB)malloc(sizeof(struct NO));
    if (*raiz != NULL) {
      (*raiz)->qtd = 0;
      for (int i = 0; i < ORDEM; i++)
        (*raiz)->filhos[i] = NULL;
      (*raiz)->pai = NULL;
    } else {
      free(raiz);
      raiz = NULL;
    }
  }

  return raiz;
}

void arvB_destroi(ArvB *raiz);

void split1to2(ArvB *raiz, int valor) {
  int vetAux[ORDEM];

  for (int i = 0; i < (*raiz)->qtd; i++)
    vetAux[i] = (*raiz)->chaves[i];
  vetAux[(*raiz)->qtd] = valor;
  qsort(vetAux, (size_t)((*raiz)->qtd + 1), sizeof(int), compara);

  struct NO *filho1 = malloc(sizeof(struct NO));
  struct NO *filho2 = malloc(sizeof(struct NO));

  // atualizar os valores de filho como zerar qtde, filhos = null, etc
  inicializa(filho1);
  inicializa(filho2);
  // Copiar chaves para filho1
  for (int i = 0; i < ORDEM / 2; i++) {
    (filho1)->chaves[i] = vetAux[i];
    (filho1)->qtd++;
  }

  // Copiar chaves para filho2
  for (int i = (ORDEM / 2) + 1, j = 0; i < ORDEM; i++, j++) {
    (filho2)->chaves[j] = vetAux[i];
    (filho2)->qtd++;
  }

  // Copiar chave mediana para a raiz
  (*raiz)->qtd = 1;
  (*raiz)->chaves[0] = vetAux[ORDEM / 2];

  // Atualizar os ponteiros dos filhos da raiz
  (*raiz)->filhos[0] = filho1;
  (*raiz)->filhos[0]->pai = (*raiz);
  (*raiz)->filhos[1] = filho2;
  (*raiz)->filhos[1]->pai = (*raiz);
}

void split2to3(ArvB *irmao1, ArvB *irmao2, int valor) {

  int vetAux[(*irmao1)->qtd + (*irmao2)->qtd + 1];


  for (int i = 0; i < (*irmao1)->qtd; i++) {
    vetAux[i] = (*irmao1)->chaves[i];
    //printf("%d\n", vetAux[i]);
  }
  printf("\n");
  arvB_imprime(irmao2);
  printf("\n");
  int j = 0;
  for (int i = (*irmao1)->qtd; i < (*irmao1)->qtd + (*irmao2)->qtd; i++, j++) {
    vetAux[i] = (*irmao2)->chaves[j];
    //printf("%d\n", vetAux[i]);
  }
  vetAux[(*irmao1)->qtd + (*irmao2)->qtd] = valor;
  qsort(vetAux, (size_t)((*irmao1)->qtd + (*irmao2)->qtd + 1), sizeof(int),
        compara);

  for (int i = 0; i < (*irmao1)->qtd + (*irmao2)->qtd + 1; i++) {
    printf("%d\n", vetAux[i]);
  }

  struct NO *filho1 = malloc(sizeof(struct NO));

  inicializa(filho1);

  j = 0;
  for (int i = 0; i < ((*irmao1)->qtd + (*irmao2)->qtd + 1) / 3; i++, j++) {
    (filho1)->chaves[j] = vetAux[i];
    (filho1)->qtd++;
  }

  printf("1\n");
  arvB_imprime(&filho1);
  printf("\n");

  for (int i = ((*irmao1)->qtd + (*irmao2)->qtd + 1) / 3, j = 0; i < 2 * (((*irmao1)->qtd + (*irmao2)->qtd) / 3); i++, j++) {
    (*irmao2)->chaves[j] = vetAux[i];
    (*irmao2)->qtd++;
  }

  printf("2\n");
  arvB_imprime(irmao2);
  printf("\n");

  // Chaves restantes irão para o próprio nó
  (*irmao1)->qtd = ORDEM / 3;
  for (int i = 0; i < ORDEM - 2 * ((*irmao1)->qtd + (*irmao2)->qtd + 1) / 3; i++) {
    (*irmao1)->chaves[i] = vetAux[i + 2 * (((*irmao1)->qtd + (*irmao2)->qtd + 1) / 3)];
  }

  printf("3\n");
  arvB_imprime(irmao1);
  printf("\n");

  // Atualizar os ponteiros dos filhos do nó pai
  if ((*irmao1)->pai != NULL) {
    for (int i = 0; i <= (*irmao1)->pai->qtd; i++) {
      if ((*irmao1)->pai->filhos[i] == (*irmao1)) {
        (*irmao1)->pai->filhos[i] = filho1;
        filho1->pai = (*irmao1)->pai;
        (*irmao1)->pai->qtd += 2;
        break;
      }
    }
  } /*else {
    // Se não há pai, cria um novo nó pai
    struct NO *new_root = malloc(sizeof(struct NO));
    inicializa(new_root);
    new_root->qtd = 1;
    new_root->chaves[0] = vetAux[ORDEM+1 / 3];
    new_root->filhos[0] = filho1;
    new_root->filhos[1] = filho2;
    filho1->pai = new_root;
    filho2->pai = new_root;

    *raiz = new_root;
  }*/
}

int arvB_insere(ArvB *raiz, int valor) {
  // 1-insercao padrao: sem split ou overflow em nó folha
  if ((*raiz)->qtd < ORDEM - 1 && NoFolha(raiz)) {
    (*raiz)->chaves[(*raiz)->qtd] = valor;
    (*raiz)->qtd++;
    qsort((*raiz)->chaves, (size_t)(*raiz)->qtd, sizeof(int), compara);
  }
  // 2 - Overflow da raiz -> sugestao: arrumar a condição verificando se tem um
  // ponteiro null para pai(precisaria criar)
  else if ((*raiz)->qtd == ORDEM - 1) {
    if ((*raiz)->pai == NULL) {
      split1to2(raiz, valor);
    }
  }
  // 3 - Insercao padrao
  else {
    int i = 0;
    while (i < (*raiz)->qtd && valor > (*raiz)->chaves[i]) {
      i++;
    }
    if ((*raiz)->filhos[i] != NULL) {
      int filho_cheio = (*raiz)->filhos[i]->qtd == ORDEM - 1;
      if (filho_cheio) {
        // Overflow no filho, chame split2to3
        ArvB auxiliar1 = (*raiz)->filhos[i];
        ArvB auxiliar2 = (*raiz)->filhos[i > 0 ? i - 1 : i + 1];
        printf("redistribui para inserir o valor : %d\n", valor);
        redistribui(&auxiliar1, &auxiliar2, valor);
        //split2to3(&auxiliar1, &auxiliar2, valor);
      } else {
        // Continue a inserção recursivamente
        arvB_insere(&((*raiz)->filhos[i]), valor);
      }
    }
  }
  return 1;
}

void reequilibra(ArvB *raiz, int pos_pai, int pos_filho) {

  struct NO *filho = (*raiz)->filhos[pos_pai];
  struct NO *irmao = (*raiz)->filhos[pos_filho];

  if (irmao != NULL && irmao->qtd > 2 * (ORDEM - 1) / 3) {
    // Redistribui chaves do irmão para o filho
    filho->chaves[filho->qtd] = (*raiz)->chaves[pos_pai];
    filho->qtd++;
    (*raiz)->chaves[pos_pai] = irmao->chaves[0];

    for (int i = 0; i < irmao->qtd - 1; i++)
      irmao->chaves[i] = irmao->chaves[i + 1];
    irmao->qtd--;
  } else if (irmao != NULL && irmao->qtd == 2 * (ORDEM - 1) / 3) {
    // Une o filho com o irmão
    filho->chaves[filho->qtd] = (*raiz)->chaves[pos_pai];
    filho->qtd++;

    for (int i = 0; i < irmao->qtd; i++)
      filho->chaves[filho->qtd + i] = irmao->chaves[i];
    filho->qtd += irmao->qtd;

    for (int i = pos_pai; i < (*raiz)->qtd - 1; i++) {
      (*raiz)->chaves[i] = (*raiz)->chaves[i + 1];
      (*raiz)->filhos[i + 1] = (*raiz)->filhos[i + 2];
    }
    (*raiz)->qtd--;

    free(irmao);
  }
}

/*void reequilibra_apos_remocao(ArvB *raiz, int pos_pai, int pos_filho) {
  printf("Ta chegando aqui?\n");
  ArvB filho = (*raiz)->filhos[pos_filho];

  // Tente redistribuir com um irmão à esquerda
  if (pos_filho > 0) {
    ArvB irmao_esq = (*raiz)->filhos[pos_filho - 1];

    if (irmao_esq->qtd > 2 * (ORDEM - 1) / 3) {
      reequilibra(raiz, pos_pai, pos_filho);
      return;
    }
  }

  // Tente redistribuir com um irmão à direita
  if (pos_filho < (*raiz)->qtd) {
    ArvB irmao_dir = (*raiz)->filhos[pos_filho + 1];

    if (irmao_dir->qtd > 2 * (ORDEM - 1) / 3) {
      reequilibra(raiz, pos_pai, pos_filho);
      return;
    }
  }
}*/

int arvB_remove(ArvB *raiz, int valor) {
  if (*raiz == NULL)
    return 0; // Árvore vazia

  int i = 0;
  while (i < (*raiz)->qtd && valor > (*raiz)->chaves[i]) {
    i++;
  }
  if ((*raiz)->filhos[i] != NULL)
    return arvB_remove(&((*raiz)->filhos[i]), valor);

  if (i < (*raiz)->qtd && valor == (*raiz)->chaves[i]) {
    // Remove a chave do nó
    for (int j = i; j < (*raiz)->qtd - 1; j++) {
      (*raiz)->chaves[j] = (*raiz)->chaves[j + 1];
    }
    (*raiz)->qtd--;
    int tam = 2 * (ORDEM - 1) / 3;

    if ((*raiz)->filhos[i] != NULL && (*raiz)->qtd < 2 * (ORDEM - 1) / 3) {
      printf("Chegou aqui?\n");
      reequilibra(raiz, i, i);
    }
  }
}

int arvB_busca(ArvB *raiz, int valor) {
  if (*raiz == NULL) {
    return 0; // Árvore vazia
  }

  int i = 0;
  while (i < (*raiz)->qtd && valor > (*raiz)->chaves[i]) {
    i++;
  }

  if (i < (*raiz)->qtd && valor == (*raiz)->chaves[i]) {
    return 1; // Valor encontrado
  }

  if ((*raiz)->filhos[i] != NULL)
    return arvB_busca(&((*raiz)->filhos[i]), valor);

  return 0; // Valor não encontrado
}

int arvB_qtd_nos(ArvB *raiz) {
  if (*raiz == NULL) {
    return 0;
  }

  int total = 1; // Conta o próprio nó

  // printChaves(raiz);
  for (int i = 0; i < (*raiz)->qtd + 1; i++) {
    total += arvB_qtd_nos(&((*raiz)->filhos[i]));
  }

  // printChaves(raiz);
  return total;
}

int arvB_qtd_chaves(ArvB *raiz) {
  if (*raiz == NULL) {
    return 0;
  }

  int total = (*raiz)->qtd;
  for (int i = 0; i < (*raiz)->qtd + 1; i++) {
    total += arvB_qtd_chaves(&((*raiz)->filhos[i]));
  }

  return total;
}

void printChaves(ArvB *raiz) { // printa as chaves de um no
  for (int i = 0; i < (*raiz)->qtd; i++)
    printf("%d ", (*raiz)->chaves[i]);
  printf("\n");
}

int compara(const void *a, const void *b) { // usada no qsort
  int x = *(const int *)a;
  int y = *(const int *)b;

  if (x > y)
    return 1;
  else if (x == y)
    return 0;
  else
    return -1;
}

int alturaNo(ArvB *no) {
  if (no == NULL) {
    return -1; // Nó nulo não tem altura
  } else {
    int maxAlturaFilhos = -1; // Altura -1 para considerar nós que não existem
    for (int i = 0; i <= (*no)->qtd; i++) {
      int alturaFilho = alturaNo(&((*no)->filhos[i]));
      if (alturaFilho > maxAlturaFilhos) {
        maxAlturaFilhos = alturaFilho;
      }
    }
    return maxAlturaFilhos + 1;
  }
}

void redistribui(ArvB *irmao1, ArvB *irmao2, int valor){
    unsigned int tam = (*irmao1)->qtd + (*irmao2)->qtd + 2;//quantidade de cada nó que vai ser distribuido + chave separadora no pai + valor
    int i , j;
    int *vetAux = malloc(sizeof(int)*tam);
    //passa o primeiro filho pro auxiliar
    for(i = 0; i < (*irmao1)->qtd; i++)
      {
        vetAux[i] = (*irmao1)->chaves[i];
      }
    //passa o separador vindo do pai
    int ChPai, idxPai;//chave separadora vinda do pai e posicao da chave separadora do pai
    int LimInf = (*irmao1)->chaves[(*irmao1)->qtd-1]; // PEGA O ULTIMO VALOR DO VETOR CHEIO
    int LimSup = (*irmao2)->chaves[0]; // PEGA O PRIMEIRO VALOR DO VETOR COM ESPAÇO
    for(i = 0; i < (*irmao1)->pai->qtd; i++)//percore o vetor de chaves até encontrar a chave separadora entre os dois filhos 
    //ARRUMAR QUAL EH O SUPERIOR OU INFERIOR
    {
        if((*irmao1)->pai->chaves[i] >  LimInf && (*irmao1)->pai->chaves[i] <  LimSup)
        {
            ChPai = (*irmao1)->pai->chaves[i];
            idxPai = i;
            break;
        }
    }
    vetAux[(*irmao1)->qtd] = ChPai; 
    //passa o vetor com espaço para o auxiliar
    for(i = (*irmao1)->qtd+1, j = 0; i < (*irmao2)->qtd+(*irmao1)->qtd+1; i++, j++)
    {
        vetAux[i] = (*irmao2)->chaves[j];
    } 
    //passa o valor a ser inserido
    vetAux[tam-1] = valor;
    qsort(vetAux, (size_t)tam, sizeof(int), compara);
    //distribuindo entre os vetores
    //primeiro
    double qtdPrimeiro = (((double)tam)-1)/2.0;
    (*irmao1)->qtd = 0;
    for(i = 0; i < ceil(qtdPrimeiro); i++)
    {
        (*irmao1)->chaves[i] = vetAux[i];
        (*irmao1)->qtd++;
    }
    
    //raiz
    (*irmao1)->pai->chaves[idxPai] = vetAux[(int)ceil(qtdPrimeiro)];
    //segundo irmão
    (*irmao2)->qtd = 0;
    for(i = ceil(qtdPrimeiro)+1, j= 0; i < tam; i++, j++)
    {
        (*irmao2)->chaves[j] = vetAux[i];
        (*irmao2)->qtd++;
    }
    free(vetAux);
}
int NoFolha(ArvB *no) {
  if ((*no)->filhos[0] == NULL)
    return 1;
  else
    return 0; // passou pela verificacao
}

void inicializa(struct NO *no) {
  // DEIXA COMO NULL OS FILHOS DO NOVO NO
  for (int i = 0; i < ORDEM - 1; i++)
    no->filhos[i] = NULL;
  // ZERA A QTDE
  no->qtd = 0;
}

void arvB_imprime(ArvB *raiz) {
  if (*raiz != NULL) {
    printf("Raiz: ");
    for (int i = 0; i < (*raiz)->qtd; i++)
      printf("%d ", (*raiz)->chaves[i]);
    printf("\n");
    for (int i = 0; i <= (*raiz)->qtd; i++) {
      if ((*raiz)->filhos[i] != NULL) {
        printf("Filho %d: ", i + 1);
        for (int j = 0; j < (*raiz)->filhos[i]->qtd; j++)
          printf("%d ", (*raiz)->filhos[i]->chaves[j]);
        printf("\n");
      }
    }
  }
}