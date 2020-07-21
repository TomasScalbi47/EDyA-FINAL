#include "arrayI.h"
#include <stdio.h>
#include <stdlib.h>


Set set_crear (){
  return NULL; // Se considera conjunto vacío.
}

Set set_crear_compresion (int extIzq, int extDer){
  // Asignando memoria.
  Set nuevoConjunto = malloc (sizeof (arrayI));
  nuevoConjunto->array = malloc (sizeof (IntervaloE));
  // Asignando la cantidad de elementos de un conjunto base.
  nuevoConjunto->capacidad = 1;

  // Completando el conjunto con el intervaloE que contiene.
  nuevoConjunto->array[0].extIzq = extIzq;
  nuevoConjunto->array[0].extIzq = extDer;

  return nuevoConjunto;
}

// Quiero insertar un intervalo [x,y] en un array de intervalos disjuntos
// ordenados.
Set set_insertar (Set conjunto, IntervaloE intervalo){
  Set nuevoConjunto = malloc (sizeof (arrayI));
  // Se asigna la capacidad del conjunto para el peor caso, que se agregue uno.
  nuevoConjunto->array = malloc (sizeof (IntervaloE));
  // Luego se deberá ajustar.

  // El intervalo aumentado se utilizara para encontrar las intersecciones,
  // teniendo como objetivo contar como interseccion a los intervalos contiguos.
  IntervaloE intervaloAumentado, aux;
  intervaloAumentado.extIzq = intervalo.extIzq - 1;
  intervaloAumentado.extDer = intervalo.extDer + 1;
  int fin = 0, interseccion = 0, i = 0, j = 0;

  for (; fin == 0; ++i){
    int interseca = intervaloE_interseccion (intervaloAumentado, conjunto->array[i];

    if (interseccion == 0){
      if (!interseca){
        nuevoConjunto->array[j] = conjunto->array[i];
        ++j;
      }
      else{
        interseccion = 1;
        aux.extIzq = min2 (intervalo.extIzq, conjunto->array[i].extIzq);
        aux.extDer = max2 (intervalo.extDer, conjunto->array[i].extDer);
      }
    }
    else{
      if (interseca)
        aux.extDer = max2 (aux.extDer, conjunto->array[i].extDer);
      else {
        nuevoConjunto->array[j] = aux;
        ++j;
        fin = 1;
      }
    }
  }

  // Agregado de los intervalos faltantes luego.
  for (; i < conjunto->capacidad; ++i){
    nuevoConjunto->array[j] =
  }

}
