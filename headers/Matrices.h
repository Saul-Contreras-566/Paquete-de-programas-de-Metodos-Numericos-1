/*
Funciones con matrices.
*/





#ifndef MATRICES
#define MATRICES

typedef struct {
	int filas;
	int columnas;
	double *entrada;
} Matriz;

// Funciones básicas con matrices
double *Leer_entradas_de_matriz (int filas, int columnas);
Matriz Leer_matriz ();
double Determinante (Matriz matriz);
int Verificar_EDD (Matriz matriz); // Verifica que la matriz sea Estrictamente Dominante Diagonalmente
double Norma_espectral (int numero_entradas, double *entrada);
int Es_simetrica (Matriz matriz);
void Normalizar (Matriz vector, double norma);
void Invertir_matriz (Matriz matriz);

// Funciones para factorización de matrices
void Factorizacion_doolittle (Matriz *lower, Matriz *upper, Matriz matriz);
Matriz Factorizacion_cholesky (Matriz matriz, int *error);
void Factorizacion_crout (Matriz *lower, Matriz *upper, Matriz matriz);

// Otras funciones
void Imprimir_matriz (Matriz matriz); // Imprime en forma de matriz
void Imprimir_vector (Matriz matriz); // Pensado para imprimir vectores fila o vectores columna
void Copiar_matriz (Matriz original, Matriz *copia);

#endif
