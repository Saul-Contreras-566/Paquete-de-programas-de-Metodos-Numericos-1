// Funciones base

#include "Funciones_basicas.h"

void Leer_cadena (char **cadena) {
	int i, fin_de_la_cadena = 0;
	fflush (stdin);
	*cadena = (char *) malloc (sizeof (char));
	for (i = 1; fin_de_la_cadena == 0; i++) {
		(*cadena)[i - 1] = getchar ();
		*cadena = (char *) realloc (*cadena, i + 1);
		fin_de_la_cadena = ((*cadena)[i - 1] == '\n') ? 1 : 0;
	}
	(*cadena)[i - 2] = 0;
	fflush (stdin);
}

char Leer_caracter () {
	char caracter, *lectura;

	Leer_cadena (&lectura);
	caracter = lectura[0];

	free (lectura);
	return caracter;
}

int Leer_entero () {
	char *lectura, *fin_de_la_cadena;
	int numero;

	do {
		Leer_cadena (&lectura);
		numero = (int) strtol (lectura, &fin_de_la_cadena, 10);
		if (*fin_de_la_cadena != '\0')
			printf ("No ha insertado un número entero, vuelva a intentarlo\n");
	}
	while (*fin_de_la_cadena != '\0');

	free(lectura);
	return numero;
}

double Leer_real () {
	char *lectura, *fin_de_la_cadena;
	double numero;

	do {
		Leer_cadena (&lectura);
		numero = strtod (lectura, &fin_de_la_cadena);
		if (*fin_de_la_cadena != '\0')
			printf ("No ha insertado un número, vuelva a intentarlo\n");
	}
	while (*fin_de_la_cadena != '\0');

	free(lectura);
	return numero;
}

int Pregunta_cerrada (char *mensaje) {
	char contestacion; // Usado para leer la respuesta del usuario
	int respuesta; // Usado para envíar un valor de salida en la función y para validar la respuesta

	do {
		printf ("%s (S / n): ", mensaje);
		contestacion = Leer_caracter ();

		if (contestacion == 'S')
			respuesta = 1;
		else if (contestacion == 'N')
			respuesta = 0;
		else {
			puts ("No ha dado una respuesta válida, vuelva a intentarlo.");
			respuesta = -1;
		}
	}
	while (respuesta == -1);

	return respuesta;
}

