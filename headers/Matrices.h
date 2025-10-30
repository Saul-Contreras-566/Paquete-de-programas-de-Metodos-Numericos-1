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

double *Leer_entradas_de_matriz (int filas, int columnas);
Matriz Leer_matriz ();
double Determinante (Matriz matriz);
int Verificar_EDD (Matriz matriz); // Verifica que la matriz sea Estrictamente Dominante Diagonalmente
double Norma_espectral (int numero_entradas, double *entrada);

#endif
