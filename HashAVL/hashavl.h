/**
 * Este tipo de tablas hash sera implementada haciendo que sus casillas sean
 * arboles AVL.
 */
#ifndef __HASHAVL_H__
#define __HASHAVL_H__

#include "../AVL/avl.h"
/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */
typedef unsigned (*FuncionHash)(char* clave, unsigned capacidad);

/**
 * Estructura principal que representa la tabla hash.
 */
typedef struct {
  AVLClavesTree *tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
} TablaHash;

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear (unsigned capacidad, FuncionHash fun);

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar (TablaHash* tabla, char* clave, ITree conjunto);

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
Contenedor tablahash_buscar (TablaHash* tabla, char* clave);

/**
 * Destruye la tabla.
 */
void tablahash_destruir (TablaHash* tabla);



#endif
