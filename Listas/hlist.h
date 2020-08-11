#ifndef __HLIST_H__
#define __HLIST_H__

#include "../Arboles/ITree1.h"

/**
 *  Declaro el conjunto de esta manera para que sea facil reconocer la diferencia
 *  entre un conjunto vacio y un conjunto no encontrado en la tabla hash.
 */
typedef struct Conjunto {
  ITree conjunto;
} *Conjunto;

/**
 *  HNodo es la estructura que representa cada nodo de una hlist.
 *  El valor en nuestro caso es un arbol.
 *  El valor clave es el alias, es decir la clave antes del hasheo.
 */
typedef struct _HNodo {
  ITree conjunto;
  char *clave;
  struct _HNodo *sig;
} HNodo;

/**
 *  La estructura HList representa una lista enlazada.
 */
typedef HNodo *HList;


/**
 * Devuelve una hlist vacia.
 */
HList hlist_crear ();

/**
 *  Dada una lista, determina si esta es vacia o no.
 */
int hlist_es_vacia (HList lista);

/**
 * Tom un puntero a Hlist y un dato.
 * Crea un nuevo nodo que contiene el dato argumento y lo agrega
 * al comienzo de la lista.
 */
void hlist_insertar (HList *lista, ITree conjunto, char *clave);

/**
 * Dada una lista enlazada, libera la lista y utiliza una funcion Destruir
 * personalizada para liberar el tipo de dato que se este llevando en ella.
 */
void hlist_destruir (HList *lista);

/**
 * Dada una lista enlazada y un dato.
 * Devuelve un apuntador al mismo.
 */
Conjunto hlist_buscar (HList lista, char *clave);
#endif
