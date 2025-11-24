/*
Código de los métodos de solución para sistemas de ecuaciones.
*/





#include <stdio.h>
#include <stdlib.h>
#include "Funciones_basicas.h"
#include "Matrices.h"
#include "Metodos_sistemas_ecuaciones.h"



void Gauss_Seidel (Matriz coeficientes) {
	/* Esta función realiza las iteraciones del método de Gauss-Seidel. Primero pide el vector
	inicial (el que se usa para realizar la primera iteración), el máximo de iteraciones a hacer
	y la tolerancia del error relativo. Después comienza a iterar e imprimir el resultado de
	estas. */

	Matriz anterior, resultado, independiente;
	int i, j, k;
	int iteraciones;
	double tolerancia, norma_espectral[2], error, suma;

	// Inicializando el vector independiente, resultado y anterior (el calculado una iteración antes)
	independiente.filas = coeficientes.filas;
	independiente.columnas = 1;
	resultado.filas = coeficientes.filas;
	resultado.columnas = 1;
	anterior.filas = coeficientes.filas;
	anterior.columnas = 1;
	anterior.entrada = (double *) malloc (sizeof (double) * anterior.filas);

	do {
		// Pidiendo los datos iniciales
		puts ("Inserte las entradas del vector independiente:");
		independiente.entrada = Leer_entradas_de_matriz (independiente.filas, 1);
		puts ("Inserte las entradas de tu vector inicial:");
		resultado.entrada = Leer_entradas_de_matriz (resultado.filas, 1);
		puts ("¿Cuántas iteraciones quiere hacer como máximo?");
		iteraciones = Leer_entero_que_sea (">=", 1);
		puts ("¿Cuál es la tolerancia del error relativo?");
		tolerancia = Leer_real_que_sea (">", 0);

		// Iniciando las iteraciones
		// Imprimiendo iteración cero
		puts ("----------");
		printf ("Iteracion #0.\n");
		printf ("Vector: ( %lf", resultado.entrada[0]);
			for (i = 1; i < resultado.filas; i++)
				printf (", %lf", resultado.entrada[i]);
			printf (").\n");
		printf ("Norma espectral: %lf.\n", Norma_espectral (resultado.filas, resultado.entrada));
		puts ("Error relativo: No aplica, es la iteración cero.");
		puts ("¿Se logró la tolerancia?: No aplica, es la iteración cero.");

		// Imprimiendo el resto de iteraciones
		i = 0; // Contador de iteraciones
		norma_espectral[0] = Norma_espectral (resultado.filas, resultado.entrada); // Calculando la norma espectral del vector inicial
		do {
			// Copiando el vector actual como el vector de la iteración anterior
			for (j = 0; j < resultado.filas; j++)
				anterior.entrada[j] = resultado.entrada[j];

			// Evaluando el vector en la matriz
			for (j = 0; j < coeficientes.filas; j++) {
				suma = independiente.entrada[j];
				for (k = 0; k < coeficientes.columnas; k++)
					suma -= (j != k) ? coeficientes.entrada[j * coeficientes.columnas + k] * resultado.entrada[k] : 0;
				resultado.entrada[j] = suma / coeficientes.entrada[j * (coeficientes.columnas + 1)];
			}
			
			// Calculando el error
			for (j = 0; j < resultado.filas; j++)
				anterior.entrada[j] -= resultado.entrada[j];
			norma_espectral[1] = Norma_espectral (resultado.filas, resultado.entrada); // Calculando la norma espectral del vector inicial
			error = Norma_espectral (anterior.filas, anterior.entrada) / norma_espectral[1];
			norma_espectral[0] = norma_espectral[1]; // Desplazando norma espectral para la siguiente iteración
			
			// Imprimiendo
			puts ("----------");
			printf ("Iteracion #%d.\n", i + 1);
			printf ("Vector: ( %lf", resultado.entrada[0]);
				for (j = 1; j < resultado.filas; j++)
					printf (", %lf", resultado.entrada[j]);
				printf (" ).\n");
			printf ("Norma espectral: %lf.\n", norma_espectral[1]);
			printf ("Error relativo: %lf.\n", error);
			printf ("¿Se logró la tolerancia?: %s.\n", (error <= tolerancia ? "Sí" : "No") );

			// Aumentando el valor de i para las iteraciones
			i += 1;
		}
		while (error > tolerancia && i < iteraciones);

		// Imprimiendo el resultado
		puts ("----------");
		puts ("La mejor aproximanción al vector solución es:");
		Imprimir_matriz (resultado);
		printf ("Con un error relativo de: %lf.\n", error);

		// Liberando memoria
		free (resultado.entrada);
		free (independiente.entrada);
	}
	while (Pregunta_cerrada ("¿Quiére resolver el sistema con otro vector independiente?") == 1);

	// Liberando más memoria
	free (anterior.entrada);
}

