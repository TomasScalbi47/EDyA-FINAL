#include <stdio.h>
#include "ITree1.h"  //Dentro de ITree1.h se incluye IntervalosE.h
#define TAMPRUEBA1 5
#define TAMPRUEBA2 4
int main (){
  /*********************************
   * CARGANDO INTERVALOS DE PRUEBA *
   *********************************/
  IntervaloE intervalosPrueba1[TAMPRUEBA1];
  int j = 0;
  for (int i = 0; i < TAMPRUEBA1; ++i){
    intervalosPrueba1[i].extIzq = j;
    intervalosPrueba1[i].extDer = j+2;
    j += 4;
  }
  IntervaloE intervalosPrueba2[TAMPRUEBA2];
  j = 2;
  for (int i = 0; i < TAMPRUEBA2; ++i){
    intervalosPrueba2[i].extIzq = j;
    intervalosPrueba2[i].extDer = j+2;
    j += 3;
  }
  /*****************************
   * CREANDO ARBOLES DE PRUEBA *
   *****************************/
  ITree arbolPrueba = itree_crear();
  for (int i = 0; i < TAMPRUEBA1; ++i){
    itree_insertar (&arbolPrueba, *(intervalosPrueba1 + i));
  }
  printf ("Arbol de prueba 1 --------------------------\n");
  print2D (arbolPrueba);
  printf ("\n-------------------------------------------------\n");

  ITree arbolPrueba2 = itree_crear();
  for (int i = 0; i < TAMPRUEBA2; ++i){
    itree_insertar (&arbolPrueba2, *(intervalosPrueba2 + i));
  }
  // Imprimiendo arbol de prueba2.
  printf ("Arbol de prueba 2 --------------------------\n");
  print2D (arbolPrueba2);
  printf ("\n-------------------------------------------------\n");

   /*********
    * UNION *
    *********/
   ITree arbolUn = itree_crear();
   arbolUn = itree_unir (arbolPrueba, arbolPrueba2);

   printf ("Imprimiendo arbolPrueba U arbolPrueba2!\n");
   print2D (arbolUn);
   printf ("\n");

   itree_destruir (arbolUn);
   arbolUn = itree_unir (arbolPrueba2, arbolPrueba);

   printf ("Imprimiendo arbolPrueba2 U arbolPrueba!\n");
   print2D (arbolUn);
   printf ("\n");

  /*********************************
   *  INTERSECCION ARBOL-INTERVALO *
   *********************************/
   // Esta es la funcion auxiliar que se usa tomando cada intervalo del arbol
   // mas petizo como si fuese el intervaloInt.
  IntervaloE intervaloInt = intervaloE_crear (-1,20);
  ITree arbolInt = itree_crear ();

  itree_intersecarV (arbolPrueba, intervaloInt, &arbolInt);
  printf ("Imprimiendo Interseccion2!\n");
  print2D (arbolInt);
  printf ("\n\n");

  /*********************************
   *  INTERSECCION ENTRE 2 ARBOLES *
   *********************************/
  printf ("Probando Interseccion entre 2 arboles.\n");
  arbolInt = itree_interseccion (arbolPrueba, arbolPrueba2);
  printf ("Arbol de Interseccion --------------------------\n");
  print2D (arbolInt);
  printf ("\n-------------------------------------------------\n");

  itree_destruir (arbolUn);
  itree_destruir (arbolInt);
  itree_destruir (arbolPrueba);
  itree_destruir (arbolPrueba2);
  itree_destruir (arbolUn);

  return 0;
}
