#include <stdio.h>
#include <stdlib.h>
#include "cola.h" // Archivo con las declaraciones y comentado de las funciones.

Cola cola_crear (){
  return NULL;
}

int cola_es_vacia (Cola cola){
  return cola == NULL;
}

void* cola_primero (Cola cola){
  return cola->principio->dato;
}

void cola_encolar (Cola *cola, void *dato){
  // Creando nuevo nodo.
  GNodo *nuevoNodo = malloc (sizeof (GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  // Si la cola no es vacia..
  if (!cola_es_vacia(*cola)){
    // Se le informa al ultimo actual que su siguiente ahora es nuevoNodo.
    (*cola)->final->sig = nuevoNodo;
  }
  else {
    (*cola) = malloc (sizeof (struct _Cola));
    (*cola)->principio = nuevoNodo;
  }
  // Se cambia la referencia al final de la cola a nuevoNodo.
  (*cola)->final = nuevoNodo;
}

void cola_desencolar (Cola *cola){
  // Cola no vacia..
  if (!cola_es_vacia (*cola)){
    // Apuntador auxiliar para liberar el principio.
    GNodo *libertador = (*cola)->principio;
    // Se cambia la referencia de principio al segundo de la cola.
    (*cola)->principio = libertador->sig;
    // Se libera el anterior principio de la cola.
    free (libertador);

    // Si la cola se quedo sin elementos luego de desencolar..
    if ((*cola)->principio == NULL){
      // Se libera la cola y se coloca como vacia.
      free (*cola);
      (*cola) = NULL;
    }
  }
}

void cola_recorrer (Cola cola, FuncionVisitante visit){
  // Si la cola no es vacia..
  if (!cola_es_vacia (cola)){
    // Iterador para recorrer la cola como lista enlazada.
    GNodo *iterador = cola->principio;

    for (; iterador != NULL; iterador = iterador->sig){
      // Se aplica la funcion a cada nodo de la cola.
      visit (iterador->dato);
    }
  }
}

void cola_destruir (Cola cola){
  // Se desencola de a un elemento hasta que la cola sea vacia.
  while (!cola_es_vacia(cola)){
    cola_desencolar (&cola);
  }
}
