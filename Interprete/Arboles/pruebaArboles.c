#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ITree1.h"  //Dentro de ITree1.h se incluye IntervalosE.h
#define TAMPRUEBA1 10
#define TAMPRUEBA2 12
int main (){
  IntervaloE intervalosPrueba1[TAMPRUEBA1];

  // Cargando intervalos de prueba..
  int j = 0;
  for (int i = 0; i < TAMPRUEBA1; ++i){
    intervalosPrueba1[i].extIzq = j;
    intervalosPrueba1[i].extDer = j+1;
    j += 3;
  }
  // Creando nuevo arbol.
  ITree arbolPrueba = itree_crear();
  for (int i = 0; i < TAMPRUEBA1; ++i){
    itree_insertar (&arbolPrueba, *(intervalosPrueba1 + i));
  }

  // Imprimiendo arbol de prueba.
  print2D (arbolPrueba);
  printf ("\n");

  IntervaloE intervalosPrueba2[TAMPRUEBA2];

  // Cargando intervalos de prueba..
  j = 1;
  for (int i = 0; i < TAMPRUEBA2; ++i){
    intervalosPrueba2[i].extIzq = j;
    intervalosPrueba2[i].extDer = j+1;
    j += 3;
  }
  // Creando nuevo arbol.
  ITree arbolPrueba2 = itree_crear();
  for (int i = 0; i < TAMPRUEBA2; ++i){
    itree_insertar (&arbolPrueba2, *(intervalosPrueba2 + i));
  }

  // Imprimiendo arbol de prueba.
  print2D (arbolPrueba2);
  printf ("\n");


  // // UNION..
  ITree arbolUn = itree_crear();
  arbolUn = itree_unir (arbolPrueba, arbolPrueba2);

  printf ("Imprimiendo union!\n");
  print2D (arbolUn);
  printf ("\n");
  itree_destruir (arbolUn);
  arbolUn = itree_unir (arbolPrueba2, arbolPrueba);

  printf ("Imprimiendo union!\n");
  print2D (arbolUn);
  printf ("\n");



  itree_destruir (arbolPrueba);
  itree_destruir (arbolPrueba2);
  itree_destruir (arbolUn);

  return 0;
}
