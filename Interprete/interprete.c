#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arboles/ITree1.h"//Dentro de ITree1.h se incluye IntervalosE.h
#include "interprete.h" //Dentro de interprete.h tambien, pero por los "ifndef"
                        //se usa la defincion de ITree1.h y no hay problemas.

#define BUFFER 80 //Constante utilizada para el buffer.

void interprete (){
  // Se crea un arbol.
  ITree arbolEjemplo = itree_crear ();
  // Se crea el intervalo auxiliar.
  IntervaloE intervaloEjemplo;
  char buffer[BUFFER];
  char accion = ' ';
  int banderaScan = 1;
  // Se crea el arbol auxiliar que se va a usar solo en caso de tener que
  // intersecar.
  ITree resultado;

  while (accion != 's'){
    // Se lee una linea a traves de la entrada estandar.
    banderaScan = scanf ("%[^\n]", buffer);
    // Se lee el \n de la linea. Tambien es de utilidad para el caso en el que
    // se ingrese solo \n por consola.
    getc (stdin);
    if (banderaScan == 0)
      printf ("Entrada invalida, ingrese algo.\n");
    else{

      // Se valida la entrada, se guarda la accion que se va a realizar y se
      // modifica el intervalo de ser necesario para esa accion.
      accion = validar_entrada (buffer, &intervaloEjemplo);
      switch (accion) {
        case 'i':
          itree_insertar (&arbolEjemplo, intervaloEjemplo);
          break;
        case 'e':
          itree_eliminar_dato (&arbolEjemplo, intervaloEjemplo);
          break;
        case '?':
          resultado = itree_intersecar (arbolEjemplo, intervaloEjemplo);
          if (resultado == NULL)
            printf ("No.\n");
          else {
            printf ("Si, ");
            intervaloE_imprimir (resultado->intervalo);
            printf("\n");
          }
          break;
        case 'd':
          printf(" ");
          itree_recorrer_dfs (arbolEjemplo, intervaloE_imprimir); printf("\n");
          break;
        case 'b':
          printf(" ");
          itree_recorrer_bfs (arbolEjemplo, intervaloE_imprimir); printf("\n");
          break;
        case 's':
          printf ("Gracias por usar el interprete!\n");
          break;
        default:
          break;
      }
    }
  }
  itree_destruir(arbolEjemplo);
}

char validar_entrada (char* entrada, IntervaloE* intervalo){
  char accion = ' ';

  if (!strcmp (entrada, "dfs")){
    accion = 'd';
  }
  else if (!strcmp (entrada, "bfs")){
    accion = 'b';
  }
  else if (!strcmp (entrada, "salir")){
    accion = 's';
  }
  else if ((entrada[0] == 'i' || entrada[0] == 'e' || entrada[0] == '?') &&
   entrada[1] == ' ' && entrada[2] == '['){
    if (validar_argumento (entrada)){
      // Si la entrada es valida extraemos los extremos del intevalo de la misma.
      sscanf (entrada + 3, "%d,%d]", &(intervalo->extIzq),
       &(intervalo->extDer));
      // Chequeamos que el intervalo sea valido.
      if (intervaloE_validar (*intervalo))
        accion = entrada[0];
      else {
        printf("Intervalo invalido:");
        printf(" El extremo izquierdo es mayor que el derecho\n");
      }
    }
  }
  else {
    printf ("Comando totalmente invalido.\n");
    printf ("Los comandos validos son:\ni [x,y]\ne [x,y]\n");
    printf ("? [x,y]\nbfs\ndfs\nsalir\n");
  }

  return accion;
}

