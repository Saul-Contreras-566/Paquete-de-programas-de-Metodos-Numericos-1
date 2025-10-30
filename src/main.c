#include <stdio.h>
#include <stdlib.h>
#include "Funciones_basicas.h"
#include "Opcion_01.h"
#include "Opcion_02.h"



int main () {
	int seleccion;

	#ifdef _WIN32
	system ("chcp 65001"); // Permitiendo acentos en Windows
	#endif

	// Portada del programa
	LIMPIAR_PANTALLA ();
	puts ("PAQUETE DE PROGRAMAS - MÉTODOS NUMÉRICOS\n");
	puts ("Integrantes:");
	puts ("- Contreras Rojas Emanuel Saúl");
	puts ("- Rodríguez Medina José Alfredo");
	puts ("- Salazar Hernández Alejandro");
	puts ("--------------------------------------------------");
	ESPERAR_TECLA ();

	do {
		LIMPIAR_PANTALLA ();

		// Menú de selección
		puts ("¿Qué quiere hacer?");
		puts ("0. SALIR.");
		puts ("1. Calcular las raices de algunas funciones con el método de la secante.");
		puts ("2. Solucionar un sistema de ecuaciones.");

		// Seleccionando
		puts ("Seleccionar:");
		seleccion = Leer_entero_entre (0, 2);

		// Yendo a la opción seleccionada
		switch (seleccion) {
			case 1: Opcion_01 (); break;
			case 2: Opcion_02 (); break;
		}
	}
	while (seleccion != 0);
	LIMPIAR_PANTALLA ();

	return 0;
}