void Doolittle (Matriz matriz) {
	int i,j; // Variables para iteraciones
	Matriz lower, upper, solucion, independiente;

	// Factorizando la matriz por Doolittle
	Factorizacion_doolittle (&lower, &upper, matriz);

	// Mostrando la factorización
	puts ("De la factorización por Doolittle del sistema se tiene lo siguiente.");
	puts ("Matriz L:");
	Imprimir_matriz (lower);
	puts ("Matriz U:");
	Imprimir_matriz (upper);

	// Solucionando el sistema con los vectores independientes que ingrese el usuario
	do {
		// Pidiendo el vector independiente
		independiente.filas = matriz.filas;
		independiente.columnas = 1;
		puts ("Ingrese el vector independiente a usar:");
		independiente.entrada = Leer_entradas_de_matriz(independiente.filas, independiente.columnas);

		// Inicializando el vector solución
		solucion.filas = matriz.filas;
		solucion.columnas = 1;
		solucion.entrada = (double *) malloc (sizeof (double) * solucion.filas * solucion.columnas);

		// Reemplazando hacia adelante
		for (i = 0; i < matriz.filas; i++) {
			solucion.entrada[i] = independiente.entrada[i];
			for (j = 0; j < i; j++)
				solucion.entrada[i] -= solucion.entrada[j] * lower.entrada[i * lower.columnas + j];
			// solucion.entrada[i] /= lower.entrada[i * matriz.columnas + i];
		}

		// Remplazando hacia atrás
		for (i = matriz.filas - 1; i >= 0 ; i--) {
			for (j = matriz.columnas - 1; j > i; j--) 
				solucion.entrada[i] -= solucion.entrada[j] * upper.entrada[i * upper.columnas + j];
			solucion.entrada[i] /= upper.entrada[i * upper.columnas + i];
		}

		// Mostrando la solución del sistema
		puts ("Vector solución:");
		Imprimir_matriz (solucion);

		// Liberando memoria dinámica
		free (solucion.entrada);
		free (independiente.entrada);
	}
	while (Pregunta_cerrada ("¿Quiére solucionar el sistema con otro vector independiente?") == 1);

	// Liberando memoria de las matrices `lower` y `upper`
	free (lower.entrada);
	free (upper.entrada);
}

