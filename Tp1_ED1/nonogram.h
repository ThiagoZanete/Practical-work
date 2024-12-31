#ifndef NONOGRAM_H
#define NONOGRAM_H

typedef struct {
    int dimension;
    char **board;
    int **row_hints;
    int **col_hints;
} Nonogram;

// Funções para manipulação do Nonograma
Nonogram* NonogramAllocate(int dimension);
void NonogramFree(Nonogram* ng);
void NonogramRead(Nonogram* ng);
void NonogramPrint(Nonogram* ng);
int NonogramPlay(Nonogram* ng);
int checkSolution(Nonogram* ng);

#endif
