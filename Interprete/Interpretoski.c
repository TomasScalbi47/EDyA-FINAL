//
// Created by scalbi on 10/8/20.
//
//
// Created by scalbi on 7/8/2020.
// Acciones que hay que crear:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interprete.h"
#include "../Arboles/Intervalos/intervaloE.h"
#define TAM_INICIAL_BUFF 100

int main (){
  interpretar();
  return 0;
}

void interpretar (){
  char *entradaOriginal, *entradaParser;
  int tamEntrada = TAM_INICIAL_BUFF, salida = 0;

  /********************
   * IMPRIMIENDO MENU *
   ********************/
  imprimir_menu ();


  while (!salida){
    // Se lee la entrada.
    entradaOriginal = leer_entrada (&tamEntrada);
    entradaParser = entradaOriginal;
    printf ("Entrada leida: |%s|\n", entradaOriginal);
    printf ("Entrada leida en parser: |%s|\n", entradaParser);

    char *palabra1 = strtok (entradaParser, " ");
    char *palabra2 = strtok (NULL, " ");

    /********************
     * COMANDO DE SALIR *
     ********************/
    if (palabra2 == NULL){
      if (strcmp (palabra1, "salir") == 0)
        salida = 1;
      else {
        printf ("No se respeta el formato. El unico comando aceptado de "
                "una palabra es 'salir'.\n");
        imprimir_menu();
      }
    }
    /***********************
    * COMANDO DE IMPRIMIR *
    ***********************/
    else if (strcmp (palabra1, "imprimir") == 0){
      if (validar_alias_entrada(palabra2)){
        if (strtok (NULL, " ") == NULL){
          printf ("El comando ingresado es imprimir, y el conjunto afectado"
                  " es |%s|\n", palabra2);
        }
        else {
          printf ("El comando imprimir solo acepta un conjunto.\n\n");
        }
      }
      else {
        printf ("Luego del comando 'imprimir' sigue un alias valido.\n"
                "Los alias validos solo contienen caracteres alfanumericos.\n\n");
      }
    }
      /********************
      * RESTO DE COMANDOS *
      *********************/
    else if (validar_alias_entrada (palabra1)){
      if (strcmp (palabra2, "=") == 0){
        char *palabra3 = strtok (NULL, " ");
        char *palabra4 = strtok (NULL, " ");
        char *analizar;

        /********************************
         * CREAR CONJUNTO POR EXTENSION *
         ********************************/
        if (palabra4 == NULL){
        }

        /*********************************
         * CREAR CONJUNTO POR COMPRESION *
         *********************************/
        else if (palabra4[0] == ':'){
        }
        /***************
         * COMPLEMENTO *
         ***************/
        else if (strcmp(palabra3, "~") == 0){
          if (validar_alias_entrada(palabra4)){
            printf ("El conjunto: |%s| es igual al complemento de |%s|\n\n",
                    palabra1, palabra4);
            // complemento.
          }
          else {
            printf ("El ultimo alias del comando no es valido.\n\n");
          }
        }
        /********************************
         * INTERSECCION - UNION - RESTA *
         ********************************/
        else {
          if (validar_alias_entrada(palabra3)){
            char *palabra5 = strtok (NULL, " ");
            if (validar_alias_entrada (palabra5)){
              if (strtok (NULL, " ") == NULL){
                  /****************
                   * INTERSECCION *
                   ****************/
                  switch (palabra4[0]) {
                    case '&':
                      printf("El conjunto |%s| es igual a la interseccion "
                             "entre |%s| y |%s|\n\n", palabra1, palabra3,
                             palabra5);
                      break;
                      /*********
                       * UNION *
                       *********/
                    case '|':
                      printf("El conjunto |%s| es igual a la union "
                             "entre |%s| y |%s|\n\n", palabra1, palabra3,
                             palabra5);
                      break;
                      /*********
                       * RESTA *
                       *********/
                    case '-':
                      printf("El conjunto |%s| es igual a la resta "
                             "entre |%s| y |%s|\n\n", palabra1, palabra3,
                             palabra5);
                      break;

                    default:
                      printf("Operacion no valida.\n");
                      imprimir_menu();
                  }
                }
              else {
                printf ("Los comandos interseccion, resta y union, solo"
                        "pueden ser realizados entre 2 conjuntos.\n\n");
              }
            }
            else {
              printf("El ultimo alias del comando no es valido.\n\n");
            }
          }
          else {
            printf ("El segundo alias del comando no es valido.\n\n");
          }
        }
      }
      else {
        printf ("No se respeta el formato adecuado.\n");
        printf ("Luego del primer alias siempre sigue un '='\n\n");
        imprimir_menu();
      }
    }
    else {
      printf (" El alias ingresado es invalido.\n"
              "Los alias validos solo contienen caracteres alfanumericos.\n\n");
      imprimir_menu();
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
  printf ("  * Crear conjunto por extension: 'A = {0,1,2,3}'\n");
  printf ("  * Crear conjunto por compresion: 'A = {x : -3 <= x <= 5}'\n");
  printf ("  * Unir conjuntos: 'A = B | C'\n");
  printf ("  * Intersecar conjuntos: 'A = B & C'\n");
  printf ("  * Complemento de un conjunto: 'A = ~A'");
  printf ("  * Restar conjuntos: 'A = B - C'\n");
}

int validar_alias_entrada (char *alias){
  int devolver = 1;
  for (int i = 0; alias[i] != '\0' && devolver == 1; ++i){
    if (!isalpha (alias[i]) && !isdigit(alias[i]))
      devolver = 0;
  }
  return devolver;
}
