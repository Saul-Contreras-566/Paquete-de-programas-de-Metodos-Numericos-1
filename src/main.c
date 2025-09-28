#include <stdio.h>
#include "Funciones_basicas.h"
#include "Opcion_01.h"



int main () {
	int seleccion;

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

		// Seleccionando
		puts ("Seleccionar:");
		seleccion = Leer_entero_entre (0, 1);

		// Yendo a la opción seleccionada
		switch (seleccion) {
			case 1: Opcion_01 (); break;
		}
	}
	while (seleccion != 0);
	LIMPIAR_PANTALLA ();

	return 0;
}
