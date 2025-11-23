
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Funciones_basicas.h"
#include "Matrices.h"

int Es_simétrica(Matriz matriz){

Matriz trans;

int i,j;
int s = 0;
int e = 0;

trans.filas = matriz.filas;
trans.columnas = matriz.columnas;
trans.entrada = (double *) malloc (sizeof (double) * matriz.filas * matriz.filas);

//transponiendo la matriz
    for (i = 0; i < matriz.filas; i++) {
        for(j=i; j < matriz.filas * matriz.filas; j += (matriz.filas)-1){
        trans.entrada[j] = matriz.entrada[j];
      }
    }

//imprimiendo la transpuesta
for (i = 0; i < matriz.filas; i++) {
			printf ("| ");
			for (j = 0; j < matriz.columnas; j++)
				printf ("%lf |", trans.entrada[i * trans.columnas + j]);
			printf ("\n");
		}

//verificando la simetria
for (i = 0; i < matriz.filas * matriz.columnas; i++) {
				if(trans.entrada[j] == matriz.entrada[j]){
        s+=1;
        }
  e+=1;
		}

if(s == e && matriz.filas == matriz.columnas){
return 1;
}else{
return 0;
}

}
