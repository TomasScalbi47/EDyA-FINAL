//#include <stdio.h>
//#include "ITree1.h"  //Dentro de ITree1.h se incluye IntervalosE.h
//#include <limits.h>
//#define TAMPRUEBA1 5
//#define TAMPRUEBA2 5
//int main (){
//    /************************
//     * PRUEBA DE INTERVALOS *
//     ************************/
//
//    IntervaloE Minfinito = intervaloE_crear(INT_MIN, INT_MIN);
//    intervaloE_imprimir2D(Minfinito);
//
//    int comparacion = intervaloE_comparacion(Minfinito, intervaloE_crear(1,2));
//    printf ("comparacion menos infinito con [1,2]: |%d|\n", comparacion);
//
//  /*********************************
//   * CARGANDO INTERVALOS DE PRUEBA *
//   *********************************/
//  IntervaloE intervalosPrueba1[TAMPRUEBA1];
//  int j = 0;
//  for (int i = 0; i < TAMPRUEBA1; ++i){
//    intervalosPrueba1[i].extIzq = j;
//    intervalosPrueba1[i].extDer = j+1;
//    j += 3;
//  }
//  IntervaloE intervalosPrueba2[TAMPRUEBA2];
//  j = 1;
//  for (int i = 0; i < TAMPRUEBA2; ++i){
//    intervalosPrueba2[i].extIzq = j;
//    intervalosPrueba2[i].extDer = j+1;
//    j += 3;
//  }
//  /*****************************
//   * CREANDO ARBOLES DE PRUEBA *
//   *****************************/
//  ITree arbolPrueba = itree_crear();
//  for (int i = 0; i < TAMPRUEBA1; ++i){
//    itree_insertar (&arbolPrueba, *(intervalosPrueba1 + i));
//  }
//  printf ("Arbol de prueba 1 --------------------------\n");
//  print2D (arbolPrueba);
//  printf ("\n-------------------------------------------------\n");
//
//  ITree arbolPrueba2 = itree_crear();
//  for (int i = 0; i < TAMPRUEBA2; ++i){
//    itree_insertar (&arbolPrueba2, *(intervalosPrueba2 + i));
//  }
//  // Imprimiendo arbol de prueba2.
//  printf ("Arbol de prueba 2 --------------------------\n");
//  print2D (arbolPrueba2);
//  printf ("\n-------------------------------------------------\n");
//
//  ITree arbolPrueba3 = itree_crear();
//  itree_insertar (&arbolPrueba3, intervaloE_crear(0,5));
//
//   /*********
//    * UNION *
//    *********/
//   ITree arbolUn = itree_crear();
//   arbolUn = itree_unir (arbolPrueba, arbolPrueba2);
//
//   printf ("Imprimiendo arbolPrueba U arbolPrueba2!\n");
//   print2D (arbolUn);
//   printf ("\n");
//
//   itree_destruir (arbolUn);
//   arbolUn = itree_unir (arbolPrueba2, arbolPrueba);
//
//   printf ("Imprimiendo arbolPrueba2 U arbolPrueba!\n");
//   print2D (arbolUn);
//   printf ("\n");
//
//  /*********************************
//   *  INTERSECCION ARBOL-INTERVALO *
//   *********************************/
//   // Esta es la funcion auxiliar que se usa tomando cada intervalo del arbol
//   // mas petizo como si fuese el intervaloInt.
//  IntervaloE intervaloInt = intervaloE_crear (-1,20);
//  ITree arbolInt = itree_crear ();
//
//  itree_intersecarV (arbolPrueba, intervaloInt, &arbolInt);
//  printf ("Imprimiendo Interseccion2!\n");
//  print2D (arbolInt);
//  printf ("\n\n");
//
//  /*********************************
//   *  INTERSECCION ENTRE 2 ARBOLES *
//   *********************************/
//  printf ("Probando Interseccion entre 2 arboles.\n");
//  arbolInt = itree_interseccion (arbolPrueba, arbolPrueba2);
//  printf ("Arbol de Interseccion --------------------------\n");
//  print2D (arbolInt);
//  printf ("\n-------------------------------------------------\n");
//
//  /*****************************
//   *  COMPLEMENTO DE UN ARBOL  *
//   *****************************/
//
//  printf ("Arbol de prueba 1:\n");
//  print2D(arbolPrueba);
//  printf ("\n-------------------------------------\n");
//
//  ITree complemento = itree_complemento(arbolPrueba);
//  printf ("Complemento de arbolPrueba1:\n");
//  print2D(complemento);
//  printf ("\n-------------------------------------\n");
//
//
//  /**********************
//   * PROBANDO RESTA AUX *
//   **********************/
//  IntervaloE intervaloRestaAux = intervaloE_crear (1,5);
//  ITree arbolRestaAux = itree_crear();
//  printf ("imprimiendo arbol prueba3\n");
//  print2D(arbolPrueba3);
//  printf ("\n-----------------------------\n");
//  // este arbol de resta auxiliar, contendra los elementos de [1,5]
//  // que no estan en el arbol.
//  itree_resta_aux(arbolPrueba3, intervaloRestaAux, &arbolRestaAux);
//
//  print2D(arbolRestaAux);
//
//  /**
//   * PROBANDO RESTA ARBOLPRUEBA - ARBOLPRUEBA2 *
//   */
//  ITree arbolResta = itree_crear ();
//  arbolResta = itree_resta(arbolPrueba, arbolPrueba2);
//  printf ("\n---------------Imprimiendo arbol resta arbolPrueba - arbolPrueba2 ------------\n");
//  print2D(arbolResta);
//  printf ("\n--------------------------------------------------------\n");
//
//  itree_destruir (arbolResta);
//  itree_destruir (arbolRestaAux);
//  itree_destruir (complemento);
//  itree_destruir (arbolUn);
//  itree_destruir (arbolInt);
//  itree_destruir (arbolPrueba);
//  itree_destruir (arbolPrueba2);
//  itree_destruir (arbolUn);
//
//  return 0;
//}
