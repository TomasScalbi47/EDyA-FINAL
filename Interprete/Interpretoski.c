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
#define TAM_INICIAL_BUFF 1
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

void mensaje_error (char* ident, char* data){
  printf ("ERROR.\n");
  int tipo = atoi(ident + 1);
  /**********************
   * ERRORES DE FORMATO *
   **********************/
  if (ident[0] == 'f'){
    printf ("No se respeta el formato.\n");

    switch (tipo) {
      case 0:
        printf ("El único comando aceptado de una palabra es 'salir'.\n");
        break;
      case 1:
        printf ("El comando imprimir solo acepta un conjunto.\n");
        break;
      case 2:
        printf ("El alias ingresado: |%s| no es válido.\n", data);
        printf ("Los alias aceptados son solo alfanumericos sin tildes.\n");;
        break;
      case 3:
        printf ("Comando incompleto.\n");
        printf ("El conjunto que se esta declarando debe estar igualado a algo.\n");
        break;
      case 4:
        printf ("Luego del primer alias sigue un '='\n");
        break;
      case 5:
        printf ("Creacion por extension invalida.\n");
        printf ("Final de la entrada invalida.\n");
        break;
      case 6:
        printf ("Creacion por extension invalida.\n");
        printf("Caracteres/numeros invalidos en la entrada.\n");
        break;
      case 7:
        printf ("Comando incompleto.\n");
        break;
      case 8:
        printf ("Numero del extremo izquierdo invalido.\n");
        break;
      case 9:
        printf ("No hay correlacion con la variable declarada"
                "en la declaracion del intervalo.\n");
        break;
      case 10:
        printf ("Simbolo invalido el simbolo valido es <=.\n");
        break;
      case 11:
        printf("Se exceden los limites de los enteros en alguno"
               "de los extremos. \n");
        break;
      case 12:
        printf ("Numero del extremo derecho invalido.\n");
        break;
      case 13:
        printf ("Intervalo invalido, el extremo izquierdo"
                "es mayor al extremo derecho, o bien el extremo"
                "derecho se pasa del limite de ints.\n");
        break;
      case 14:
        printf ("Basura al final.\n");
        break;
    }
    imprimir_menu();
  }
  /********************************
   * ERRORES DE USO DE INTERPRETE *
   ********************************/
  else if (ident[0] == 'u'){
    printf ("Mal uso de interprete.\n");

    switch (tipo) {
      case 0:
        printf ("El conjunto |%s| no esta definido.\n", data);
        break;
    }
  }

}

