/*
Código de las funciones con matrices.
*/





#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Funciones_basicas.h"
#include "Matrices.h"



double *Leer_entradas_de_matriz (int filas, int columnas) {
	/* Esta función está pensada para que se puedan leer las entradas de las matrices de una
	manera más flexible, por ejemplo, en un sistema de ecuaciones de la forma `Ax=b`, se puede
	pedir al usuario primero las dimensiones de las matriz `A` y luego simplemente copiar el
	número de filas al vector `b`, de modo que no se le pide o permite al usuario insertar dos
	veces el número de filas, impidiéndole así que inserte un sistema incoherente. */

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
	/* Esta función pide las dimensiones de la matriz y luego lee sus entradas. Las entradas
	son leídas por una función aparte. */

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



double Determinante (Matriz matriz) {
    /* Calcula el determinante de una matriz cuadrada usando eliminación gaussiana */
    
    if (matriz.filas != matriz.columnas) {
        printf ("ERROR: La matriz debe ser cuadrada para calcular el determinante.\n");
        return 0;
    }
    
    double determinante = 1.0;
    int i, j, k; // Variables para iteraciones
    int columna_del_maximo;
    double valor_temporal, factor;
    
    // Crear una copia de la matriz para no modificar la original
    Matriz temporal;
    temporal.filas = matriz.filas;
    temporal.columnas = matriz.filas;
    temporal.entrada = (double *) malloc (sizeof (double) * matriz.filas * matriz.filas);
    
    // Copiar los valores de la matriz original
    for (i = 0; i < matriz.filas * matriz.filas; i++) {
        temporal.entrada[i] = matriz.entrada[i];
    }
    
    // Aplicar eliminación gaussiana
    for (i = 0; i < matriz.filas; i++) {
        // Buscar el pivote máximo en la columna actual
        columna_del_maximo = i; // Seleccionando la columna del elmento de la diagonal principal para compararlo con el resto de elementos de su misma fila
        for (k = i + 1; k < matriz.filas; k++)
            if (fabs (temporal.entrada[k * matriz.columnas + i]) > fabs (temporal.entrada[columna_del_maximo * matriz.columnas + i]))
                columna_del_maximo = k;
        
        // Si el pivote es cero, el determinante es cero
        if (fabs (temporal.entrada[columna_del_maximo * matriz.columnas + i]) == 0.0) {
            free (temporal.entrada);
            return 0.0;
        }
        
        // Intercambiar filas si es necesario
        if (columna_del_maximo != i) {
            for (k = 0; k < matriz.filas; k++) {
                valor_temporal = temporal.entrada[i * matriz.columnas + k];
                temporal.entrada[i * matriz.columnas + k] = temporal.entrada[columna_del_maximo * matriz.columnas + k];
                temporal.entrada[columna_del_maximo * matriz.columnas + k] = valor_temporal;
            }
            determinante *= -1; // El determinante cambia de signo al intercambiar filas
        }
        
        // Hacer ceros debajo del pivote
        for (k = i + 1; k < matriz.filas; k++) {
            factor = temporal.entrada[k * matriz.columnas + i] / temporal.entrada[i * matriz.columnas + i];
            for (j = i; j < matriz.filas; j++) {
                temporal.entrada[k * matriz.columnas + j] -= factor * temporal.entrada[i * matriz.columnas + j];
            }
        }
        
        // Multiplicar el determinante por el pivote
        determinante *= temporal.entrada[i * matriz.columnas + i];
    }
    
    free (temporal.entrada);
    return determinante;
}



int Verificar_EDD (Matriz matriz) {
	/* Función que verifica que una función sea estrictamente dominante diagonalmente. Compara
	el valor absoluto de cada elemento de la diagonal con la suma de los valores absolutos del
	resto de elemtos de las misma fila que el del elemento en la diagonal. Devuelve `1` en caso
	de ser estrcitamente dominante diagonalmente o `0` en caso de no serlo. */

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
	/* Calcula la norma espectral de un vector. Un simple bucle `for` que itera comparaciones
	entre entradas del vector y en cada una de ellas se queda con la entrada más grande. De esta
	forma, obtiene la entrada de mayor magnitud y, por lo tanto, la norma espectral. */

	int i; // Variable para iteraciones
	double maximo;

	// Comparando
	maximo = fabs (entrada[0]);
	for (i = 1; i < numero_entradas; i++)
		maximo = (maximo < fabs (entrada[i])) ? fabs (entrada[i]) : maximo;
	
	// Regresando norma espectral
	return maximo;
}
