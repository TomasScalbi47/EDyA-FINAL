#include "intervaloE.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/* -------------------------------BASICAS ------------------------------------*/
IntervaloE intervaloE_crear (int izq, int der){
  IntervaloE nuevoIntervalo;
  nuevoIntervalo.extIzq = izq;
  nuevoIntervalo.extDer = der;
  return nuevoIntervalo;
}

int intervaloE_comparacion (IntervaloE intervalo1, IntervaloE intervalo2){
  int devolver = 0;
  if (intervalo1.extIzq > intervalo2.extIzq)
    devolver = 1;
  else if (intervalo1.extIzq < intervalo2.extIzq)
    devolver = -1;

  return devolver;
}

int intervaloE_interseccion (IntervaloE intervalo1, IntervaloE intervalo2){
  return (intervalo1.extIzq <= intervalo2.extDer &&
          intervalo1.extDer >= intervalo2.extIzq);
}

void intervaloE_imprimir (IntervaloE intervalo, char* agregar){

  if (intervalo.extIzq == intervalo.extDer)
    printf ("%d", intervalo.extDer);
  else
    printf ("%d:%d",intervalo.extIzq, intervalo.extDer);

  printf ("%s", agregar);
}

void intervaloE_imprimir2D (IntervaloE intervalo){
  printf ("[%d, %d] ", intervalo.extIzq, intervalo.extDer);
}

/* ------------------------------ UTILES -------------------------------------*/

IntervaloE intervaloE_expandir (IntervaloE intervalo){
  if (intervalo.extDer != INT_MAX)
    intervalo.extDer += 1;
  if (intervalo.extIzq != INT_MIN)
    intervalo.extIzq -= 1;
  return intervalo;
}

IntervaloE intervaloE_unir (IntervaloE intervalo1, IntervaloE intervalo2){
  IntervaloE nuevo;
  nuevo.extIzq = min2 (intervalo1.extIzq, intervalo2.extIzq);
  nuevo.extDer = max2 (intervalo1.extDer, intervalo2.extDer);

  return nuevo;
}

IntervaloE intervaloE_intersecar (IntervaloE intervalo1, IntervaloE intervalo2){
  IntervaloE nuevo;
  nuevo.extIzq = max2 (intervalo1.extIzq, intervalo2.extIzq);
  nuevo.extDer = min2 (intervalo1.extDer, intervalo2.extDer);

  return nuevo;
}

IntervaloE intervaloE_no_interseccion_izq (IntervaloE intervalo1, IntervaloE intervalo2){
    // Esta funcion es empleada solamente cuando se sabe que el intervalo1 excede
    // el intervalo2 por izquierda.
    intervalo1.extDer = intervalo2.extIzq - 1;
    return intervalo1;
}

IntervaloE intervaloE_no_interseccion_der (IntervaloE intervalo1, IntervaloE intervalo2){
    // Esta funcion es empleada solamente cuando se sabe que el intervalo1 excede
    // el intervalo2 por derecha.
    intervalo1.extIzq = intervalo2.extDer + 1;
    return intervalo1;
}