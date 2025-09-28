/*
Código de las funciones de la primera opción del paquete.
*/





#include <stdio.h>
#include <math.h>
#include "Opcion_01.h"
#include "Funciones_basicas.h"



static double Evaluar (int funcion_seleccionada, double x) {

	/* Evaluando según la función seleccionada, el número del caso corresponde al número de la
	función a evaluar */
	switch (funcion_seleccionada) {
		case 1:
			return pow (x, 2.0) * cos (x) - 2.0 * x;
		case 2:
			return (6.0 - 2.0 / pow (x, 2.0)) * ( exp (2.0 + x) / 4 ) + 1;
		case 3:
			return pow (x, 3.0) - 3.0 * sin (pow (x, 2.0)) + 1;
		case 4:
			return pow (x, 3.0) + 6.0 * pow (x, 2.0) + 9.4 * x + 2.5;
		// En caso de no seleccionarse correctamente una función
		default:
			puts("ERROR: NO FUNCTION SELECTED"); // Igualmente escrito en inglés para que resalte más
			return 0;
	}
}



static void Iterador (int funcion_seleccionada) {
	double tolerancia, cota_inferior, cota_superior, error_absoluto, error_relativo;
	int maximo_iteraciones;
	double x[3]; // Arreglo con las 3 últimas x calculadas
	int i; // Variable para iteraciones



	// Pidiendo los parámetros de las iteraciones

	puts ("¿Cuál es la tolerancia del error relativo en porcentaje?");
	tolerancia = Leer_real_que_sea (">", 0);
	
	puts ("¿Cuál es el número máximo de iteraciones a realizar?");
	maximo_iteraciones = Leer_entero_que_sea (">", 0);
	
	puts ("¿Cuál es la cota inferior del intervalo?");
	cota_inferior = Leer_real ();
	
	puts ("¿Cuál es la cota superior del intervalo?");
	cota_superior = Leer_real_que_sea (">", cota_inferior);



	// Realizando las iteraciones con la función seleccionada
	x[0] = cota_inferior;
	x[1] = cota_superior;
	error_absoluto = fabs (x[1] - x[0]);
	error_relativo = error_absoluto * 100.0 / fabs(x[1]);
	puts ("| i   | x_i                  | f(x_i)               | Error absoluto       | Error relativo (%)   |"); // Encabezado de la tabla
	printf ("| %3d | %20lf | %20lf | ---                  | ---                  |\n", 0, x[0], Evaluar (funcion_seleccionada, x[0])); 
	for (i = 1;   i <= maximo_iteraciones   &&   error_relativo > tolerancia;  i++) {
		// Calculando errores
		error_absoluto = fabs (x[1] - x[0]);
		error_relativo = error_absoluto * 100.0 / fabs(x[1]);

		// Imprimiendo el valor de la x actual
		printf ("| %3d | %20lf | %20lf | %20lf | %20lf |\n", i, x[1], Evaluar(funcion_seleccionada, x[1]), error_absoluto, error_relativo);

		// Calculando la siguiente x
		x[2] = x[1] - Evaluar (funcion_seleccionada, x[1]) * (x[0] - x[1]) / (Evaluar (funcion_seleccionada, x[0]) - Evaluar (funcion_seleccionada, x[1]));

		// Recorriendo datos para continuar el bucle
		x[0] = x[1];
		x[1] = x[2];
	}

	// Mensaje que indica que se alcanzó el número máximo de iteraciones
	if (i == maximo_iteraciones)
		puts ("Máxmo de iteraciones alcanzado.");
	
	// Mensaje que indica que si el error relativo es menor a la tolerancia
	if (error_relativo  <=  tolerancia)
		puts ("El error relativo es menor a la tolerancia.");
	else
		puts ("El error relativo no es menor a la tolerancia.");

	// Imprimiendo la raíz
	printf ("Aproximación de la raíz: %lf\n", x[0]);
}



void Opcion_01 () {
	int seleccion, respuesta;

	do {
		LIMPIAR_PANTALLA ();

		// Mostrando opciones
		puts ("Seleccione la función a iterar:");
		puts ("1. x^2 * cos(x) - 2 * x");
		puts ("2. (6 - 2 / x^2) * exp( 2 + x ) / 4 + 1");
		puts ("3. x^3 - 3 * sen(x^2) + 1");
		puts ("4. x^3 + 6 * x^2 + 9.4 * x + 2.5");
		puts ("5. SALIR");

		// Leyendo selección
		puts ("Seleccionar:");
		seleccion = Leer_entero_entre (1, 5);
		
		// Procesando selección
		if (seleccion >= 1 && seleccion <= 4) {
			Iterador (seleccion);
			respuesta = Pregunta_cerrada ("¿Quiére iterar otra función");
		}
		else
			respuesta = 0;
	}
	while (respuesta == 1);
}
