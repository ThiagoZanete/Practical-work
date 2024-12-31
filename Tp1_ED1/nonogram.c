#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nonogram.h"

// Função para alocar memória para o Nonograma
Nonogram* NonogramAllocate(int dimension) {
    Nonogram* ng = (Nonogram*)malloc(sizeof(Nonogram));
    ng->dimension = dimension;
    
    ng->board = (char**)malloc(dimension * sizeof(char*));
    for (int i = 0; i < dimension; i++) {
        ng->board[i] = (char*)malloc(dimension * sizeof(char));
        memset(ng->board[i], '.', dimension * sizeof(char));  // Inicializa com '.'
    }

    ng->row_hints = (int**)malloc(dimension * sizeof(int*));
    ng->col_hints = (int**)malloc(dimension * sizeof(int*));
    
    for (int i = 0; i < dimension; i++) {
        ng->row_hints[i] = (int*)malloc(dimension * sizeof(int));
        ng->col_hints[i] = (int*)malloc(dimension * sizeof(int));
        memset(ng->row_hints[i], 0, dimension * sizeof(int));
        memset(ng->col_hints[i], 0, dimension * sizeof(int));
    }

    return ng;
}

// Função para liberar memória alocada para o Nonograma
void NonogramFree(Nonogram* ng) {
    for (int i = 0; i < ng->dimension; i++) {
        free(ng->board[i]);
        free(ng->row_hints[i]);
        free(ng->col_hints[i]);
    }
    free(ng->board);
    free(ng->row_hints);
    free(ng->col_hints);
    free(ng);
}

// Função para ler o tabuleiro e dicas
void NonogramRead(Nonogram* ng) {
    int i, j;
    // Lê o número de grupos por coluna
    for (i = 0; i < ng->dimension; i++) {
        scanf("%d", &ng->col_hints[i][0]);
        for (j = 1; j < ng->col_hints[i][0]; j++) {
            scanf("%d", &ng->col_hints[i][j]);
        }
    }
    // Lê o número de grupos por linha
    for (i = 0; i < ng->dimension; i++) {
        scanf("%d", &ng->row_hints[i][0]);
        for (j = 1; j < ng->row_hints[i][0]; j++) {
            scanf("%d", &ng->row_hints[i][j]);
        }
    }
}

// Função para imprimir o tabuleiro
void NonogramPrint(Nonogram* ng) {
    for (int i = 0; i < ng->dimension; i++) {
        for (int j = 0; j < ng->dimension; j++) {
            printf("%c", ng->board[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se a solução está correta
int checkSolution(Nonogram* ng) {
    // Verifica se as dicas de linhas e colunas estão sendo atendidas
    for (int i = 0; i < ng->dimension; i++) {
        int row_count = 0, col_count = 0;
        // Verifica linhas
        for (int j = 0; j < ng->dimension; j++) {
            if (ng->board[i][j] == '#') {
                row_count++;
            }
        }
        // Verifica colunas
        for (int j = 0; j < ng->dimension; j++) {
            if (ng->board[j][i] == '#') {
                col_count++;
            }
        }
        
        if (row_count != ng->row_hints[i][0] || col_count != ng->col_hints[i][0]) {
            return 0; // Se qualquer linha ou coluna não estiver correta
        }
    }
    return 1; // Se todas as dicas estiverem corretas
}

// Função para resolver o Nonograma utilizando backtracking
int NonogramPlay(Nonogram* ng) {
    int solutions = 0;
    
    // Tente preencher o Nonograma (simplificado, exemplo básico de preenchimento)
    // Verifica o preenchimento com base nas dicas
    for (int i = 0; i < ng->dimension; i++) {
        for (int j = 0; j < ng->dimension; j++) {
            if (ng->board[i][j] == '.') {
                ng->board[i][j] = '#';  // Preenche uma célula arbitrária
                if (checkSolution(ng)) {
                    solutions++;
                    NonogramPrint(ng);  // Imprime a solução
                }
                ng->board[i][j] = '.';  // Desfaz o preenchimento caso não seja solução
            }
        }
    }

    return solutions;
}
