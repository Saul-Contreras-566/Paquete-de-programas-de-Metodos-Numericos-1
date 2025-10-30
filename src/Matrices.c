/*
Código de las funciones con matrices.
*/





#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Funciones_basicas.h"
#include "Matrices.h"



double *Leer_entradas_de_matriz (int filas, int columnas) {
	int i, j; // Variables para iteraciones
	int x, y; // Variables para la selección de la entrada a corregir
	int respuesta; // Respuesta del usuaior para corregir otra entrada o no
	double *entrada = malloc (sizeof (double) * filas * columnas); // Reservando memoria dinámica para las entradas

	// Leyendo las entradas
	for (i = 0; i < filas; i++)
		for (j = 0; j < columnas; j++) {
			printf ("Entrada (%d, %d) = ", i + 1, j + 1);
			entrada[i * columnas + j] = Leer_real ();
		}
	
	// Corrigiendo entradas
	do {
		// Mostrando matriz
		for (i = 0; i < filas; i++) {
			printf ("| ");
			for (j = 0; j < columnas; j++)
				printf ("%lf |", entrada[i * columnas + j]);
			printf ("\n");
		}

		// Preguntando por la corrección
		respuesta = Pregunta_cerrada ("¿Quiére corregir alguna entrada?");

		// Corrigiendo en caso de quererlo
		if (respuesta == 1) {
			// Pidiendo ubicación
			puts ("¿Cuál es la fila de la entrada?");
			x = Leer_entero_entre (1, filas);
			puts ("¿Cuál es la columna de la entrada?");
			y = Leer_entero_entre (1, columnas);

			// Actualizando
			puts ("Inserte el nuevo número:");
			entrada[(x - 1) * columnas + y - 1] = Leer_real ();
		}
	}
	while (respuesta == 1);
	
	return entrada;
}



Matriz Leer_matriz () {
	Matriz lectura;

	// Pidiendo las dimensiones de la matriz
	puts ("¿Cuántas filas tiene la matriz?");
	lectura.filas = Leer_entero_que_sea (">=", 1);
	puts ("¿Cuántas columnas tiene la matriz?");
	lectura.columnas = Leer_entero_que_sea (">=", 1);

	// Leyendo entradas
	lectura.entrada = Leer_entradas_de_matriz (lectura.filas, lectura.columnas);

	// Devolviendo la matriz
	return lectura;
}



static int Factorial (int numero) {
	int resultado = 1;
	int i; // Variable para iteraciones

	for (i = 1; i <= numero; i++)
		resultado *= i;
	
	return resultado;
}



double Determinante (Matriz matriz) {
	int i, j, k, m; // Variables para iteraciones
	int cursor = 0, disponible, pasos = Factorial(matriz.filas);
	double determinante = 0.0, temporal;

	// Declarando variables inicializadas
	int *seleccionados = malloc(matriz.filas * sizeof(int));
	double *signos = malloc(matriz.filas * sizeof(double));
	for (i = 0; i < matriz.filas; i++) {
		seleccionados[i] = 0;
		signos[i] = -1.0;
	}

	// Calculando determinante
	for (i = 0; i < pasos; i++) {
		// Seleccionando columna para la j-ésima fila
		for (j = cursor; j >= 0 && j < matriz.filas; j++) {
			signos[j] *= -1.0; // Intercalando signo
			disponible = 0;
			for (k = seleccionados[j]; disponible == 0; k++) {
				if (k < matriz.columnas) {
					// En caso de que no sobrepase las columnas

					// Verificando disponibilidad de la columna
					disponible = 1;
					for (m = 0; m < j; m++)
						if (seleccionados[m] == k)
							disponible = 0;

					// Seleccionando columna en caso de estar disponible
					if (disponible == 1)
						seleccionados[j] = k;
				} else {
					// En caso de que sobrepase las columnas

					seleccionados[j] = 0; // Seleccionando la primera columna en la fila actual
					seleccionados[j - 1] += 1; // Seleccionando siguiente columna de la fila anterior
					signos[j] = -1.0; // Cambiando signo para que cuando se vuelva a llegar a esta fila el signo sea positivo
					j -= 2; // Regresando dos filas antes para que, cuando se aumente 1, quede en la fila anterior
					break; // Cambiando de fila
				}
			}

			// Seleccionando última fila donde se seleccionó una columna
			cursor = j;
		}

		// Multiplicando y sumando
		temporal = 1.0;
		for (j = 0; j < matriz.filas; j++)
			temporal *= matriz.entrada[j * matriz.columnas + seleccionados[j]] * signos[j];
		determinante += temporal;
		seleccionados[matriz.filas - 1] += 1;
	}

	// Liberando memoria
	free(seleccionados);
	free(signos);

	// Regresando determinante
	return determinante;
}



int Verificar_EDD (Matriz matriz) {
	int i, j; // Variables para iteraciones
	double suma; // Para verificar la dominancia
	int edd = 1; // Para indicar si la matriz es EDD o no, suponemos que lo es con 1 para después tratar de desmentirlo y, en caso de no ser EDD, detener el proceso de verificación
	
	// Verificando
	for (i = 0; i < matriz.filas && edd == 1; i++) {
		suma = 0.0;
		for (j = 0; j < matriz.columnas; j++)
			suma += (i == j) ? 0 : fabs (matriz.entrada[i * matriz.columnas + j]);
		edd = (matriz.entrada[i * (matriz.columnas + 1)] > suma) ? 1 : 0;
	}

	// Regresando el resultado de la verificación
	return edd;
}



double Norma_espectral (int numero_entradas, double *entrada) {
	int i; // Variable para iteraciones
	double maximo;

	// Comparando
	maximo = fabs (entrada[0]);
	for (i = 1; i < numero_entradas; i++)
		maximo = (maximo < fabs (entrada[i])) ? fabs (entrada[i]) : maximo;
	
	// Regresando norma espectral
	return maximo;
}
