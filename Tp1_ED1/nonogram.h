#ifndef nonogram_h
#define nonogram_h

/**
 * @typedef Dicas
 * Estrutura para armazenar dicas de um nonograma.
 */
typedef struct dicas Dicas;

/**
 * @typedef Nonograma
 * Estrutura para representar um nonograma.
 */
typedef struct nonograma Nonograma;

/**
 * @brief Aloca memória para a estrutura Dicas.
 * 
 * @param n O número de dicas a serem armazenadas.
 * @return Ponteiro para a estrutura Dicas alocada.
 */
Dicas *DicksAllocate(int n);

/**
 * @brief Aloca memória para a estrutura Nonograma.
 * 
 * @param n O tamanho do nonograma.
 * @return Ponteiro para a estrutura Nonograma alocada.
 */
Nonograma *NonogrammAllocate(int n);

/**
 * @brief Libera a memória alocada para um Nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma a ser liberada.
 * @return NULL após liberar a memória.
 */
Nonograma *NonogrammFree(Nonograma *nonograma);

/**
 * @brief Lê os dados de um nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma onde os dados serão armazenados.
 */
void NonogrammRead(Nonograma *nonograma);

/**
 * @brief Imprime os dados de um nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma a ser impressa.
 */
void NonogrammPrint(Nonograma *nonograma);

/**
 * @brief Joga no nonograma, marcando uma posição.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma.
 * @param i Linha da posição a ser jogada.
 * @param j Coluna da posição a ser jogada.
 * @param solutions Ponteiro para o vetor de soluções.
 */
void NonogrammPlay(Nonograma *nonograma, int i, int j, int* solutions);

/**
 * @brief Realiza uma jogada no nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma.
 * @param lin Linha da posição a ser jogada.
 * @param col Coluna da posição a ser jogada.
 */
void play(Nonograma *nonograma, int lin, int col);

/**
 * @brief Inicializa os dados de um nonograma.
 * 
 * @param nonograma Ponteiro para a estrutura Nonograma a ser inicializada.
 */
void NonogrammInicio(Nonograma *nonograma);

#endif
