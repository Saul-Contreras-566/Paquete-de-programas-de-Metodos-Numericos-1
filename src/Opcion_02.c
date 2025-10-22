#include <stdio.h>
#include <math.h>
#include "Funciones_basicas.h"
#include "Opcion_02.h"


static int EDD (Matriz matriz*){
int i, j, fRes;
  int filaEDD;
for(i=0;i<=matriz.filas;i++){
    fRes=0;
    for(j=0;j<matriz.columnas;i++){
      if(j!=i){
    fRes += fabs(matriz.entrada[j]);
      }
    }
if(fabs (matriz.entrada[i]) >= fRes){
        filaEDD +=1;
      }
}

  if(filaEDD==matriz.filas){
    return 1;
  }else{
  return 0;
  }
  
}



  static void Determinante (Matriz matriz*){
if(EDD(matriz) ==1){
  printf("No se necesita calcular el determinante, la matriz es EDD\n");
}else{




  
}}
