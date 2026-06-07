/*
Código de la tercera opción del paquete de programas
*/





#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Funciones_basicas.h"
#include "Matrices.h"
#include "Opcion_03.h"



static void Multiplicar (Matriz matriz, Matriz vector, Matriz resultado) {
	/* Función usada para multiplicar la matriz con el vector en una iteración */

	int i, j; // Variables para iteraciones

	for (i = 0; i < matriz.filas; i++) {
		resultado.entrada[i] = 0;
		for (j = 0; j < matriz.columnas; j++)
			resultado.entrada[i] += matriz.entrada[i * matriz.columnas + j] * vector.entrada[j];
	}
}



static double Iterador_potencias (Matriz matriz, Matriz vector, int maximo_iteraciones, double tolerancia) {
	/* Iterador del método de potencias, usado para calcular el valor propio máximo y el mínimo, uno solo a la vez */

	int i; // Variable para iteraciones
	double error, norma_espectral, norma_espectral_anterior;
	Matriz anterior;
	anterior.entrada = NULL;

	// Imprimiendo iteración 0
	puts ("----------");
	puts ("Iteracion #0");
	puts ("Vector: ");
		Imprimir_vector (vector);
	norma_espectral = Norma_espectral (vector.filas, vector.entrada);
	Normalizar (vector, norma_espectral);
	printf ("Norma espectral (valor propio): %.10lf\n", norma_espectral);
	puts ("Vector normalizado: ");
		Imprimir_vector (vector);
	puts ("Error absoluto: No aplica, es la iteración cero.");
	Copiar_matriz (vector, &anterior);
	norma_espectral_anterior = norma_espectral;
	error = tolerancia + 1.0; // Esto solo para asegurar que se puedan iniciar correctamente las iteraciones
	// Imprimiendo el resto de iteraciones
	for (i = 1; i < maximo_iteraciones && error > tolerancia; i ++) {
		// Calculando el valor y vector propio
		Multiplicar (matriz, anterior, vector);
		norma_espectral = Norma_espectral (vector.filas, vector.entrada);
		error = fabs (norma_espectral - norma_espectral_anterior);

		// Imprimiendo el resultado
		puts ("----------");
		printf ("Iteracion #%d\n", i);
		puts ("Vector: ");
			Imprimir_vector (vector);
		Normalizar (vector, norma_espectral);
		printf ("Norma espectral (valor propio): %.10lf\n", norma_espectral);
		puts ("Vector normalizado: ");
			Imprimir_vector (vector);
		printf ("Error absoluto: %.10lf\n", error);

		// Preparando datos para la siguiente iteracion
		norma_espectral_anterior = norma_espectral;
		Copiar_matriz (vector, &anterior);
	}

	return norma_espectral;
}



void Opcion_03 () {
	Matriz matriz, vector;
	int maximo_iteraciones;
	double valor_propio_maximo, valor_propio_minimo, norma_espectral, tolerancia;

	do {
		LIMPIAR_PANTALLA ();

		// Leyendo matriz
		puts ("Inserte la matriz asociada al sistema:");
		puts ("¿Cuántas filas y columnas tiene la matriz? (el número de filas debe ser igual al de las columnas)");
		matriz.filas = Leer_entero_que_sea (">=", 1);
		matriz.columnas = matriz.filas;
		puts ("Inserte las entradas de la matriz:");
		matriz.entrada = Leer_entradas_de_matriz (matriz.filas, matriz.columnas);

		// Inicializando `vector`
		vector.filas = matriz.filas;
		vector.columnas = 1;

		// Leyendo datos para las iteraciones
		puts ("==========");
		puts ("Calculando el valor propio máximo.");
		do {
			puts ("Inserte el vector inicial:");
			vector.entrada = Leer_entradas_de_matriz (vector.filas, vector.columnas);
			norma_espectral = Norma_espectral (vector.filas, vector.entrada);
			if (norma_espectral != 1) {
				puts ("ERROR: Ha insertado un vector inicial con norma espectral distinta de 1, vuelva a intentarlo.");
				free (vector.entrada);
			}
		}
		while (norma_espectral != 1);
		puts ("¿Cuál es el máximo de iteraciones a realizar?");
		maximo_iteraciones = Leer_entero_que_sea (">=", 1);
		puts ("¿De cuánto es la tolerancia?");
		tolerancia = Leer_real_que_sea (">", 0.0);

		// Realizando las iteraciones con la matriz sin invertir
		valor_propio_maximo = Iterador_potencias (matriz, vector, maximo_iteraciones, tolerancia);

		// Pidiendo datos para iniciar las iteraciones del cálculo del valor propio mínimo
		puts ("==========");
		puts ("Calculando el valor propio mínimo.");
		do {
			puts ("Inserte el vector inicial:");
			vector.entrada = Leer_entradas_de_matriz (vector.filas, vector.columnas);
			norma_espectral = Norma_espectral (vector.filas, vector.entrada);
			if (norma_espectral != 1) {
				puts ("ERROR: Ha insertado un vector inicial con norma espectral distinta de 1, vuelva a intentarlo.");
				free (vector.entrada);
			}
		}
		while (norma_espectral != 1);
		puts ("¿Cuál es el máximo de iteraciones a realizar?");
		maximo_iteraciones = Leer_entero_que_sea (">=", 1);
		puts ("¿De cuánto es la tolerancia?");
		tolerancia = Leer_real_que_sea (">", 0.0);

		// Iniciando iteraciones para calcular el valor propio mínimo
		Invertir_matriz (matriz);
		valor_propio_minimo = Iterador_potencias (matriz, vector, maximo_iteraciones, tolerancia);
		valor_propio_minimo = 1.0 / valor_propio_minimo;

		// Mostrando los resultados
		puts ("==========");
		printf ("El valor propio máximo es: %.10lf\n", valor_propio_maximo);
		printf ("El valor propio mínimo es: %.10lf\n", valor_propio_minimo);
	}
	while (Pregunta_cerrada ("¿Quiére calcular los valores propios de otra matriz?") == 1);
}
