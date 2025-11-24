#include <stdio.h>
#include <stdlib.h>
#include "Funciones_basicas.h"
#include "Opcion_01.h"
#include "Opcion_02.h"
#include "Opcion_03.h"



int main () {
	int seleccion;

	#ifdef _WIN32
	system ("chcp 65001"); // Permitiendo acentos en Windows
	#endif

	// Portada del programa
	LIMPIAR_PANTALLA ();
	puts ("PAQUETE DE PROGRAMAS - MÉTODOS NUMÉRICOS\n");
	puts ("Integrantes:");
	puts ("- Contreras Rojas Emanuel Saúl.");
	puts ("- Galindo Juárez Miguel Ángel.");
	puts ("- Rodríguez Medina José Alfredo.");
	puts ("- Salazar Hernández Alejandro.");
	puts ("--------------------------------------------------");
	ESPERAR_TECLA ();

	do {
		LIMPIAR_PANTALLA ();

		// Menú de selección
		puts ("¿Qué quiere hacer?");
		puts ("0. SALIR.");
		puts ("1. Calcular las raices de algunas funciones con el método de la secante.");
		puts ("2. Solucionar un sistema de ecuaciones.");
			puts ("\t2.0. Primero se lee la matriz, luego se puede seleccionar los siguientes métodos:");
			puts ("\t2.1. Método de Gauss-Seidel.");
			puts ("\t2.2. Factorización LU, método de Doolittle.");
			puts ("\t2.3. Factorización LU, método de Cholesky.");
			puts ("\t2.4. Factorización LU, método de Crout.");
		puts ("3. Hallar los valores propios de una matriz por el método de potencias.");

		// Seleccionando
		puts ("Seleccionar:");
		seleccion = Leer_entero_entre (0, 3);

		// Yendo a la opción seleccionada
		switch (seleccion) {
			case 1: Opcion_01 (); break;
			case 2: Opcion_02 (); break;
			case 3: Opcion_03 (); break;
		}
	}
	while (seleccion != 0);
	LIMPIAR_PANTALLA ();

	return 0;
}
