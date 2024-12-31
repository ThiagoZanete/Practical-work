#include "nonogram.h"
#include <stdio.h>

int main() {
  // Dicas *tips = DickAllocate(5);
  int n;
  printf("\nn\n");
  scanf("%d", &n);
  Nonograma *nono = NonogrammAllocate(n);
  // printf("\n1\n");
  NonogrammInicio(nono);
  NonogrammRead(nono);
  NonogrammPrint(nono);

  NonogrammPlay(nono, 0, 0);

  printf("\nSolution:\n");
  NonogrammPrint(nono);
  NonogrammFree(nono);

  printf("\nOk\n");
  return 0;
}