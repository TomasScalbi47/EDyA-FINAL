/**
 * Archivo de cabecera de nuestra implementacion de pilas enlazadas.
 */

#ifndef __pilaG_h__
#define __pilaG_h__

/**
 * Estructura de nodo para cada elemento de la pila.
 * Cada nodo tiene un dato y un apuntador a otro nodo que sera el siguiente
 * en la pila. De esta forma se logra una Lista enlazada.
 * Se tomo la decision de usar el nombre PGNodo puesto que sino se superoponia
 * con la definicion de los nodos (Exactamente igual) que esta en cola.h.
 */
typedef struct _PGNodo {
  void *dato;
  struct _PGNodo *sig;
} PGNodo;

/**
 * Estructura de Pila.
 * Es un tipo de lista enlazada en la cual los elementos se ingresan y se
 * quitan por el mismo lado, a traves de Pila.
 * Pila debe ser un puntero puesto que es un representante del comienzo de
 * la lista enlazada.
 */
typedef PGNodo *Pila;

/**
 * Tipo de dato para funciones que se apliquen sobre los datos de los nodos de
 * la pila.
 */
typedef void (*FuncionVisitante) (void *dato);

/**
 * Devuelve lo que definimos como pila vacia.
 */
Pila pila_crear ();

/**
 * Dada una pila, determina si esta es vacia o no.
 * Devuelve:  1 si es vacia.
 *            0 si es no vacia.
 */
int pila_es_vacia (Pila);

/**
 * Toma una pila.
 * Devuelve el dato del primer nodo de la misma.
 */
void* pila_ultimo (Pila);

/**
 * Dado un apuntador a una pila, y un dato.
 * Modifica la pila, creando un nuevo nodo y colocandolo en el tope.
 */
void pila_apilar (Pila*, void *dato);

/**
 * Dado un apuntador a una pila, y un dato.
 * Modifica la pila, quitando el tope y liberandolo.
 */
void pila_desapilar (Pila*);

/**
 * Dada una pila y una funcion del tipo FuncionVisitante.
 * Recorre la pila aplicando la funcion a cada elemento.
 */
void pila_recorrer (Pila, FuncionVisitante);

/**
 * Toma un pila.
 * Desapila todos los elementos hasta que quede vacia.
 */
void pila_destruir (Pila);
#endif
