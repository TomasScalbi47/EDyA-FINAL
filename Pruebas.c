////
//// Created by scalbi on 11/8/20.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <limits.h>
//#include "Arboles/ITree1.h"
//#include "Arboles/Intervalos/intervaloE.h"
//
//#define TAM_STR 100
//
//int main (){
//  // Esto se hara una vez descartado el caso del conjunto vacio.
//  char str[TAM_STR] = "{1,5}";
//  char *ptr = str;
//  long leido;
//  int validez = 1;
//
//  ITree arbolNuevo =  itree_crear ();
//  IntervaloE intervalo;
//
//  for (int i = 0; ptr[0] != '}' && ptr[0] != '\0' && validez; ++i){
//    if (isdigit(ptr[1]) || (ptr[1] == '-' && isdigit(ptr[2]))) {
//      leido = strtol(ptr + 1, &ptr, 10);
//      printf("The number(unsigned long integer) is %ld\n", leido);
//      if (leido >= INT_MIN && leido <= INT_MAX) {
//        intervalo = intervaloE_crear(leido, leido);
//        printf("Insertando intervalo: ");
//        intervaloE_imprimir(intervalo);
//        printf("\n");
//        itree_insertar(&arbolNuevo, intervalo);
//        printf("\nImprimiendo arbol------------------------\n");
//        print2D(arbolNuevo);
//        printf("\n-----------------------------------------\n");
//      } else {
//        printf("Numero invalido.\n");
//        validez = 0;
//      }
//      printf("String part is |%s|\n\n", ptr);
//    }
//    else
//      validez = 0;
//  }
//
//  if (validez) {
//    if (ptr[0] == '}' && ptr[1] == '\0') {
//      printf("entrada correcta.\n");
//      // Agregar a la tabla hash.
//    }
//    else {
//      printf("Entrada de creacion de conjunto por extension invalida.\n");
//      itree_destruir(arbolNuevo);
//    }
//  }
//  else {
//    printf("Entrada de creacion de conjunto por extension invalida.\n");
//    itree_destruir(arbolNuevo);
//  }
//
//
//  return 0;
//}
