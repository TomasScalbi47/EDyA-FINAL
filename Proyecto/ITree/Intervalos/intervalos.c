#include <stdio.h>
#include <stdlib.h>
#include "intervalos.h" // Archivo con las declaraciones y comentado de las funciones.

Intervalo intervalo_crear (double extIzq, double extDer){
  Intervalo nuevoIntervalo;
  nuevoIntervalo.extIzq = extIzq;
  nuevoIntervalo.extDer = extDer;
  return nuevoIntervalo;
}

int intervalo_comparacion (Intervalo intervalo1, Intervalo intervalo2){
  //0: iguales. 1: intervalo1 > intervalo2. -1: intervalo1 < intervalo2.
  int devolver = 0;

  if (intervalo1.extIzq > intervalo2.extIzq)
    devolver = 1;
  else if (intervalo1.extIzq < intervalo2.extIzq)
    devolver = -1;
  // Extremos izquierdos iguales..
  else if (intervalo1.extIzq == intervalo2.extIzq){
    if (intervalo1.extDer > intervalo2.extDer)
      devolver = 1;
    else if (intervalo1.extDer < intervalo2.extDer)
      devolver = -1;
  }

  return devolver;
}

void intervalo_imprimir (Intervalo intervalo){
  // Los double se imprimen como %g como se recomendo para asi mejorar la
  // legibilidad, solo se mostraran las cifras significativas necesarias.
  printf ("[%g, %g] ", intervalo.extIzq, intervalo.extDer);
}

int intervalo_interseccion (Intervalo intervalo1, Intervalo intervalo2){
  return (intervalo1.extIzq <= intervalo2.extDer &&
          intervalo2.extIzq <= intervalo1.extDer);
}

int intervalo_validar (Intervalo intervalo){
  return intervalo.extIzq <= intervalo.extDer;
}