///**
// * Funcion utilizada luego de determinar que se esta intentando ingresar
// * un conjunto por compresion.
// */
//void crear_compresion (char* entradaPars, TablaHash *tabla, ITree arbolNuevo){
//  char *palabra5
//}
void interpretar (){
  TablaHash *tablita = tablahash_crear(TAM_TABLA_HASH, hasheo);

  char *entradaOriginal, *entradaParser;
  int salida = 0;

  /********************
   * IMPRIMIENDO MENU *
   ********************/
  imprimir_menu ();
  while (!salida){
    // Se lee la entrada.
    entradaOriginal = leer_entrada ();
    entradaParser = entradaOriginal;

    char *palabra1 = strtok (entradaParser, " ");
    char *palabra2 = strtok (NULL, " ");

    /********************
     * COMANDO DE SALIR *
     ********************/
    if (palabra2 == NULL){
      if (strcmp (palabra1, "salir") == 0) {
        salida = 1;
        tablahash_destruir(tablita);
      }
      else {
        mensaje_error ("f0", NULL);
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
          else {
            mensaje_error ("u0", palabra2);
          }
          // Liberando el contenedor, pero no el conjunto.
          free (contenedor);
        }
        else {
          mensaje_error ("f1", NULL);
        }
      }
      else {
        mensaje_error ("f2", palabra2);
      }
    }
      /********************
      * RESTO DE COMANDOS *
      *********************/
    else if (validar_alias_entrada (palabra1)){
      if (strcmp (palabra2, "=") == 0){
        char *palabra3 = strtok (NULL, " ");
        char *palabra4 = strtok (NULL, " ");
        ITree arbolNuevo = itree_crear();

        if (palabra3 != NULL) {
          /************************
           * CREACION DE CONJUNTO *
           ************************/
          if (palabra3 [0] == '{'){
            /********************************
             * CREAR CONJUNTO POR EXTENSION *
             ********************************/
            if (palabra4 == NULL){
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
                      // Se puede hacer tranquilamente la conversion de long
                      // a int puesto que se corroboro en el if.
                      itree_insertar(&arbolNuevo, intervaloE_crear(leido, leido));
                    }
                    else {
                      validez = 0;
                    }
                  }
                  else {
                    validez = 0;
                  }
                }

                if (validez) {
                  // Se valido toda la entrada excepto el final.
                  if (palabra3[0] == '}' && palabra3[1] == '\0') {
                    printf("Entrada por extension validada correcta.\n");
                    tablahash_insertar(tablita, palabra1, arbolNuevo);
                  }
                  else {
                    mensaje_error ("f7", NULL);
                    itree_destruir(arbolNuevo);
                  }
                }
                else {
                  mensaje_error ("f8", NULL);
                  itree_destruir(arbolNuevo);
                }
              }
            }

            /*********************************
             * CREAR CONJUNTO POR COMPRESION *
             *********************************/
            else if (palabra4[0] == ':'){
              char *palabra5 = strtok (NULL, " "); // Numero.
              if (palabra5 != NULL){
                char *check; // Variable utilizada para almacenar el sobrante del strtol.
                long leido1 = 0; // Almacenar primer numero.
                long leido2 = 0; // Almacenar segundo numero.

                leido1 = strtol (palabra5, &check, 10);
                if (*check == '\0'){
                  char *palabra6 = strtok(NULL, " "); // simbolo.
                  if (palabra6 != NULL){
                    // Si el simbolo es <=.
                    if (strcmp (palabra6, "<=") == 0){
                      if ((INT_MIN <= leido1 && leido1 <= INT_MAX)){
                        char* palabra7 = strtok (NULL, " "); // variable.
                        if (palabra7 != NULL){
                          // Correalcion con la variable?
                          if (strcmp (palabra7, palabra3 + 1) == 0){
                            // Si la variable declarada en el 'tal que' es la misma...
                            char *palabra8 = strtok (NULL, " "); // simbolo.
                            if (palabra8 != NULL){
                              if (strcmp (palabra8, "<=") == 0){
                                char *palabra9 = strtok (NULL, " "); // numero.
                                // Chequeando que comando no este incompleto.
                                if (palabra9 != NULL){
                                  if (palabra9[0] != '}'){
                                    leido2 = strtol (palabra9, &check, 10);
                                    if (check[0] == '}' && check[1] == '\0') {
                                      if (leido2 <= INT_MAX){
                                        char *palabra10 = strtok (NULL, " ");
                                        if (palabra10 == NULL){
                                          if (leido1 <= leido2) {
                                            itree_insertar(&arbolNuevo, intervaloE_crear(leido1, leido2));
                                            tablahash_insertar(tablita, palabra1, arbolNuevo);
                                          }
                                          else
                                            tablahash_insertar (tablita, palabra1, arbolNuevo);
                                        }
                                        else
                                          mensaje_error ("f14", NULL);
                                      }
                                      else
                                        mensaje_error ("f13", NULL);
                                    }
                                    else
                                      mensaje_error("f12", NULL);
                                  }
                                  else
                                    mensaje_error ("f12", NULL);
                                }
                                else
                                  mensaje_error ("f7", NULL);
                              }
                              else
                                mensaje_error ("f10", NULL);
                            }
                            else
                              mensaje_error ("f7", NULL);
                          }
                          else
                            mensaje_error ("f9", NULL);
                        }
                        else
                          mensaje_error("f7", NULL);
                      }
                      else
                        mensaje_error ("f11", NULL);
                    }
                    else
                      mensaje_error("f10", NULL);
                  }
                  else
                    mensaje_error ("f7", NULL);
                }
                else
                  mensaje_error ("f8", NULL);
              }
              else
                mensaje_error("f7", NULL);
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
                printf ("ERROR.\n");
                printf ("El conjunto |%s| no esta definido\n", palabra4);
              }
              free (contenedor);
            }
            else {
              printf ("ERROR.\n");
              printf ("No se respeta el formato.\n");
              printf ("El alias ingresado: |%s| no es válido.\n", palabra4);
              printf ("Los alias aceptados son solo alfanumericos sin tildes.\n");
            }
          }
            /********************************
             * INTERSECCION - UNION - RESTA *
             ********************************/
          else if (validar_alias_entrada(palabra3)) {
            Conjunto contenedor1 = tablahash_buscar(tablita, palabra3);
            if (contenedor1 != NULL) {
              if (palabra4 == NULL){
                tablahash_insertar(tablita, palabra1, contenedor1->conjunto);
              }
              else {
                char *palabra5 = strtok(NULL, " ");
                if (palabra5 != NULL){
                  if (validar_alias_entrada(palabra5)) {
                    Conjunto contenedor2 = tablahash_buscar(tablita, palabra5);
                    if (contenedor2 != NULL) {
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
                                               itree_unir(contenedor1->conjunto,
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
                                               itree_resta(contenedor1->conjunto,
                                                           contenedor2->conjunto));
                            break;

                          default:
                            printf("ERROR.\n");
                            printf("Operacion no valida.\n");
                            imprimir_menu();
                        }
                      } else {
                        printf("ERROR.\n");
                        printf("Basura al final.\n");
                        printf("Los comandos interseccion, resta y union, solo"
                               "pueden ser realizados entre 2 conjuntos.\n");
                      }
                    } else {
                      printf("ERROR.\n");
                      printf("El conjunto |%s| no está definido.\n", palabra5);
                    }
                    free(contenedor2);
                  }
                  else {
                    printf("ERROR.\n");
                    printf("No se respeta el formato.\n");
                    printf("El alias ingresado: |%s| no es válido.\n", palabra5);
                    printf(
                      "Los alias aceptados son solo alfanumericos sin tildes.\n");
                  }
                }
                else {
                  printf ("ERROR.\n");
                  printf ("No se respeta el formato.\n");
                  printf ("Operacion incompleta.\n");
                  imprimir_menu();
                }
              }
            }
            else {
              printf("ERROR.\n");
              printf("El conjunto |%s| no esta definido\n", palabra3);
            }
            free(contenedor1);
          }
          else {
            mensaje_error("f2", palabra3);
          }
        }
        else {
          mensaje_error ("f3", NULL);
        }
      }
      else {
        mensaje_error ("f4", NULL);
      }
    }
    else {
      mensaje_error ("f2", palabra1);
    }
    free (entradaOriginal);
  }

}


