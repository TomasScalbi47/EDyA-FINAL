/**
 * Archivo de cabecera de nuestra implementacion de colas enlazadas.
 */

#ifndef __cola_h__
#define __cola_h__

/**
 * Estructura de nodo para cada elemento de la cola.
 * Cada nodo tiene un dato y un apuntador a otro nodo que sera el siguiente
 * en la cola. De esta forma se logra una Lista enlazada.
 */
typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;


/**
 * Estructura de Cola.
 * Es un tipo de lista enlazada en la cual los datos se ingresan a partir de
 * el nodo al que llamamos final, y se sacan desde el nodo al que llamamos
 * principio.
 * Tambien decidimos que la cola sea un apuntador a esta Estructura
 * puesto que es un objeto, y en todas las implementaciones nos manejamos de
 * esta forma.
 */
typedef struct _Cola {
  GNodo *principio;
  GNodo *final;
} *Cola;

/**
 * Tipo de dato para funciones que se apliquen sobre los datos de los nodos de
 * la cola.
 */
typedef void (*FuncionVisitante) (void *dato);

/**
 * Devuelve lo que definimos como cola vacia.
 */
Cola cola_crear ();

/**
 * Dada una cola, determina si esta es vacia o no.
 * Devuelve:  1 si es vacia.
 *            0 en caso contrario.
 */
int cola_es_vacia (Cola);

/**
 * Toma una cola.
 * Devuelve el dato del primer nodo de la misma.
 */
void* cola_primero (Cola);

/**
 * Dado un apuntador a una cola y un dato.
 * Modifica la cola, creando un nuevo nodo y colocandolo al final.
 */
void cola_encolar (Cola* , void*);

/**
 * Dado un apuntador cola.
 * Modifica la cola, quitando el primer elemento de la misma y liberandolo.
 */
void cola_desencolar (Cola*);

/**
 * Dada una cola y una funcion del tipo FuncionVisitante.
 * Recorre la cola aplicando la funcion a cada elemento.
 */
void cola_recorrer (Cola, FuncionVisitante);

/**
 * Toma un cola.
 * Desencola todos los elementos hasta que quede vacia.
 */
void cola_destruir (Cola);
#endif
