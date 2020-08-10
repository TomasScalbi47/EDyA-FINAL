//
// Created by scalbi on 7/8/2020.
// Acciones que hay que crear:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interprete.h"
#define TAM_INICIAL_BUFF 100

int main (){
    interpretar();
    return 0;
}

void interpretar (){
  char *entradaOriginal, *conjuntoAfectado, *conjuntoA, *conjuntoB;

  char *igualVariable, *aliasOrLlaveOrComp, *operacion;

  int tamEntrada = TAM_INICIAL_BUFF, salida = 0;

  int es_alias;
  /********************
   * IMPRIMIENDO MENU *
   ********************/
   imprimir_menu ();


  while (!salida){
    // Se lee la entrada.
    entradaOriginal = leer_entrada (&tamEntrada);
    char *entradaParser = malloc(sizeof(char) * tamEntrada);
    strcpy (entradaParser, entradaOriginal);
    printf ("Entrada leida: |%s|\n", entradaOriginal);
    printf ("Entrada leida en parser: |%s|\n", entradaParser);

    // Chequeando si es salir.
    if (strcmp (entradaOriginal, "salir") == 0) {
      printf("El comando fue salir\n");
      salida = 1;
    }

    // Comando comenzado con imprimir.
    else if (strncmp (entradaOriginal, "imprimir", 8) == 0){
      printf ("Comando comienza con imprimir\n");
      strtok(entradaParser, " ");
      conjuntoAfectado = strtok (NULL, " ");
      printf ("Conjunto a imprimir: |%s|\n", conjuntoAfectado);
    }

    // El resto de comandos comienza si o si con un alias.
    else {
      conjuntoAfectado = strtok (entradaParser, " ");
      igualVariable = strtok (NULL, " ");
      printf (" Conjunto afectado: |%s|\n", conjuntoAfectado);
      printf (" igualVariable: |%s|\n", igualVariable);

      // Y luego sigue con un '='
      if (strcmp (igualVariable, "=") == 0){
        // luego nos encontramos con 2 familias de comandos.
        // Operaciones, y crear.

        // Operaciones.
        aliasOrLlaveOrComp = strtok (NULL, " ");
        char comienzo = aliasOrLlaveOrComp[0];

        switch (comienzo) {
          //// COMPLEMENTO
          case '~':
            printf ("  La operacion es complemento\n");
            conjuntoA = strtok (NULL, " ");
            printf ("   ConjuntoA: |%s|\n", conjuntoA);
            es_alias = validar_alias_entrada (conjuntoA);
            if (es_alias) {
              printf ("El cojunto afectado: |%s|, "
                      "sera actualizado a ~|%s|\n", conjuntoAfectado, conjuntoA);
            }
            else {
              printf("No se respeta el formato adecuado.\n");
              printf("Los alias pueden contener numeros o letras.\n");
            }
            break;
          //// CREACION DE CONJUNTO
          case '{':
            printf ("  Creacion de conjunto.\n");
            break;
          //// OPERACIONES
          default:
            printf ("  Operacion entre conjuntos.\n");
            es_alias = validar_alias_entrada (aliasOrLlaveOrComp);
            if (es_alias) {
              printf("   Primer alias es: |%s|\n", aliasOrLlaveOrComp);
              conjuntoA = aliasOrLlaveOrComp;
              operacion = strtok(NULL, " ");

              if (operacion != NULL) {
                if (strcmp(operacion, "|") == 0) {
                  printf("   Operacion de Union.\n");
                  conjuntoB = strtok (NULL, " ");

                  es_alias = validar_alias_entrada (conjuntoB);
                  if (es_alias) {
                    printf ("El cojunto afectado: |%s|, "
                            "sera actualizado a |%s| U |%s|\n",
                            conjuntoAfectado, conjuntoA, conjuntoB);
                  }
                  else {
                    printf("No se respeta el formato adecuado.\n");
                    printf("Los alias pueden contener numeros o letras.\n");
                  }
                } else if (strcmp(operacion, "&") == 0) {
                  printf("   Operacion de Interseccion.\n");
                  conjuntoB = strtok (NULL, " ");

                  es_alias = validar_alias_entrada (conjuntoB);
                  if (es_alias) {
                    printf ("El cojunto afectado: |%s|, "
                            "sera actualizado a |%s| & |%s|\n",
                            conjuntoAfectado, conjuntoA, conjuntoB);
                  }
                  else {
                    printf("No se respeta el formato adecuado.\n");
                    printf("Los alias pueden contener numeros o letras.\n");
                  }
                } else if (strcmp(operacion, "-") == 0) {
                  printf("   Operacion de Resta.\n");
                  conjuntoB = strtok (NULL, " ");

                  es_alias = validar_alias_entrada (conjuntoB);
                  if (es_alias) {
                    printf ("El cojunto afectado: |%s|, "
                            "sera actualizado a |%s| - |%s|\n",
                            conjuntoAfectado, conjuntoA, conjuntoB);
                  }
                  else {
                    printf("No se respeta el formato adecuado.\n");
                    printf("Los alias pueden contener numeros o letras.\n");
                  }
                }
                else {
                  printf("   Operacion Invalida.\n");
                  printf("   No se respeta el formato adecuado.\n");
                  printf("   Las operaciones avaladas estan en el menu.\n");
                  imprimir_menu();
                }
              }
              else {
                printf ("Comando incompleto.\n");
                imprimir_menu();
              }
            }
            else {
              printf("No se respeta el formato adecuado.\n");
              printf("Los alias pueden contener numeros o letras.\n");
            }

        }

      }
      else {
        printf ("No se respeta el formato adecuado.\n");
        printf ("Luego de un alias siempre sigue un '='\n\n");
        imprimir_menu();
      }

    }
  }
  free (entradaOriginal);
}


