#include "intervaloE.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

IntervaloE intervaloE_crear (int izq, int der){
  IntervaloE nuevoIntervalo;
  nuevoIntervalo.extIzq = izq;
  nuevoIntervalo.extDer = der;
  return nuevoIntervalo;
}

void intervaloE_imprimir (IntervaloE intervalo){
  printf ("[%d, %d] ", intervalo.extIzq, intervalo.extDer);
}

int intervaloE_interseccion (IntervaloE intervalo1, IntervaloE intervalo2){
  return (intervalo1.extIzq <= intervalo2.extDer &&
          intervalo1.extDer >= intervalo2.extIzq);
}

int intervaloE_comparacion (IntervaloE intervalo1, IntervaloE intervalo2){
  int devolver = 0;
  if (intervalo1.extIzq > intervalo2.extIzq)
      devolver = 1;
  else if (intervalo1.extIzq < intervalo2.extIzq)
      devolver = -1;

  return devolver;
}

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

int intervaloE_validar (IntervaloE intervalo){
  return intervalo.extIzq <= intervalo.extDer;
}

IntervaloE intervaloE_no_interseccion_izq (IntervaloE intervalo1, IntervaloE intervalo2){

}


IntervaloE intervaloE_no_interseccion_der (IntervaloE intervalo1, IntervaloE intervalo2);