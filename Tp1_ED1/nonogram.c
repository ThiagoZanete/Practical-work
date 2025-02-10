#include "nonogram.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @typedef Dicas
 * Estrutura para armazenar dicas de um nonograma.
 */
struct dicas {
    int *linhas;
    int *colunas;
    int lqnt; // quantidade total de dicas na linha
    int cqnt; // quantidade total de dicas na coluna
    int l;    // quantidade preenchida nessa linha
    int c;    // quantidade preenchina nessa coluna
};

/**
 * @typedef Nonograma
 * Estrutura para representar um nonograma.
 */
struct nonograma {
    char **mat;
    Dicas *dicas;
    int n;
};

/**
 * @brief Aloca memória para a estrutura Dicas.
 * 
 * @param n O número de dicas a serem armazenadas.
 * @return Ponteiro para a estrutura Dicas alocada.
 */
Dicas *DicksAllocate(int n) {
    Dicas *dicas = malloc(n * 2 * sizeof(Dicas));
    for (int i = 0; i < n * 2; i++) {
        dicas[i].linhas = NULL; // Inicializa como NULL
        dicas[i].colunas = NULL; // Inicializa como NULL
    }

    for (int i = 0; i < n; i++) {
        dicas[i].colunas = malloc((n / 2 + 1) * sizeof(int));
        for (int j = 0; j < (n / 2 + 1); j++) {
            dicas[i].colunas[j] = 0; // Inicializar com 0
        }
    }

    for (int i = n; i < n * 2; i++) {
        dicas[i].linhas = malloc((n / 2 + 1) * sizeof(int));
        for (int j = 0; j < (n / 2 + 1); j++) {
            dicas[i].linhas[j] = 0; // Inicializar com 0
        }
    }

    return dicas;
}

/**
 * @brief Aloca memória para a estrutura Nonograma.
 * 
 * @param n O tamanho do nonograma.
 * @return Ponteiro para a estrutura Nonograma alocada.
 */
Nonograma *NonogrammAllocate(int n) {
    Nonograma *nonograma = malloc(1 * sizeof(Nonograma));
    nonograma->mat = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        nonograma->mat[i] = malloc(n * sizeof(char));
    }
    nonograma->n = n;
    nonograma->dicas = DicksAllocate(n);

    return nonograma;
}

/**
 * @brief Libera a memória alocada para um Nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma a ser liberada.
 * @return NULL após liberar a memória.
 */
Nonograma *NonogrammFree(Nonograma *nonograma) {
    for (int i = 0; i < nonograma->n * 2; i++) {
        if (nonograma->dicas[i].linhas != NULL) {
            free(nonograma->dicas[i].linhas);
        }
        if (nonograma->dicas[i].colunas != NULL) {
            free(nonograma->dicas[i].colunas);
        }
    }
    free(nonograma->dicas);
    for (int i = 0; i < nonograma->n; i++) {
        free(nonograma->mat[i]);
    }
    free(nonograma->mat);
    free(nonograma);
    return NULL;
}

/**
 * @brief Inicializa os dados de um nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma a ser inicializada.
 */
void NonogrammInicio(Nonograma *nonograma) {
    for (int i = 0; i < nonograma->n; i++) {
        for (int j = 0; j < nonograma->n; j++) {
            nonograma->mat[i][j] = '.';
        }
    }
}


/**
 * @brief Lê os dados de um nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma onde os dados serão armazenados.
 */
void NonogrammRead(Nonograma *nonograma) {
    for (int i = 0; i < nonograma->n; i++) {
        scanf("%d", &nonograma->dicas[i].cqnt);
        if (nonograma->dicas[i].cqnt > (nonograma->n / 2 + 1)) {
            fprintf(stderr, "Error: Too many hints for column %d\n", i);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < nonograma->dicas[i].cqnt; j++) {
            scanf("%d", &nonograma->dicas[i].colunas[j]);
        }
    }

    for (int i = nonograma->n; i < nonograma->n * 2; i++) {
        scanf("%d", &nonograma->dicas[i].lqnt);
        if (nonograma->dicas[i].lqnt > (nonograma->n / 2 + 1)) {
            fprintf(stderr, "Error: Too many hints for row %d\n", i - nonograma->n);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < nonograma->dicas[i].lqnt; j++) {
            scanf("%d", &nonograma->dicas[i].linhas[j]);
        }
    }
}

/**
 * @brief Imprime os dados de um nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma a ser impressa.
 */
void NonogrammPrint(Nonograma *nonograma) {
    for (int i = 0; i < nonograma->n; i++) {
        for (int j = 0; j < nonograma->n; j++) {
            printf("%c ", nonograma->mat[i][j]);
        }
        printf("\n");
    }
    return;
}