char* leer_entrada (int *tamBuffer){
    int cantElementos = 0;
    char *buffer = malloc (sizeof(char) * *tamBuffer);
    char entrada = getchar();

    while (entrada != '\n'){
        if (cantElementos == *tamBuffer - 1)
            buffer = aumentar_tamanio(buffer, tamBuffer);
        buffer[cantElementos] = entrada;
        cantElementos += 1;
        entrada = getchar();
    }
    buffer[cantElementos] = '\0';
    // Reajustando el tamaño del buffer al minimo.
    buffer = realloc (buffer, ((cantElementos + 1) * sizeof(char)));
    *tamBuffer = cantElementos + 1;
    return buffer;
}

char* aumentar_tamanio (char* buffer, int *tamAnterior){
    int nuevoTamanio = *tamAnterior * 2;
    char* nuevoBuffer = malloc (sizeof(char) * nuevoTamanio);
    for (int i = 0; i < *tamAnterior; ++i)
        nuevoBuffer[i] = buffer[i];
    *tamAnterior = nuevoTamanio;

    free (buffer);
    return nuevoBuffer;
}

void imprimir_menu (){
  printf ("Lista de comandos y formatos aceptados:\n");
  printf ("  * Cerrar el interprete: 'salir'\n");
  printf ("  * Imprimir un conjunto: 'imprimir A'\n");
  printf ("  * Crear conjunto por compresion: 'A = {0,1,2,3}'\n");
  printf ("  * Crear conjunto por extension: 'A = {x : -3 <= x <= 5}'\n");
  printf ("  * Unir conjuntos: 'A = B | C'\n");
  printf ("  * Intersecar conjuntos: 'A = B & C'\n");
  printf ("  * Complemento de un conjunto: 'A = ~A'");
  printf ("  * Restar conjuntos: 'A = B - C'\n");
}

int validar_alias_entrada (char *alias){
  int devolver = 1;
  for (int i = 0; alias[i] != '\0'; ++i){
    if (!isalpha (alias[i]) && !isdigit(alias[i]))
      devolver = 0;
  }
  return devolver;
}
