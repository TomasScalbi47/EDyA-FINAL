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
#include <limits.h>
#include "../Arboles/ITree1.h"
#include "../Hash/tablahash.h"
#define TAM_INICIAL_BUFF 100
#define TAM_TABLA_HASH 100

int hasheo(char *alias, unsigned capacidad) {
    // Funcion de hash de Dan Bernstein.
    // Declarado como unsigned para que sea siempre positivo.
    unsigned int hash = 5381;

    for(int i = 0; alias[i]; i++)
        hash = (33 * hash) + alias[i];
    return hash % capacidad;
}

int main (){
  interpretar();
  return 0;
}

void interpretar (){
    TablaHash *tablita = tablahash_crear(TAM_TABLA_HASH, hasheo);


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
        tablahash_destruir (tablita);
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
          Conjunto contenedor = tablahash_buscar(tablita, palabra2);
          if (contenedor != NULL){
            print2D(contenedor->conjunto);
            printf ("\n");
          }
          else
            printf ("El conjunto |%s| no esta definido", palabra2);
        }
        else
          printf ("El comando imprimir solo acepta un conjunto.\n\n");
      }
      else
        printf ("Luego del comando 'imprimir' sigue un alias valido.\n"
                "Los alias validos solo contienen caracteres alfanumericos.\n\n");
    }
      /********************
      * RESTO DE COMANDOS *
      *********************/
    else if (validar_alias_entrada (palabra1)){
      if (strcmp (palabra2, "=") == 0){
        char *palabra3 = strtok (NULL, " ");
        char *palabra4 = strtok (NULL, " ");

        ITree arbolNuevo = itree_crear();

        /********************************
         * CREAR CONJUNTO POR EXTENSION *
         ********************************/
        if (palabra4 == NULL && palabra3[0] == '{'){
          // Si se trata del conjunto vacio..
          if (palabra3[1] == '}' && palabra3[2] == '\0') {
            printf("Se añade el conjunto vacio a la tabla hash.\n");
            tablahash_insertar(tablita, palabra1, arbolNuevo);
          }
          // No es conjunto vacio..
          else {
            long leido;
            int validez = 1;

            for (int i = 0; palabra3[0] != '}' && palabra3[0] != '\0' && validez; ++i) {
              if (isdigit(palabra3[1]) ||
                  (palabra3[1] == '-' && isdigit(palabra3[2]))) {
                leido = strtol(palabra3 + 1, &palabra3, 10);
                if (leido >= INT_MIN && leido <= INT_MAX) {
                  itree_insertar(&arbolNuevo, intervaloE_crear(leido, leido));
                }
                else {
                  printf("Numero invalido.\n");
                  validez = 0;
                }
              } else {
                validez = 0;
              }
            }
            if (validez) {
              if (palabra3[0] == '}' && palabra3[1] == '\0') {
                printf("entrada correcta.\n");
                tablahash_insertar(tablita, palabra1, arbolNuevo);
              } else {
                printf(
                  "Entrada de creacion de conjunto por extension invalida.\n");
                itree_destruir(arbolNuevo);
              }
            }
            else {
              printf(
                "Entrada de creacion de conjunto por extension invalida.\n");
              itree_destruir(arbolNuevo);
            }
          }
        }

        /*********************************
         * CREAR CONJUNTO POR COMPRESION *
         *********************************/
        else if (palabra4 != NULL && palabra4[0] == ':'){
          char *palabra5 = strtok (NULL, " "); // Numero.
          char *check; // Variable utilizada para almacenar el sobrante del strtol.
          long leido1;
          long leido2;
          leido1 = strtol (palabra5, &check, 10);
          if (*check == '\0'){
            // Significa que efectivamente se leyo un numero.

            char *palabra6 = strtok(NULL, " "); // simbolo.

            // Si el simbolo es <=.
            if (strcmp (palabra6, "<=") == 0){
              if ((INT_MIN <= leido1 && leido1 <= INT_MAX)){
                char* palabra7 = strtok (NULL, " "); // variable.

                if (strcmp (palabra7, palabra3 + 1) == 0){
                  // Si la variable declarada en el 'tal que' es la misma...
                  char *palabra8 = strtok (NULL, " "); // simbolo.
                  char *palabra9 = strtok (NULL, " "); // numero.

                  leido2 = strtol (palabra9, &check, 10);
                  if (check[0] == '}' && check[1]  == '\0') {
                    if (leido1 <= leido2 && leido2 <= INT_MAX){
                      char *palabra10 = strtok (NULL, " ");
                      if (palabra10 == NULL){
                        itree_insertar (&arbolNuevo, intervaloE_crear(leido1, leido2));
                        printf ("\nImprimiendo arbol --------------------\n");
                        print2D(arbolNuevo);
                        printf ("\n --------------------\n");
                        tablahash_insertar(tablita, palabra1, arbolNuevo);
                      }
                    }
                    else {
                      printf ("Intervalo invalido, el extremo izquierdo"
                              "es mayor al extremo derecho, o bien el extremo"
                              "derecho se pasa del limite de ints.\n");
                      printf ("Tener en cuenta: INT_MIN = |%d|, "
                              "INT_MAX = |%d|\n\n", INT_MIN, INT_MAX);
                    }
                  }
                  else {
                    printf ("Numero del extremo derecho invalido.\n");
                    printf ("O bien caracteres extra luego del } que "
                            "cierra el conjunto.\n");
                    imprimir_menu();
                  }
                }
                else {
                  printf ("No hay correlacion con la variable declarada"
                          "en la declaracion del intervalo.\n");
                  imprimir_menu();
                }
              }
              else {
                printf("Se exceden los limetes de los enteros en alguno"
                       "de los intervalos. \n");
                printf ("Tener en cuenta: INT_MIN = |%d|, INT_MAX = |%d\n\n",
                        INT_MIN, INT_MAX);
              }
            }
            else {
              printf ("Simbolo invalido, los simbolos validos son <=.\n");
            }
          }
          else {
            printf ("Numero del extremo izquierdo invalido.\n");
            imprimir_menu();
          }

        }

        /***************
         * COMPLEMENTO *
         ***************/
        else if (strcmp(palabra3, "~") == 0){
          if (validar_alias_entrada(palabra4)){
            printf ("El conjunto: |%s| es igual al complemento de |%s|\n\n",
                    palabra1, palabra4);
            Conjunto contenedor = tablahash_buscar(tablita, palabra4);
            if (contenedor != NULL){
              tablahash_insertar(tablita, palabra1, itree_complemento (contenedor->conjunto));
            }
            else {
              printf ("El conjunto |%s|, no esta declarado.\n", palabra4);
            }
          }
          else {
            printf ("El ultimo alias del comando no es valido.\n\n");
          }
        }
        /********************************
         * INTERSECCION - UNION - RESTA *
         ********************************/
        else {
          if (validar_alias_entrada(palabra3)) {
            Conjunto contenedor1 = tablahash_buscar(tablita, palabra3);
            if (contenedor1 == NULL) {
              printf("El conjunto |%s|, no está definido.\n\n", palabra3);
            }
            else {
              char *palabra5 = strtok(NULL, " ");
              // extrapolar comportamiento..
              if (validar_alias_entrada(palabra5)) {
                Conjunto contenedor2 = tablahash_buscar(tablita, palabra5);
                if (contenedor1 == NULL) {
                  printf("El conjunto |%s|, no está definido.\n\n", palabra3);
                }
                else {
                  if (strtok(NULL, " ") == NULL) {
                    /****************
                     * INTERSECCION *
                     ****************/
                    switch (palabra4[0]) {
                      case '&':
                        printf("El conjunto |%s| es igual a la interseccion "
                               "entre |%s| y |%s|\n\n", palabra1, palabra3,
                               palabra5);
                        tablahash_insertar(tablita, palabra1,
                                           itree_interseccion(
                                             contenedor1->conjunto,
                                             contenedor2->conjunto));
                        break;
                        /*********
                         * UNION *
                         *********/
                      case '|':
                        printf("El conjunto |%s| es igual a la union "
                               "entre |%s| y |%s|\n\n", palabra1, palabra3,
                               palabra5);
                        tablahash_insertar(tablita, palabra1,
                                           itree_unir (contenedor1->conjunto,
                                                       contenedor2->conjunto));
                        break;
                        /*********
                         * RESTA *
                         *********/
                      case '-':
                        printf("El conjunto |%s| es igual a la resta "
                               "entre |%s| y |%s|\n\n", palabra1, palabra3,
                               palabra5);
                        tablahash_insertar(tablita, palabra1,
                                           itree_resta (contenedor1->conjunto,
                                                       contenedor2->conjunto));
                        break;

                      default:
                        printf("Operacion no valida.\n");
                        imprimir_menu();
                    }
                  } else {
                    printf("Los comandos interseccion, resta y union, solo"
                           "pueden ser realizados entre 2 conjuntos.\n\n");
                  }
                }

              } else {
                printf("El ultimo alias del comando no es valido.\n\n");
              }
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
