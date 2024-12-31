#include "nonogram.h"
#include <stdio.h>
#include <stdlib.h>

// armazenar dicas
struct dicas {
  int *linhas;
  int *colunas;
  int lqnt;
  int cqnt;
  int l;
  int c;
};

// armazenar o jogo, dimensão e dicas
struct nonograma {
  char **mat;
  Dicas *dicas;
  int n;
};

// aloca um vetor de dicas do tamanho n*2, para cada Dicas aloca um vetor com a
// tanto de dicas para cada linha e coluna
Dicas *DicksAllocate(int n) {
  Dicas *dicas = malloc(n * 2 * sizeof(Dicas));
  for (int i = 0; i < n; i++) {
    dicas[i].colunas = malloc((n / 2) + 1 * sizeof(int));
  }
  for (int i = n; i < n * 2; i++) {
    dicas[i].linhas = malloc((n / 2) + 1 * sizeof(int));
  }
  return dicas;
}

// alocar o nonograma com as dicas corretamente
Nonograma *NonogrammAllocate(int n) {
  Nonograma *nonograma = malloc(n * sizeof(Nonograma));
  nonograma->mat = malloc(n * sizeof(char *));
  for (int i = 0; i < n; i++) {
    nonograma->mat[i] = malloc(n * sizeof(char));
  }
  nonograma->n = n;
  nonograma->dicas = DicksAllocate(n);

  return nonograma;
}

// libera o nonograma
// arrumar isso
Nonograma *NonogrammFree(Nonograma *nonograma) {
  free(nonograma->dicas->linhas);
  free(nonograma->dicas->colunas);
  free(nonograma);
  return NULL;
}

void NonogrammInicio(Nonograma *nonograma) {
  for (int i = 0; i < nonograma->n; i++) {
    for (int j = 0; j < nonograma->n; j++) {
      nonograma->mat[i][j] = ' ';
    }
  }
}
// leitura das linhas(0,n-1), colunas(n, n*2-1)
void NonogrammRead(Nonograma *nonograma) {
  printf("Vamos ler\n");
  for (int i = 0; i < nonograma->n; i++) {
    int j = 0;
    while (scanf("%d", &nonograma->dicas[i].colunas[j]) == 1) {

      char c = getchar();

      j++;
      if (c == EOF || c == '\n')
        break;
      if (ungetc(c, stdin) == EOF)
        break;
    }

    nonograma->dicas[i].cqnt = j;
  }

  for (int i = nonograma->n; i < (nonograma->n) * 2; i++) {
    int j = 0;

    while (scanf("%d", &nonograma->dicas[i].linhas[j]) == 1) {
      char c = getchar();

      j++;
      if (c == EOF || c == '\n')
        break;
      if (ungetc(c, stdin) == EOF)
        break;
    }

    nonograma->dicas[i].lqnt = j;
  }
  printf("\n[Leu]\n");
}

// printa as dicas pra ver se tá certo
void NonogrammPrint(Nonograma *nonograma) {

  for (int i = 0; i < nonograma->n; i++) {
    for (int j = 0; j < nonograma->n; j++) {
      printf("[%c]", nonograma->mat[i][j]);
    }
    printf("\n");
  }

  return;
}

void NonogrammPlay(Nonograma *nonograma, int i, int j) {
  if (i == nonograma->n || j == nonograma->n) {
    return;
  }
  if (!(nonograma->dicas[j].colunas[0] == nonograma->dicas[j].c ||
        nonograma->dicas[nonograma->n + i].linhas[0] ==
            nonograma->dicas[nonograma->n + i].l)) {
    nonograma->mat[i][j] = '*';
    nonograma->dicas[j].c++;
    nonograma->dicas[nonograma->n + i].l++;
    // return;
  }

  // recursão nanogrammplay
  NonogrammPlay(nonograma, i, j + 1);
  /*
                0   1  2  3  4  5
                [2][0][1][2][0][1]

                    d   2  0  1
                     i  0  1  2
                     
                  2 0  [*][ ][*]
                  0 1  [ ][ ][ ]
                  1 2  [*][ ][ ]
  */
  NonogrammPlay(nonograma, i + 1, j);
}