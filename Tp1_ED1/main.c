#include <stdio.h>
#include "nonogram.h"

int main() {
    int dimension;
    scanf("%d", &dimension);  // Lê a dimensão do tabuleiro

    Nonogram* ng = NonogramAllocate(dimension);  // Aloca o Nonograma
    NonogramRead(ng);  // Lê os dados do Nonograma

    int solutions = NonogramPlay(ng);  // Resolve o Nonograma e imprime a solução
    if (solutions == 0) {
        printf("Nosolutionwasfound!\n");
    } else {
        printf("Totalofsolutions: %d\n", solutions);
    }

    NonogramFree(ng);  // Libera a memória
    return 0;
}
