/**
 * Archivo de cabecera de mi implementación de arreglos de intervalos de
 * enteros.
 */

#ifndef __arrayI_h__
#define __arrayI_h__
/**
 * Se incluyen las funciones de intervalos de enteros para la creacion de
 * la estructura _arrayI.
 */
#include "intervaloE.h"

/**
 * Represento conjuntos numéricos de enteros a con un arreglo de intervalos
 * cerrados de números enteros. Las funciones serán implementadas de forma tal
 * que de ser necesario se expanda el tamaño del array, por eso consideré útil
 * incluir en la estructura, la cantidad de elementos del array.
 * La dificultad que suele traer utilizar esta estructura es cuando se
 * desea insertar elementos. En nuestro caso, esto sucederá solo cuando
 * se cree el conjunto por extensión. Puesto que luego este será ordenado
 * teniendo esto último como ventaja el hecho de que para unir cojuntos se
 * puede realizar en un nuevo array e ir insertando como si de la segunda
 * parte de un mergeSort se tratase (puesto que son "listas" ordenadas).
 */

typedef struct _arrayI {
  int capacidad;
  IntervaloE *array;
} ArrayI;

typedef ArrayI *Set;

/**
 * Defino estas macro para obtener el minimo y el maximo entre 2 numeros respec.
*/
#define min2(x, y) (((x) < (y)) ? (x) : (y))
#define max2(x, y) (((x) > (y)) ? (x) : (y))

/**
 * Se crea un conjunto vacío.
 */
Set set_crear ();

/**
 * Dado un conjunto.
 * Lo destruye, liberando toda su memoria asociada.
 */
void set_destruir (Set conjunto);

/**
 * Dados dos extremos de un intervalo.
 * Devuelve el conjunto.
 */
Set set_crear_compresion (int extIzq, int extDer);

/**
 * Dado un conjunto y un intervalo.
 * Inserta el intervalo de forma inteligente, es decir:
 *      Si el intervalo interseca con elementos del conjunto entonces se los
 *      come.
 */
Set set_insertar (Set conjunto, IntervaloE intervalo);



#endif
