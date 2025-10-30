/*
Código de la segunda opción del paquete
*/








#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Opcion_02.h"
#include "Funciones_basicas.h"



static void Gauss_Seidel (Matriz coeficientes, Matriz B) {
	/* Esta función realiza las iteraciones del método de Gauss-Seidel. Primero pide el vector
	inicial (el que se usa para realizar la primera iteración), el máximo de iteraciones a hacer
	y la tolerancia del error relativo. Después comienza a iterar e imprimir el resultado de
	estas. */

	Matriz anterior, resultado;
	int i, j, k;
	int iteraciones;
	double tolerancia, norma_espectral[2], error, suma;

	// Inicializando el vector resultado y anterior (el calculado una iteración antes)
	resultado.filas = B.filas;
	resultado.columnas = 1;
	resultado.entrada = (double *) malloc (sizeof (double) * resultado.filas);
	anterior.filas = B.filas;
	anterior.columnas = 1;
	anterior.entrada = (double *) malloc (sizeof (double) * anterior.filas);

	// Pidiendo los datos iniciales
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
			suma = B.entrada[j];
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
	printf ("La mejor aproximanción al vector solución es: ( %lf", resultado.entrada[0]);
	for (i = 1; i < resultado.filas; i++)
		printf (", %lf", resultado.entrada[i]);
	printf (" ).\n");
	printf ("Con un error relativo de: %lf.\n", error);
}

void Opcion_02 () {
	/* Entorno para la solución de sistemas de ecuaciones con el método de Gauss-Seidel. Segunda
	opción del paquete de programas. */

	int respuesta;
	int edd; // Variable que guarda 1 o 0 dependiendo si la matriz es EDD o no.
	double determinante;
	int filas; /* Dado que se lee la matriz `A` y luego el vector columna `b` del sistema `Ax=b`, esta variable se usa
	              para igualar las filas del vector con las de la matriz de coeficientes y asegurar que esta última sea
		      cuadrada. */
	Matriz coeficientes, B;

	do {
		// Leyendo el sistema
		puts ("Inserte la matriz de coeficientes:");
		puts ("¿Cuántas filas y columnas tiene la matriz de coeficientes? NOTA: El número de filas debe ser el mismo que el de columnas.");
		filas = Leer_entero_que_sea (">=", 1);
		coeficientes.filas = filas;
		coeficientes.columnas = filas;
		coeficientes.entrada = Leer_entradas_de_matriz (filas, filas);
		puts ("Inserte las entradas del vector B:");
		B.filas = filas;
		B.columnas = 1;
		B.entrada = Leer_entradas_de_matriz (filas, 1);

		// Verificando que el sistema tenga solución
		edd = Verificar_EDD (coeficientes);
		if (edd == 1)
			puts ("NOTA: El sistema es estrictamente dominante diagonalmente, por lo que tiene solución.");
		else {
			puts ("ADVERTENCIA: La matriz no es estrictamente dominante diagonalmente, por lo que la convergencia no se asegura.");
			determinante = Determinante (coeficientes);
			if (determinante == 0)
				puts ("ADVERTENCIA: El sistema no tiene solución, su determinante es cero.");
		}

		// Solucionando el sistema en caso de tener solución
		if (edd == 1 || determinante != 0)
			Gauss_Seidel (coeficientes, B);
		
		// Liberando memoria de las entradas de las matrices
		free (coeficientes.entrada);
		free (B.entrada);

		// Preguntando por otro sistema
		respuesta = Pregunta_cerrada ("¿Quiére solucionar otro sistema?");
		
		LIMPIAR_PANTALLA ();
	}
	while (respuesta == 1);

}
