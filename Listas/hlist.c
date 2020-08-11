#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hlist.h"



HList hlist_crear (){
  return NULL;
}

int hlist_es_vacia (HList lista){
  return lista == NULL;
}

void hlist_insertar (HList *lista, ITree conjunto, char *clave){
  // Primero se compruba si hay o no un conjunto con la misma clave.
  // De ser el caso, se procede a reemplazar su dato, es decir, el conjunto.
  int reemplazado = 0;
  HList iterador = *lista;

  while (!hlist_es_vacia(iterador) && !reemplazado){
    if (strcmp (iterador->clave, clave) == 0) {
      itree_destruir(iterador->conjunto);
      iterador->conjunto = conjunto;
      reemplazado = 1;
    }
    else
      iterador = iterador->sig;
  }

  // Si iterador es null, significa que no se reemplazo.
  if (hlist_es_vacia(iterador)) {
    // Creando el nodo.
    HNodo *nuevoNodo = malloc (sizeof (HNodo));
    nuevoNodo->conjunto = conjunto;
    nuevoNodo->clave = malloc (sizeof (char) * strlen (clave) + 1);
    strcpy(nuevoNodo->clave, clave);
    nuevoNodo->sig = *lista;

    *lista = nuevoNodo;
  }
}

void hlist_destruir (HList *lista){
  HNodo *iterador;

  for (; !hlist_es_vacia(*lista); *lista = iterador ){
    iterador = (*lista)->sig;
    // Libera cada dato de acuerdo al metodo dado.
    itree_destruir((*lista)->conjunto);
    free ((*lista)->clave);
    // Libera cada nodo.
    free (*lista);
  }
}

Conjunto hlist_buscar (HList lista, char *clave){
  Conjunto contenedor = NULL;
  HNodo *iterador = lista;
  int encontrado = 0;

  for (; iterador != NULL && !encontrado; ) {
    if (strcmp(iterador->clave, clave) == 0){
      encontrado = 1;
      // Se le asigna tamaño a contenedor para que pueda almacenar el arbol.
      contenedor = malloc (sizeof (ITree));
      contenedor->conjunto = iterador->conjunto;
    }
    else
      iterador = iterador->sig;
  }

  return contenedor;
}