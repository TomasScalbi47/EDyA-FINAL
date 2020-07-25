#ifndef __ITree_H__
#define __ITree_H__

#include "Intervalos/intervaloE.h"




/**
 * Estructura que representa cada nodo (o subarbol) de un arbol de intervalos.
 * Cada nodo tiene:
 *  - un intervalo
 *  - un double que representa el maximo extremo derecho de ese subarbol
 *  - un int que representa la altura de ese subarbol
 *  - 2 apuntadores a 2 nodos que representan los hijos del subarbol actual
 */
typedef struct _ITreeNodo {
  IntervaloE intervalo;
  double maxExtDer;
  int altura;
  struct _ITreeNodo *left;
  struct _ITreeNodo *right;
} ITreeNodo;

/**
 * Estructura de ITree.
 * El ITree (o arbol de intervalos) es un tipo de AVLTree que trabaja
 * especificamente con intervalos.
 */
typedef ITreeNodo *ITree;

/**
 * Tipo de dato para funciones que se apliquen sobre los datos de los nodos del
 * arbol.
 */
typedef void (*FuncionQueVisita) (IntervaloE dato);
typedef void (*FuncionAplicar) (ITree *arbol, IntervaloE);

/**
 * Devuelve lo que determinamos como un arbol vacio.
 */
ITree itree_crear ();

/**
 *  Toma un arbol y devuelve 1 si es vacio y 0 en caso contrario.
 */
int itree_es_vacio (ITree);

/**
 * Dado un arbol.
 * Devuelve la altura del mismo.
 * Aunque en la declaracion del tipo de dato de arboles agregamos un campo
 * que guarda la altura del arbol, decidimos hacer esta funcion puesto que
 * como consideramos al arbol vacio como NULL, este no tiene campo altura.
 */
int itree_altura(ITree arbol);

/**
 * Dado un arbol.
 * Devuelve el factor de balance de un arbol.
 * Definido como la altura del subarbol izquierdo menos la del subarbol derecho.
 */
int itree_factor_balance (ITree arbol);

/**
 * Toma un apuntador a un arbol.
 * Calcula la altura de ese subarbol y lo guarda en el parametro
 * altura del nodo raiz del subarbol que se tomo como parametro.
 */
void itree_actualizar_altura (ITree *arbol);

/**
 * Toma un apuntador a un arbol.
 * Calcula el maximo extremo derecho de intervalo para ese subarbol
 * y lo guarda en el parametro maxExtDer del nodo raiz del subarbol que se
 * tomo como parametro.
 */
void itree_mayor_extDer (ITree *arbol);

/**
 * Dado un arbol, obtiene su factor de balance y de ser nesecario lo balancea
 * aplicando las rotaciones correspondientes y actualizando sus campos de altura
 * y maxExtDer.
 * Devuelve el arbol rotado.
 */
ITree itree_balancear (ITree arbol);

/**
 * Dado un arbol, realiza una rotacion simple a derecha. Ademas se actualizan
 * los campos de altura y maxExtDer de forma que el arbol resultante sea
 * correcto.
 * Devuelve el arbol luego de la rotacion.
 */
ITree itree_rotacion_der (ITree arbol);

/**
 * Dado un arbol, realiza una rotacion simple a izquierda. Ademas se actualizan
 * los campos de altura y maxExtDer de forma que el arbol resultante sea
 * correcto.
 * Devuelve el arbol luego de la rotacion.
 */
ITree itree_rotacion_izq (ITree arbol);

/**
 * Toma un arbol y un intervalo.
 * Elimina todas las colisiones con el intervalo dado y luego utiliza
 * itree_insercion para insertar el intervalo que contiene a la union de todos
 * los conjuntos con los que interseco.
 */
void itree_insertar (ITree *arbol, IntervaloE);

/**
 *  Toma un arbol y un intervalo.
 *  Inserta el intervalo en el arbol respetando las propiedades del arbol AVL.
 *  Luego chequea si cada subarbol que se cambio cuando se ingreso el nodo
 *  quedo desbalanceado. En ese caso lo balancea aplicando las rotaciones
 *  correspondientes.
 */
void itree_insercion (ITree *arbol, IntervaloE);

ITree itree_unir (ITree arbol1, ITree arbol2);

/**
 *  Toma un arbol y un intervalo.
 *  Elimina el intervalo del arbol respetando las propiedades del arbol AVL.
 *  Luego chequea si cada subarbol que se cambio cuando se elimino el nodo
 *  quedo desbalanceado. En ese caso lo balancea aplicando las rotaciones
 *  correspondientes.
 */
void itree_eliminar_dato (ITree *arbol, IntervaloE);

/**
 *  Toma un apuntador a un arbol.
 *  Elimina el nodo que se encuentra mas a la izquierda de ese arbol y
 *  devuelve el intervalo que se encontraba en el nodo eliminado.
 */
IntervaloE itree_eliminar_minimo (ITree *arbol);

/**
 * Toma un arbol y un intervalo.
 * Busca si dentro del arbol hay por lo menos un intervalo que interseque con
 * el intervalo parametro. En caso de ser asi devuelve un subarbol cuyo primer
 * nodo interseca con el intervalo parametro. En caso contrario devuelve NULL.
 */
ITree itree_intersecar (ITree, IntervaloE);

/**
 * Toma un arbol una funcion visitante.
 * Recorre el arbol en su ancho y aplica la funcion visitante a cada nodo
 * del arbol.
 */
void itree_recorrer_bfs (ITree arbol, FuncionQueVisita visit);

/**
 * Toma un arbol una funcion visitante.
 * Recorre el arbol en profundidad y aplica la funcion visitante a cada nodo
 * del arbol.
 */
void itree_recorrer_dfs (ITree arbol, FuncionQueVisita visit);

/**
 * Toma un arbol una funcion visitante.
 * Recorre el arbol en profundidad y aplica la funcion visitante a cada nodo
 * del arbol.
 */
void itree_recorrer_dfs_agg (ITree arbol, FuncionAplicar visit, ITree *arbolU);

ITree itree_copiar (ITree arbol);

/**
 * Definimos estas 2 funciones para imprimir el arbol de una forma legible
 * dentro de la consola de comandos.
 * COUNT es la constante que marca la cantidad de espacios que hay entre cada
 * nodo y sus hijos.
 */
#define COUNT 10

void print2D(ITree arbol);

void print2DUtil(ITree arbol, int space);

/**
 * Toma un arbol y libera todos sus nodos.
 */
void itree_destruir (ITree raiz);

#endif