void Cholesky (Matriz matriz) {
	int i,j; // Variables de iteración
	Matriz lower, solucion, independiente;
	int error = 0; /* Para verificar que la matriz sea simétrica y definida positiva, presuponemos que todo está bien con
	                  la matriz para luego tratar de hallar un fallo y detener el método. */

	// Verificando simetría
	error = Es_simetrica (matriz);
	if (error == 1) { // En caso de no serlo
		puts ("ERROR: La matriz no es simétrica, por lo que no se puede factorizar por Cholesky.");
		return;
	}

	// Factorizando y averiguando si es definida positiva
	lower = Factorizacion_cholesky (matriz, &error);
	if (error == 1) { // En caso de no ser definida positiva
		puts ("ERROR: La matriz no es definida positiva, por lo que no se puede factorizar por Cholesky.");
		free (lower.entrada);
		return;
	}

	// Mostrando la factorización
	puts ("De la factorización por Cholesky del sistema se tiene lo siguiente.");
	puts ("Matriz L:");
	Imprimir_matriz (lower);

	// Resolviendo el sistema con los vectores independientes que inserte el usuario
	do {
		// Pidiendo el vector independiente
		independiente.filas = matriz.filas;
		independiente.columnas = 1;
		puts ("Inserte el vector independiente:");
		independiente.entrada = Leer_entradas_de_matriz(independiente.filas, independiente.columnas);

		// Inicializando el vector solución
		solucion.filas = matriz.filas;
		solucion.columnas = 1;
		solucion.entrada = (double *) malloc (sizeof (double) * solucion.filas * solucion.columnas);

		// Reemplazando hacia adelante
		for (i = 0; i < matriz.filas; i++) {
			solucion.entrada[i] = independiente.entrada[i];
			for (j = 0; j < i; j++)
				solucion.entrada[i] -= solucion.entrada[j] * lower.entrada[i * matriz.columnas + j];
			solucion.entrada[i] /= lower.entrada[i * matriz.columnas + i];
		}

		// Remplazando hacia atrás
		for (i = matriz.filas - 1; i >= 0 ; i--) {
			for (j = matriz.columnas - 1; j > i; j--) 
				solucion.entrada[i] -= solucion.entrada[j] * lower.entrada[j * lower.columnas + i];
			solucion.entrada[i] /= lower.entrada[i * lower.columnas + i];
		}

		// Mostrando la solución
		puts ("Vector solución:");
		Imprimir_matriz (solucion);

		// Liberando memoria
		free (independiente.entrada);
		free (solucion.entrada);
	}
	while (Pregunta_cerrada ("¿Quiére resolver el sistema con otro vector independiente?") == 1);

	// Liberando memoria dinámica de la matriz `lower`
	free (lower.entrada);
}

void Crout (Matriz matriz) {
	int i,j; // Variables de iteración
	Matriz lower, upper, solucion, independiente;

	// Factorizando por Crout
	Factorizacion_crout (&lower, &upper, matriz);

	// Mostrando la factorización
	puts ("De la factorización por Crout del sistema se tiene lo siguiente.");
	puts ("Matriz L:");
	Imprimir_matriz (lower);
	puts ("Matriz U:");
	Imprimir_matriz (upper);

	// Solucionando el sistema con los vectores independientes que ingrese el usuario
	do {
		// Pidiendo el vector independiente
		independiente.filas = matriz.filas;
		independiente.columnas = 1;
		puts ("Ingrese el vector independiente a usar:");
		independiente.entrada = Leer_entradas_de_matriz(independiente.filas, independiente.columnas);

		// Inicializando el vector solución
		solucion.filas = matriz.filas;
		solucion.columnas = 1;
		solucion.entrada = (double *) malloc (sizeof (double) * solucion.filas * solucion.columnas);

		// Reemplazando hacia adelante
		for (i = 0; i < matriz.filas; i++) {
			solucion.entrada[i] = independiente.entrada[i];
			for (j = 0; j < i; j++)
				solucion.entrada[i] -= solucion.entrada[j] * lower.entrada[i * matriz.columnas + j];
			solucion.entrada[i] /= lower.entrada[i * matriz.columnas + i];
		}

		// Remplazando hacia atrás
		for (i = matriz.filas - 1; i >= 0 ; i--) {
			for (j = matriz.columnas - 1; j > i; j--) 
				solucion.entrada[i] -= solucion.entrada[j] * upper.entrada[i * upper.columnas + j];
		}

		// Mostrando la solución del sistema
		puts ("Vector solución:");
		Imprimir_matriz (solucion);

		// Liberando memoria dinámica
		free (solucion.entrada);
		free (independiente.entrada);
	}
	while (Pregunta_cerrada ("¿Quiére solucionar el sistema con otro vector independiente?") == 1);

	// Liberando memoria de las matrices `lower` y `upper`
	free (lower.entrada);
	free (upper.entrada);
}