char* leer_entrada (){
  int tamBuffer = TAM_INICIAL_BUFF;
  int cantElementos = 0; // Contador de elementos en el array.
  char *buffer = malloc (sizeof(char) * tamBuffer); // buffer inicial.

  char entrada = getchar();
  while (entrada != '\n'){
    // Si el buffer está lleno, se "aumenta su tamaño".
    if (cantElementos >= tamBuffer - 1)
      buffer = aumentar_tamanio(buffer, &tamBuffer);
    // Se agrega elemento al array.
    buffer[cantElementos] = entrada;
    cantElementos += 1;

    entrada = getchar();
  }
  // Se agrega terminador al buffer para que sea considerado como un string.
  buffer[cantElementos] = '\0';
  // Reajustando el tamaño del buffer al minimo.
  buffer = realloc (buffer, ((cantElementos + 1) * sizeof(char)));
  return buffer;
}

char* aumentar_tamanio (char* buffer, int *tamAnterior){
  // Se creara un nuevo arreglo con el doble de tamaño y se copiaran sus elementos.
  int nuevoTamanio = *tamAnterior * 2;
  char* nuevoBuffer = malloc (sizeof(char) * nuevoTamanio);
  for (int i = 0; i < *tamAnterior; ++i)
    nuevoBuffer[i] = buffer[i];
  *tamAnterior = nuevoTamanio;
  // Luego de haber almacenado toda la data en el nuevo buffer, este se libera.
  free (buffer);
  return nuevoBuffer;
}

void imprimir_menu (){
  printf ("Solo se aceptan numeros enteros bajo la condicion de que sean ints.\n");
  printf ("Tener en cuenta: INT_MIN = |%d|, INT_MAX = |%d\n\n", INT_MIN, INT_MAX);
  printf ("Lista de comandos y formatos aceptados:\n");
  printf ("  * Cerrar el interprete: 'salir'\n");
  printf ("  * Imprimir un conjunto: 'imprimir A'\n");
  printf ("  * Crear conjunto por extension: 'A = {0,1,2,3}'\n");
  printf ("  * Crear conjunto por compresion: 'A = {x : -3 <= x <= 5}'\n");
  printf ("  * Unir conjuntos: 'A = B | C'\n");
  printf ("  * Intersecar conjuntos: 'A = B & C'\n");
  printf ("  * Complemento de un conjunto: 'A = ~ A'");
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


