/*
Código de la opción para resolver sistemas de ecuaciones.
*/





#include <stdio.h>
#include <stdlib.h>
#include "Funciones_basicas.h"
#include "Opcion_02.h"
#include "Matrices.h" // Biblioteca con funciones de matrices
#include "Metodos_sistemas_ecuaciones.h" // Biblioteca con las funciones de resolución de sistemas de ecuaciones



void Opcion_02 () {
	/* Entorno para la solución de sistemas de ecuaciones con el método de Gauss-Seidel y los
	métodos de factorización. Segunda opción del paquete de programas. */

	int respuesta, seleccion;
	int edd; // Variable que guarda 1 o 0 dependiendo si la matriz es EDD o no.
	double determinante;
	Matriz coeficientes;

	do {
		LIMPIAR_PANTALLA ();

		// Leyendo el sistema
		puts ("Inserte la matriz de coeficientes:");
		puts ("¿Cuántas filas y columnas tiene la matriz de coeficientes? NOTA: El número de filas debe ser el mismo que el de columnas.");
		coeficientes.filas = Leer_entero_que_sea (">=", 1);
		coeficientes.columnas = coeficientes.filas;
		coeficientes.entrada = Leer_entradas_de_matriz (coeficientes.filas, coeficientes.columnas);

		// Verificando que el sistema tenga solución
		edd = Verificar_EDD (coeficientes);
		if (edd == 1)
			puts ("NOTA: El sistema es estrictamente dominante diagonalmente, por lo que tiene solución.");
		else {
			puts ("ADVERTENCIA: La matriz no es estrictamente dominante diagonalmente, por lo que la convergencia no se asegura.");
			determinante = Determinante (coeficientes);
			if (determinante == 0)
				puts ("ADVERTENCIA: El sistema no tiene solución, su determinante es cero.");
			else
				printf ("NOTA: El determinante de la matriz de coeficientes es %lf.\n", determinante);
		}

		if (edd == 1 || determinante != 0.0) {
			// Seleccionando el método por el cual resolver
			do {
				puts ("¿Cuál es el método que quiere utilizar para resolver el sistema?");
				puts ("1. Método de Gauss-Seidel.");
				puts ("2. Por factorización por el método de Dooittle.");
				puts ("3. Por factorización por el método de Cholesky.");
				puts ("4. Por factorización por el método de Crout.");
				puts ("5. SALIR.");
				puts ("Seleccionar:");
				seleccion = Leer_entero_entre (1,5);

				if (seleccion == 5) break;
				
				switch (seleccion) {
					case 1: Gauss_Seidel (coeficientes); break;
					case 2: Doolittle (coeficientes); break;
					case 3: Cholesky (coeficientes); break;
					case 4: Crout (coeficientes); break;
				}

				puts ("==========");
				respuesta = Pregunta_cerrada ("¿Quiére utilizar otro método?");
			}
			while (respuesta == 1);
		}

		// Liberando memoria de la matriz del sistema
		free (coeficientes.entrada);

		// Preguntando por otro sistema
		respuesta = Pregunta_cerrada ("¿Quiére solucionar otro sistema?");
	}
	while (respuesta == 1);
}
