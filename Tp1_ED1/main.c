#include "nonogram.h"
#include <stdio.h>

int main() {
    int n;
    printf("\nTamanho do tabuleiro: ");
    scanf("%d", &n);

    Nonograma *nono = NonogrammAllocate(n);
    NonogrammInicio(nono);
    NonogrammRead(nono);
    NonogrammPrint(nono);

    NonogrammPlay(nono, 0, 0);

    printf("\nSolução:\n");
    NonogrammPrint(nono);
    NonogrammFree(nono);

    return 0;
}