#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash) {
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
    // ver de cambiar a calloc.
  tabla->tabla = malloc(sizeof(HList) * capacidad);
  tabla->numElems = 0;

  // Se inicializan las listas como vacias.
  for (unsigned idx = 0; idx < capacidad; ++idx)
    tabla->tabla[idx] = NULL;

  return tabla;
}

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, char* clave, ITree conjunto) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  // Si el lugar estaba vacío, incrementamos el número de elementos.
  if (hlist_es_vacia (tabla->tabla[idx]))
    tabla->numElems++;

  hlist_insertar(&(tabla->tabla[idx]), conjunto, clave);
}

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
void* tablahash_buscar(TablaHash* tabla, void* clave) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  return hlist_buscar(tabla->tabla[idx], clave);
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir (TablaHash* tabla) {
  for (int i = 0; i < tabla->numElems; ++i){
    if (!hlist_es_vacia (tabla->tabla[i])){
      --tabla->numElems;
      hlist_destruir (&(tabla->tabla[i]));
      tabla->tabla[i] = NULL;
    }
  }

  free (tabla->tabla);
  free (tabla);
}
