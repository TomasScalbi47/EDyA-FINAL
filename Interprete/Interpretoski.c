#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "interprete.h"
#define TAM_INICIAL_BUFF 50
#define TAM_TABLA_HASH 100

unsigned int hasheo(char *alias, unsigned capacidad) {
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

void operaciones (char *entradaParser, char *destino, char* nombre1,
                  char *operacion, TablaHash *tabla){

  Conjunto contenedor1 = tablahash_buscar(tabla, nombre1);
  // Se corrobora que exista el conjunto 'nombre1'.
  if (contenedor1 != NULL) {
    /****************
     * REASIGNACION *
     ****************/
    // Si la entrada termina alli, significa que es el caso de reasignacion.
    if (operacion == NULL)

      tablahash_insertar(tabla, destino, itree_copiar(contenedor1->conjunto));
    // La entrada no termina alli, se continua.
    else {
      char *nombre2 = strsep(&entradaParser, " ");
      // Se corrobora que la entrada no quede incompleta.
      if (nombre2 != NULL){
        // Se corrobora que 'nombre2' sea un nombre de conjunto valido.
        if (validar_alias_entrada(nombre2)) {
          Conjunto contenedor2 = tablahash_buscar(tabla, nombre2);
          // Se corrobora que exista el conjunto 'nombre2'.
          if (contenedor2 != NULL) {
            // Se corrobora que la entrada termine alli. Sino habria basura.
            if (strsep(&entradaParser, " ") == NULL) {
              /****************
               * INTERSECCION *
               ****************/
              switch (operacion[0]) {
                case '&':
                  tablahash_insertar(tabla, destino,
                                     itree_interseccion(
                                       contenedor1->conjunto,
                                       contenedor2->conjunto));
                  break;
                  /*********
                   * UNION *
                   *********/
                case '|':
                  tablahash_insertar(tabla, destino,
                                     itree_unir(contenedor1->conjunto,
                                                contenedor2->conjunto));
                  break;
                  /*********
                   * RESTA *
                   *********/
                case '-':
                  tablahash_insertar(tabla, destino,
                                     itree_resta(contenedor1->conjunto,
                                                 contenedor2->conjunto));
                  break;

                default:
                  mensaje_error ("f18", operacion);
              }
            }
            else
              mensaje_error("f17", NULL);
          }
          else
            mensaje_error ("u0", nombre2);
          // Se libera el contenedor, pero no el conjunto.
          free(contenedor2);
        }
        else
          mensaje_error ("f2", nombre2);
      }
      else
        mensaje_error ("f16", NULL);
    }
  }
  else
    mensaje_error ("u0", nombre1);
  // Se libera el contenedor, pero no el conjunto.
  free(contenedor1);
}

void complemento (char *destino, char *origen, TablaHash *tabla){
  // Se corrobora que la entrada no haya terminado en '~' y quede incompleta.
  if (origen != NULL){
    // Se corrobora que sea un alias valido.
    if (validar_alias_entrada(origen)){
      Conjunto contenedor = tablahash_buscar(tabla, origen);
      // Se corrobora que exista el conjunto 'origen'.
      if (contenedor != NULL)
        tablahash_insertar(tabla, destino, itree_complemento (contenedor->conjunto));
      else
        mensaje_error ("u0", origen);
      // Se libera el contenedor, no el conjunto.
      free (contenedor);
    }
    else
      mensaje_error ("f2", origen);
  }
  else
    mensaje_error("f7", NULL);
}

void imprimir (char *entradaParser, char *origen, TablaHash *tabla,
               FuncionImpresion imprimir){
  // Validando alias del conjunto que se desea imprimir
  if (validar_alias_entrada(origen)){
    // Chequeando que la entrada no contenga basura.
    if (strsep (&entradaParser, " ") == NULL){
      Conjunto contenedor = tablahash_buscar(tabla, origen);
      // Se chequea que exista un conjunto declarado como 'origen'.
      if (contenedor != NULL){
        imprimir (contenedor->conjunto);
        printf ("\n");
      }
      else
        mensaje_error ("u0", origen);
      // Liberando el contenedor, pero no el conjunto.
      free (contenedor);
    }
    else
      mensaje_error ("f1", NULL);
  }
  else
    mensaje_error ("f2", origen);
}

void crear_extension (char* palabra3, char* destino, TablaHash *tabla,
                      ITree *arbolNuevo){
  // palabra3: "{..."
  // Si es el conjunto vacio no se hace nada..
  if (! (palabra3[1] == '}' && palabra3[2] == '\0')) {
    // No es el conjunto vacio.
    long leido = 0;
    int validez = 1;
    // Mientras no se ingrese basura ni numeros invalidos.
    // No se llegue al final de la declaracion del conjunto.
    // Ni termine abruptamente el array.
    // Se validan las entradas y se insertan en el arbol.
    for (int i = 0; palabra3[0] != '}' && palabra3[0] != '\0' && validez; ++i) {
      if (isdigit(palabra3[1]) ||
          (palabra3[1] == '-' && isdigit(palabra3[2]))) {
        leido = strtol(palabra3 + 1, &palabra3, 10);
        if (leido >= INT_MIN && leido <= INT_MAX) {
          // Se puede hacer tranquilamente la conversion de long
          // a int puesto que se corroboro en el if.
          itree_insertar(arbolNuevo, intervaloE_crear(leido, leido));
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
      if (!(palabra3[0] == '}' && palabra3[1] == '\0')) {
        // Final invalido.
        mensaje_error ("f7", NULL);
        itree_destruir(*arbolNuevo);
      }
    }
    else {
      // Invalido.
      mensaje_error ("f8", NULL);
      itree_destruir(*arbolNuevo);
    }
  }

  tablahash_insertar (tabla, destino, *arbolNuevo);
}


void crear_compresion (char* entradaPars, char* destino, char *variable,
                       TablaHash *tabla, ITree *arbolNuevo){
  char *extremoIzquierdo = strsep (&entradaPars, " ");
  // Se corrobora que la entrada no termine alli.
  if (extremoIzquierdo != NULL){
    char *check; // Variable utilizada para almacenar el sobrante del strtol.
    long leido1 = 0; // Almacenar primer numero.
    long leido2 = 0; // Almacenar segundo numero.

    leido1 = strtol (extremoIzquierdo, &check, 10);
    // Se corrobora que se haya leido satisfactoriamente un numero.
    if (*check == '\0'){
      char *simbolo1 = strsep(&entradaPars, " ");
      // Se corrobora que la entrada no termine alli.
      if (simbolo1 != NULL){
        // Se corrobora que el simbolo sea correcto.
        if (strcmp (simbolo1, "<=") == 0){
          // Se corrobora que el extremo izquierdo este dentro de los limites.
          if (validar_int (leido1)){
            char* variable2 = strsep (&entradaPars, " ");
            // Se corrobora que la entrada no termine alli.
            if (variable2 != NULL){
              // Se corrobora la correalcion con la variable1.
              if (strcmp (variable2, variable + 1) == 0){
                char *simbolo2 = strsep (&entradaPars, " ");
                // Se corrobora que la entrada no termine alli.
                if (simbolo2 != NULL){
                  // Se corrobora que el simbolo2 sea correcto.
                  if (strcmp (simbolo2, "<=") == 0){
                    char *extremoDerecho = strsep (&entradaPars, " ");
                    // Se corrobora que la entrada no termine alli.
                    if (extremoDerecho != NULL){
                      // Se corrobora que el extremo derecho no sea '}'.
                      if (extremoDerecho[0] != '}'){
                        leido2 = strtol (extremoDerecho, &check, 10);
                        // Se corrobora que luego del extremo derecho, la
                        // entrada sea correcta.
                        if (check[0] == '}' && check[1] == '\0') {
                          // Se corrobora que el extremo derecho este dentro
                          // de los limites,
                          if (validar_int (leido2)){
                            // Se corrobora que la entrada termine alli.
                            if (strsep (&entradaPars, " ") == NULL){
                              // Si el intervalo tiene sentido se inserta.
                              if (leido1 <= leido2) {
                                itree_insertar(arbolNuevo, intervaloE_crear (leido1, leido2));
                                tablahash_insertar(tabla, destino, *arbolNuevo);
                              }
                              // Caso contrario se inserta el conjunto vacio.
                              else
                                tablahash_insertar (tabla, destino, *arbolNuevo);
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
  printf ("__________________________________________________________________________\n");
  printf ("| Solo se aceptan numeros enteros bajo la condicion de que sean ints.    |\n");
  printf ("| Tener en cuenta: INT_MIN = |%d|, INT_MAX = |%d|       |\n", INT_MIN, INT_MAX);
  printf ("|                                                                        |\n");
  printf ("| Lista de comandos y formatos aceptados:                                |\n");
  printf ("|  * Cerrar el interprete: 'salir'                                       |\n");
  printf ("|  * Imprimir un conjunto: 'imprimir A'                                  |\n");
  printf ("|  * Imprimir en 2d un conjunto: 'imprimir2D A'                          |\n");
  printf ("|  * Imprimir menu: 'menu'                                               |\n");
  printf ("|  * Crear conjunto por extension: 'A = {0,1,2,3}'                       |\n");
  printf ("|  * Crear conjunto por compresion: 'A = {x : -3 <= x <= 5}'             |\n");
  printf ("|  * Unir conjuntos: 'A = B | C'                                         |\n");
  printf ("|  * Intersecar conjuntos: 'A = B & C'                                   |\n");
  printf ("|  * Complemento de un conjunto: 'A = ~ A'                               |\n");
  printf ("|  * Restar conjuntos: 'A = B - C'                                       |\n");
  printf ("--------------------------------------------------------------------------\n");
}

int validar_alias_entrada (char *alias){
  int devolver = 1;
  // Se corrobora que no haya ningun caracter que se escape de la norma.
  for (int i = 0; alias[i] != '\0' && devolver == 1; ++i){
    if (!isalpha (alias[i]) && !isdigit(alias[i]))
      devolver = 0;
  }
  return devolver;
}

int validar_int (long numero){
  return (INT_MIN <= numero && numero <= INT_MAX);
}

void mensaje_error (char* ident, char* data){

  printf ("ERROR.\n");
  printf ("*********************************************************\n");
  int tipo = atoi(ident + 1);


  /**********************
   * ERRORES DE FORMATO *
   **********************/
  if (ident[0] == 'f'){
    printf ("No se respeta el formato.\n");

    switch (tipo) {
      case 0:
        printf ("Comando de una sola palabra desconocido.\n");
        printf ("Los unicos conandos de una sola palabra validos son 'salir' y 'menu'.\n");
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
      case 15:
        printf ("Creacion de conjunto invalida.\n");
        printf ("Se detecto la siguiente basura: |%s|\n", data);
        break;
      case 16:
        printf ("Operacion incompleta.\n");
        printf ("Es necesario tener 2 conjuntos para realizar una operacion.\n");
        break;
      case 17:
        printf("Basura al final.\n");
        printf("Los comandos interseccion, resta y union, solo"
               "pueden ser realizados entre 2 conjuntos.\n");
        break;
      case 18:
        printf ("Operacion |%s| no valida.\n", data);
        break;
    }
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
  printf ("*********************************************************\n");
}

void interpretar (){
  // Creando tabla hash.
  TablaHash *tablita = tablahash_crear(TAM_TABLA_HASH, hasheo);
  // Variables utiles.
  char *entradaOriginal, *entradaParser;
  int salida = 0;

  /********************
   * IMPRIMIENDO MENU *
   ********************/
  imprimir_menu ();

  while (!salida){
    // Se lee la entrada.
    entradaOriginal = leer_entrada ();
    // Como se trabaja con strsep, es necesario tener una referencia al comienzo
    // de la cadena para su posterior liberacion.
    entradaParser = entradaOriginal;

    char *palabra1 = strsep(&entradaParser, " ");
    char *palabra2 = strsep(&entradaParser, " ");

    /*************************
     * COMANDOS DE 1 PALABRA *
     *************************/
    if (palabra2 == NULL){
      // Hay solo 2 comandos de una palabra. 'salir' y 'menu'.
      if (strcmp (palabra1, "salir") == 0) {
        salida = 1;
        tablahash_destruir(tablita);
      }
      else if (strcmp (palabra1, "menu") == 0)
        imprimir_menu ();
      else
        mensaje_error ("f0", NULL);
    }

      /***********************
      * COMANDOS DE IMPRIMIR *
      ************************/
      // Comando de imprimir conjunto.
    else if (strcmp (palabra1, "imprimir") == 0)
      imprimir (entradaParser, palabra2, tablita, itree_imprimir);
    else if (strcmp (palabra1, "imprimir2D") == 0)
      imprimir (entradaParser, palabra2, tablita, print2D);

      /********************
      * RESTO DE COMANDOS *
      *********************/
      // Luego de los casos anteriores, para que el comando tenga sentido, la
      // primer palabra leida debe ser un alias valido.
    else if (validar_alias_entrada (palabra1)){
      // Se corrobora que la siguiente 'palabra' sea un '='.
      if (strcmp (palabra2, "=") == 0){
        char *palabra3 = strsep (&entradaParser, " ");
        char *palabra4 = strsep (&entradaParser, " ");
        ITree arbolNuevo = itree_crear();
        // Se corrobora que el comando no este incompleto.
        if (palabra3 != NULL) {
          /************************
          * CREACION DE CONJUNTO *
          ************************/
          if (palabra3 [0] == '{'){
            /********************************
             * CREAR CONJUNTO POR EXTENSION *
             ********************************/
            if (palabra4 == NULL)
              crear_extension (palabra3, palabra1, tablita, &arbolNuevo);
              /*********************************
               * CREAR CONJUNTO POR COMPRESION *
               *********************************/
            else if (palabra4[0] == ':')
              crear_compresion (entradaParser, palabra1, palabra3, tablita,
                                &arbolNuevo);
            else
              mensaje_error("f15", palabra4);
          }

            /***************
             * COMPLEMENTO *
             ***************/
          else if (strcmp(palabra3, "~") == 0)
            complemento (palabra1, palabra4, tablita);

            /***********************************************
             * INTERSECCION - UNION - RESTA - REASIGNACION *
             ***********************************************/
            // Se corrobora que entonces la palabra3 sea un alias valido.
          else if (validar_alias_entrada(palabra3))
            operaciones (entradaParser, palabra1, palabra3, palabra4, tablita);
          else
            mensaje_error("f2", palabra3);
        }
        else
          mensaje_error ("f3", NULL);
      }
      else
        mensaje_error ("f4", NULL);
    }
    else
      mensaje_error ("f2", palabra1);

    free(entradaOriginal);
  }
}