/*
 * Função de complexidade:
 * Col = n
 * f(n) = n+1
 *
 * Notação Assintótica:
 * O(n+1) = O(n)
 *
 * ----------------------------------------------------------------
 *
 *  @brief Verifica se uma linha do nonograma está em conformidade com as dicas.
 * 
 * Essa função verifica se a linha do nonograma, até a coluna fornecida, está consistente com as dicas de linhas. 
 * A verificação é feita contando os blocos de células marcadas ('*') e comparando com as dicas fornecidas.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma que contém o tabuleiro e as dicas.
 * @param lin A linha do nonograma a ser verificada.
 * @param col A coluna do nonograma até a qual a verificação será feita.
 * @param position A posição atual da dica a ser verificada.
 * @return Retorna 1 se a linha está em conformidade com as dicas, caso contrário retorna 0.
 */

int checkLine(Nonograma *nonograma, int lin, int col, int position) {
    int count = 0;

    for (int i = 0; i <= col; i++) {
        if (nonograma->mat[lin][i] == '*') {
            count++;
            if (count > nonograma->dicas[nonograma->n + lin].linhas[position]) {
                return 0; // Excedeu o permitido pela dica atual
            }
        } else if (count > 0) {
            // Separamos um bloco, verificamos se o bloco corresponde à dica
            if (count != nonograma->dicas[nonograma->n + lin].linhas[position]) {
                return 0; // Bloco incompleto ou incorreto
            }
            position++;
            count = 0;

            if (position >= nonograma->dicas[nonograma->n + lin].lqnt) {
                return 0; // Excedeu o número de dicas permitidas
            }
        }
    }

    return 1;
}

/*
 * Função de complexidade:
 * Lin = n
 * f(n) = n+1
 *
 * Notação Assintótica:
 * O(n+1) = O(n)
 *
 *---------------------------------------------------------------------------- 
 *
 * @brief Verifica se uma coluna do nonograma está em conformidade com as dicas.
 * 
 * Essa função verifica se a coluna do nonograma, até a linha fornecida, está consistente com as dicas de colunas. 
 * A verificação é feita contando os blocos de células marcadas ('*') e comparando com as dicas fornecidas.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma que contém o tabuleiro e as dicas.
 * @param lin A linha do nonograma até a qual a verificação será feita.
 * @param col A coluna do nonograma a ser verificada.
 * @param position A posição atual da dica a ser verificada.
 * @return Retorna 1 se a coluna está em conformidade com as dicas, caso contrário retorna 0.
 */
int checkCol(Nonograma *nonograma, int lin, int col, int position) {
    int count = 0;


    for (int i = 0; i <= lin; i++) {
        if (nonograma->mat[i][col] == '*') {
            count++;
            if (count > nonograma->dicas[col].colunas[position]) {
                return 0; // Excedeu o permitido pela dica atual
            }
        } else if (count > 0) {
            // Separamos um bloco, verificamos se o bloco corresponde à dica
            if (count != nonograma->dicas[col].colunas[position]) {
                return 0; // Bloco incompleto ou incorreto
            }
            position++;
            count = 0;

            if (position >= nonograma->dicas[col].cqnt) {
                return 0; // Excedeu o número de dicas permitidas
            }
        }
    }

    return 1;
}


/*
 * Função de complexidade:
 * checkCol = n, checkLin = n        No pior caso, analisando os ultimos blocos da lina/coluna
 *
 * Logo,
 * F(n+m) = 2n +1
 *
 * Notação Assintótica:
 * O(2n+1) = O(n)
 *
 *-----------------------------------------------------------------------------
 *
 * @brief Verifica se a inserção de um valor no nonograma é válida.
 * 
 * Essa função verifica se a posição no nonograma está de acordo com as dicas das linhas e colunas associadas.
 * Ela chama as funções `checkCol` e `checkLine` para realizar a validação das dicas.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma que contém o tabuleiro e as dicas.
 * @param lin A linha onde a inserção será feita.
 * @param col A coluna onde a inserção será feita.
 * @return Retorna 1 se a inserção é válida de acordo com as dicas, caso contrário retorna 0.
 */

int checkInsertion(Nonograma *nonograma, int lin, int col) {

    int condition = 1;

    condition = checkCol(nonograma, lin, col, 0);

    if(condition){
        condition = checkLine(nonograma, lin, col, 0);
    }

    if (nonograma->dicas[col].cqnt == 0 ||
        nonograma->dicas[nonograma->n + lin].lqnt == 0) {
        condition = 0;
    }

    return condition;
}


