#include "intervaloE.h"
#include <stdio.h>
#include <stdlib.h>

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
  return intervalo1.extIzq - intervalo2.extIzq;
}
