
/*
    Este TP foi desenvolvido em colaboração pelos discentes:
     
    Thayllon Bragança
    Thiago Zanete
*/
#include "nonogram.h"
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    Nonograma *nono = NonogrammAllocate(n);
    
    NonogrammInicio(nono);
    NonogrammRead(nono);

    play(nono, 0, 0);

    NonogrammFree(nono);

    return 0;
}