/*
 * Função de Complexidade:
 * Assim como na checkInsertion, a função serada da por:
 *
 * f(n+m) = n+m
 *
 * Já que no pior caso, Columns  totais sempre sera maior que a quantidade totais de dicas.
 *
 * Notação Assintótica:
 * O(n+m) = O(n)
 * 
 *----------------------------------------------------------------------------------------
 *
 * @brief Verifica se uma linha do nonograma está completamente preenchida conforme as dicas.
 * 
 * Essa função verifica se a linha foi completamente preenchida de acordo com as dicas fornecidas. 
 * Ela soma as quantidades de células marcadas ('*') e compara com o total exigido pelas dicas.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma que contém o tabuleiro e as dicas.
 * @param lin A linha do nonograma a ser verificada.
 * @param col A coluna até a qual a verificação será feita.
 * @return Retorna 1 se a linha está completamente preenchida conforme as dicas, caso contrário retorna 0.
 */
int checkIsCompletedLine(Nonograma *nonograma, int lin, int col) {
    int totalInLine = 0;
    for (int i = 0; i < nonograma->dicas[nonograma->n + lin].lqnt; i++) {
        totalInLine += nonograma->dicas[nonograma->n + lin].linhas[i]; // 1
    }

    int count = 0;
    for (int i = 0; i <= col; i++) {
        if (nonograma->mat[lin][i] == '*') { // 1
            count++;
        }
    }

    return count == totalInLine;
}


/*
 * Função de Complexidade:
 *
 * Para cada chamada de NonogrammPlay chamamos temos mais 2 dela mesma.
 * A equação seria:
 *
 *          T(n) = 2*T(n-1)
 * T(n) =
 *          T(0) = 1
 * T(n-1) é a quantidade restante para resolver o restante das células.
 *
 * Já no pior caso, de visitar todas a células, temos n = n*n
 *
 * T(n*n) = 2*T(n*n-1) + O(n)
 *
 * Expandindo:
 *
 * T(n*n) = 2*T(n*n-1) + O(n)
 * T(n*n-1) = 2*(2*T(n*n-2)) + O(n)
 * T(n*n-2) = 2*(2*(2*T(n*n-3))) + O(n)
 * T(n*n-3) = 2*(2*(2*(2*T(n*n-4)))) + O(n)
 * .
 * .
 * .
 * T(n*n-k) = 2^(k)*T(0)
 * T(0) = 1
 *
 *
 *
 * Prova:
 *
 * n=2
 *
 * ------Daqui------
 * T(4) = 2¹*T(3) + O(n)
 * T(3) = 2²*T(2)) + O(n)
 * T(2) = 2³*T(1))) + O(n)
 * T(1) = 2⁴*(2*T(0)))) + O(n)
 * -----Ate aqui-----
 * Elevamos o 2, k vezes, k=4
 *
 * T(k+1) = 1 -> T(0)=1
 * k+1=n² -> k=n²-1
 *
 * Logo,
 * k = n²-1
 * T(n) = 2((k-1)) + 1 + O(n)
 *
 * Logo O(2^(n²-1) + n + 1 ) = O(2^n²)
 *
 * ----------------------------------------------------------
 *
 * @brief Joga no nonograma, marcando uma posição.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma.
 * @param i Linha da posição a ser jogada.
 * @param j Coluna da posição a ser jogada.
 * @param solutions Ponteiro para o vetor de soluções.
 */
void NonogrammPlay(Nonograma *nonograma, int lin, int col, int *solutions) {

    if (lin == nonograma->n) {
        *solutions+=1;
        printf("SOLUTION %d:\n", *solutions);
        NonogrammPrint(nonograma); // Imprime a solução
        printf("\n"); // Adiciona uma linha em branco entre soluções
        return; // Continua explorando outras soluções
    }

    if (col == nonograma->n) {
        if (!checkIsCompletedLine(nonograma, lin, col-1)) {
            return; // Linha incompleta
        }
        NonogrammPlay(nonograma, lin+1, 0, solutions); // Próxima Coluna
        return;
    }

    nonograma->mat[lin][col] = '*';
    if (checkInsertion(nonograma, lin, col)) {
        NonogrammPlay(nonograma, lin, col+1, solutions); // Avança para a próxima coluna
    }

    nonograma->mat[lin][col] = '.';
    NonogrammPlay(nonograma, lin, col+1, solutions);
}


/**
 * @brief Realiza uma jogada no nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma.
 * @param lin Linha da posição a ser jogada.
 * @param col Coluna da posição a ser jogada.
 */
void play(Nonograma *nono, int lin, int col){
    int solutions =0;
    NonogrammPlay(nono, lin, col, &solutions);

    if(solutions>0){
        printf("Total of solutions: %d\n", solutions);
    }else{
        printf("No solution was found!\n");
    }

}