int validar_argumento (char *entrada){
  int validez = 0;
  // Declarando banderas.
  int coma = 0;     // bandera que indica si se coloco o no una coma
  int punto = 0;    // bandera que indica si se coloco o no un punto
  int basura = 0;   // caracteres no desesados dentro del intervalo
  int espacioM = 0; // espacio mal colocado.
  int menos = 0;    // bandera que indica si se coloco o no un signo menos
  int exp = 0;      // bandera que indica si hay una e mal colocada
  int i = 3;        // contador luego del '[' en la entrada


  for (; entrada[i] != ']' && entrada[i] != '\0' && !basura && !espacioM; ++i){
    // Si se ingresa una coma, y esta es valida. Se resetean los contadores de
    // punto y signo menos y se modifica la bandera de coma a 1, lo que
    // implicara que si se ingresa otra coma esta sera invalida.
    if (entrada[i] == ',' && validar_coma (entrada, coma, i)) {
      coma = 1;
      punto = 0;
      menos = 0;
      exp = 0;
    }

    // Si se ingreso un signo menos y es valido. Se modifica la bandera de signo
    // menos a 1, lo que implicara que si se ingresa otro signo menos este sera
    // tomado invalido.
    else if (entrada[i] == '-' && validar_sign_menos (entrada, menos, i))
      menos = 1;

    // Si se ingreso un punto y es valido. Se modifica la bandera de punto a 1,
    // lo que implicara que si se ingresa otro punto este sera tomado invalido.
    else if (entrada[i] == '.' && validar_punto (entrada, punto, i))
      punto = 1;

    // Si se ingreso un espacio en blanco y es valido. Se modifica la bandera de
    // espacio en blanco a 1, lo que implicara que si se ingresa otro espacio en
    // blanco este sera tomado invalido.
    else if (entrada[i] == ' ' && !validar_espacio (entrada, i))
      espacioM = 1;

    else if (entrada[i] == 'e' && validar_exp (entrada, exp, i)){
      exp = 1;
      menos = 0;
      punto = 1;
    }

    // Si se ingreso algo diferente a un espacio o numero (distinguimos el caso
    // de espacio en blanco para identificarlo como un error particular).
    // Se modifica la bandera de basura indicando que se ingreso basura en el
    // intervalo.
    else if (entrada[i] != ' ' && !validar_numero (entrada[i]))
      basura = 1;
  }
  // Si se salio del bucle por los siguientes motivos, significa que hubo
  // algun error.
  if (basura == 1)
    printf ("Basura en el argumento.\n");
  else if (espacioM)
    printf("Hay AL MENOS un espacio mal ubicado.\n");
  else if (coma == 0)
    printf ("El intervalo esta incompleto.\n");
  else if (entrada[i] == '\0')
    printf ("Todo intervalo debe finalizar con un ].\n");
  else if (entrada[i + 1] != '\0')
    printf ("Mas de un argumento, o basura al final.\n");
  // Si no hubo errores, se modifica el valor de validez a 1, indicando que
  // la entrada es valida.
  else
    validez = 1;

  return validez;
}

int validar_coma (char *entrada, int bandera, int i){
  // Si no se coloco ninguna coma en la entrada aun, el anterior
  // a la coma es un numero y el siguiente es un numero, un espacio o un signo
  // menos, se dice que es una coma valida.
  return !bandera && validar_numero (entrada[i-1]) &&
    (validar_numero (entrada[i+1]) || entrada[i+1] == ' ' || entrada[i+1] == '-');
}

int validar_sign_menos (char *entrada, int bandera, int i){
  // Si no se coloco ningun signo menos para este numero, el anterior es un '['
  // (caso extremo izquierdo intervalo), o un ' ' (caso ", -x"), o una ','
  // (caso ",-x"), y el siguiente debe ser siempre un numero.
  // Se dice que es un signo menos valido.
  return !bandera && (entrada[i-1] == ' ' || entrada[i-1] == '[' ||
    entrada[i-1] == ',' || entrada[i-1] == 'e') && (validar_numero(entrada[i+1]));
}

int validar_punto (char *entrada, int bandera, int i){
  // Si no se coloco ningun punto para este numero, el anterior es un numero y
  // el siguiente tambien, se dice que es un punto valido.
  return !bandera && validar_numero (entrada[i-1]) &&
    validar_numero (entrada[i+1]);
}

int validar_numero (char entrada){
  // Si el valor ascii del caracter esta entre 0 y 9 incluidos, se trata de un
  // numero.
  return (entrada >= '0' && entrada <= '9');
}

int validar_espacio (char* entrada, int i){
  // Si el espacio esta entre una coma y un numero se dice que es valido.
  // Es el unico espacio valido dentro del argumento.
  return (entrada[i-1] == ',' &&
   (validar_numero (entrada[i + 1]) || entrada[i + 1] == '-'));
}

int validar_exp (char* entrada, int bandera, int i){
  // Si no hay una e en el numero actual, si el anterior es un numero y el
  // siguiente es un numero o un menos, se dice que es una e valida.
  return (bandera == 0 && validar_numero (entrada[i - 1]) &&
   (validar_numero (entrada[i + 1]) || entrada[i + 1] == '-'));
}
