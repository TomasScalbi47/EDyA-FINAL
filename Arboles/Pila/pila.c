#include <stdio.h>
#include <stdlib.h>
#include "pila.h" // Archivo con las declaraciones y comentado de las funciones.

Pila pila_crear (){
  return NULL;
}

int pila_es_vacia (Pila pila){
  return pila == NULL;
}

void* pila_ultimo (Pila pila){
  return pila->dato;
}

void pila_apilar (Pila *pila, void *dato){
  // Creando nuevo nodo.
  PGNodo *nuevoNodo = malloc (sizeof (PGNodo));
  nuevoNodo->dato = dato;
  // Se declara el nodo apuntando al final de la pila.
  nuevoNodo->sig = *pila;
  // Se cambia la referencia al final de la pila al nuevo nodo agregado.
  *pila = nuevoNodo;
}

void pila_desapilar (Pila *pila){
  // Si la pila es vacia..
  if (!pila_es_vacia (*pila)){
    // Apuntardor para poder liberar el tope de la pila.
    PGNodo *libertador = *pila;
    // Se cambia el final de la pila al siguiente.
    *pila = (*pila)->sig;
    free (libertador);
  }
}

void pila_recorrer (Pila pila, FuncionVisitante visit){
  // Se recorre la pila como una lista enlazada.
  while (pila != NULL){
    // Se aplica la funcion a cada elemento de la pila.
    visit (pila->dato);
    pila = pila->sig;
  }
}

void pila_destruir (Pila pila){
  // Se desapilan los elementos de a uno hasta que la pila sea vacia.
  while (!pila_es_vacia(pila)){
    pila_desapilar (&pila);
  }
}
