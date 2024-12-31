#ifndef nonogram_h
#define nonogram_h

typedef struct dicas Dicas;
typedef struct nonograma Nonograma;

Dicas *DicksAllocate(int n);

Nonograma *NonogrammAllocate(int n);

Nonograma *NonogrammFree(Nonograma *nonograma);

void NonogrammRead(Nonograma *nonograma);

void NonogrammPrint(Nonograma *nonograma);

void NonogrammPlay(Nonograma *nonograma, int i, int j);

void NonogrammInicio(Nonograma *nonograma);

#endif