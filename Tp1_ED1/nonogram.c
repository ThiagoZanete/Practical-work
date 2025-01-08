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
    for (int i = 0; i < nonograma->n * 2; i++) {
        free(nonograma->dicas[i].linhas);
        free(nonograma->dicas[i].colunas);
    }
    free(nonograma->dicas);
    for (int i = 0; i < nonograma->n; i++) {
        free(nonograma->mat[i]);
    }
    free(nonograma->mat);
    free(nonograma);
    return NULL;
}

void NonogrammInicio(Nonograma *nonograma) {
    for (int i = 0; i < nonograma->n; i++) {
        for (int j = 0; j < nonograma->n; j++) {
            nonograma->mat[i][j] = '.';
        }
    }
}
// leitura das linhas(0,n-1), colunas(n, n*2-1)
void NonogrammRead(Nonograma *nonograma) {
    printf("Vamos ler\n");
    for (int i = 0; i < nonograma->n; i++) {
        scanf("%d", &nonograma->dicas[i].cqnt);
        for (int j = 0; j < nonograma->dicas[i].cqnt; j++) {
            scanf("%d", &nonograma->dicas[i].colunas[j]);
        }
    }

    for (int i = nonograma->n; i < (nonograma->n) * 2; i++) {
        scanf("%d", &nonograma->dicas[i].lqnt);
        for (int j = 0; j < nonograma->dicas[i].lqnt; j++) {
            scanf("%d", &nonograma->dicas[i].linhas[j]);
        }
    }
    printf("\n[Leu]\n");
}

// printa as dicas pra ver se tá certo
void NonogrammPrint(Nonograma *nonograma) {

    for (int i = 0; i < nonograma->n; i++) {
        for (int j = 0; j < nonograma->n; j++) {
            printf(" %c ", nonograma->mat[i][j]);
        }
        printf("\n");
    }

    return;
}


void NonogrammPlay(Nonograma *nonograma, int i, int j) {
    if (i == nonograma->n) {
      return;
    }
    if (j == nonograma->n){
      NonogrammPlay(nonograma, i + 1, 0);  // Reinicia a coluna para 0 na próxima linha
      return;
    }

    int conditionCol = 1, conditionLin = 1, aux = 0, aux2 = 0;
    for (int k = 0; k < nonograma->dicas[j].cqnt; k++) {
        //aux += nonograma->dicas[j].colunas[k];
        int a = 0;
        int initpos = i - 1;
        int maxdicas = nonograma->dicas[j].colunas[k];
        for (int y = initpos; y >= initpos - maxdicas + 1 && y >= 0; y--) {

            if (nonograma->mat[y][j] == '*') {
                a++;
            }else{
                break;
            }
        }
        if (a != maxdicas) {
            conditionCol = 0;
            break;
        }
        aux += maxdicas;

    }


    for (int k = 0; k < nonograma->dicas[nonograma->n + i].lqnt; k++) {
        //aux2 += nonograma->dicas[nonograma->n + i].linhas[k];
        int a = 0;
        int maxdicas = nonograma->dicas[nonograma->n + i].linhas[k];
        for (int y = j - 1; y >= j - maxdicas && y >= 0 && conditionCol; y--) {

            if (nonograma->mat[i][y] == '*') {
                a++;
            } else{
                break;
            }

        }

        if (a != maxdicas) {
            conditionLin = 0;
            break;
        }
        aux2+= maxdicas;

    }

    if (conditionCol && conditionLin && aux != nonograma->dicas[j].c && aux2 != nonograma->dicas[nonograma->n + i].l) {

        nonograma->mat[i][j] = '*';
        nonograma->dicas[j].c++;
        nonograma->dicas[nonograma->n + i].l++;
    }

   // NonogrammPlay(nonograma, i+1, j);
    NonogrammPlay(nonograma, i , j+1);
}




