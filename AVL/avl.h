#ifndef __AVL_H__
#define __AVL_H__

#include "../Arboles/ITree1.h"

/**
 * Macros utiles.
 */
#define max2(x, y) (((x) > (y)) ? (x) : (y))

/**
 *  Declaro el conjunto de esta manera para que sea facil reconocer la diferencia
 *  entre un conjunto vacio y un conjunto no encontrado en la tabla hash.
 */
typedef struct Contenedor {
  ITree conjunto;
} *Contenedor;

/**
 * Estructura que representa cada nodo (o subarbol) de un arbol avl de conjuntos.
 * Cada nodo tiene:
 *  - una clave
 *  - un conjunto
 *  - un int que representa la altura de ese arbol.
 *  - 2 apuntadores a 2 nodos que representan los hijos del subarbol actual
 */
typedef struct _AVLClavesNodo {
  char* clave;
  ITree conjunto;
  int altura;
  struct _AVLClavesNodo *left;
  struct _AVLClavesNodo *right;
} AVLClavesNodo;

/**
 * Estructura de AVLClavesTree.
 * El AVLClavesTree es un tipo de AVLTree que con claves y conjuntos.
 * La idea de su implementacion es acelerar la busqueda ante la presencia
 * de colisiones. Puesto que a diferencia de la lista, la velocidad de busqueda
 * aqui seria de log(n).
 */
typedef AVLClavesNodo *AVLClavesTree;

/* -------------------------------- BASICAS ----------------------------------*/
/**
 * Devuelve lo que se determina como un arbol vacio.
 */
AVLClavesTree avlClavesTree_crear ();

/**
*  Toma un arbol y devuelve 1 si es vacio y 0 en caso contrario.
*/
int avlClavesTree_es_vacio (AVLClavesTree);

/**
 * Dado un arbol.
 * Devuelve la altura del mismo.
 * Aunque en la declaracion del tipo de dato de arboles se agrego un campo
 * que guarda la altura del arbol, se decide hacer esta funcion puesto que
 * como se considera al arbol vacio como NULL, este no tiene campo altura.
 */
int avlClavesTree_altura (AVLClavesTree arbol);

/**
 * Dado un arbol.
 * Devuelve el factor de balance de un arbol.
 * Definido como la altura del subarbol izquierdo menos la del subarbol derecho.
 */
int avlClavesTree_factor_balance (AVLClavesTree arbol);

/**
 * Toma un apuntador a un arbol.
 * Calcula la altura de ese subarbol y lo guarda en el parametro
 * altura del nodo raiz del subarbol que se tomo como parametro.
 */
void avlClavesTree_actualizar_altura (AVLClavesTree *arbol);

/**
 * Toma un arbol de claves y libera todos sus nodos y sus contenidos.
 */
void avlClavesTree_destruir (AVLClavesTree arbolClaves);

/* ------------------------------ BALANCEO -----------------------------------*/

/**
 * Dado un arbol, obtiene su factor de balance y de ser nesecario lo balancea
 * aplicando las rotaciones correspondientes y actualizando su campo de altura.
 * Devuelve el arbol rotado.
 */
AVLClavesTree avlClavesTree_balancear (AVLClavesTree arbol);

/**
 * Dado un arbol, realiza una rotacion simple a derecha. Ademas se actualiza
 * el campo de altura de forma que el arbol resultante sea correcto.
 * Devuelve el arbol luego de la rotacion.
 */
AVLClavesTree avlClavesTree_rotacion_der (AVLClavesTree arbol);

/**
 * Dado un arbol, realiza una rotacion simple a izquierda. Ademas se actualiza
 * el campo de altura de forma que el arbol resultante sea correcto.
 * Devuelve el arbol luego de la rotacion.
 */
AVLClavesTree avlClavesTree_rotacion_izq (AVLClavesTree arbol);


/* ----------------------------- FUNDAMENTALES -------------------------------*/
/**
 * Dadas dos cadenas.
 * Devuelve strcmp (clave1, clave2);
 */
int comparar_claves (char *clave1, char *clave2);

/**
 *  Toma un arbol, un conjunto y una clave.
 *  Inserta el conjunto en el arbol teniendo en cuenta con la clave
 *  las propiedades del arbol AVL.
 *  Luego chequea si cada subarbol que se cambio cuando se ingreso el nodo
 *  quedo desbalanceado. En ese caso lo balancea aplicando las rotaciones
 *  correspondientes.
 *  Si se encuentra con que ya existe un conjunto con la clave ingresada, se
 *  pisa el valor anterior.
 */
void avlClavesTree_insertar (AVLClavesTree *arbolClaves, ITree conjunto,
                             char* clave);

/**
 * Toma un arbol y una clave.
 * Busca por el arbol el nodo que tenga clave coincidente.
 * Si lo encuentra, devuelve un 'contenedor' con el conjunto. De esta forma se
 * logra diferenciar el caso en el que el cojunto sea vacio y en el no exista
 * ningun conjunto con la clave pasada como argumento asociada.
 */
Contenedor avlClavesTree_buscar (AVLClavesTree arbol, char* clave);


#endif
