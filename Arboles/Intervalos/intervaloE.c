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

IntervaloE intervaloE_expandir (IntervaloE intervalo){
  intervalo.extDer += 1;
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
