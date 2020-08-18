/**
 * Los arboles de este archivo, son arboles de intervalos disjuntos, y cada uno
 * representa un conjunto numerico.
 */

#ifndef __ITree_H__
#define __ITree_H__
#include "../Intervalos/intervaloE.h"

/**
 * Estructura que representa cada nodo (o subarbol) de un arbol de intervalos.
 * Cada nodo tiene:
 *  - un intervalo.
 *  - un int que representa la altura de ese arbol.
 *  - 2 apuntadores a 2 nodos que representan los hijos del subarbol actual
 */

typedef struct _ITreeNodo {
  IntervaloE intervalo;
  int altura;
  struct _ITreeNodo *left;
  struct _ITreeNodo *right;
} ITreeNodo;

/**
 * Estructura de ITree.
 * El ITree (o arbol de intervalos) es un tipo de AVLTree que trabaja
 * especificamente con intervalos disjuntos.
 */
typedef ITreeNodo *ITree;

/**
 * Funciones utiles.
 */
typedef void (*FuncionAux) (ITree arbbl2, IntervaloE intervalo, ITree *destino);
typedef void (*FuncionImpresion) (ITree arbol);


/* -------------------------------- BASICAS ----------------------------------*/
/**
 * Devuelve lo que se determina como un arbol vacio.
 */
ITree itree_crear ();

/**
 *  Toma un arbol y devuelve 1 si es vacio y 0 en caso contrario.
 */
int itree_es_vacio (ITree);

/**
 * Dado un arbol.
 * Devuelve la altura del mismo.
 * Aunque en la declaracion del tipo de dato de arboles se agrego un campo
 * que guarda la altura del arbol, se decide hacer esta funcion puesto que
 * como se considera al arbol vacio como NULL, este no tiene campo altura.
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
 * Dado un arbol,
 * utilizando la funcion itree_imprimir_util, lo imprime inorder.
 */
void itree_imprimir (ITree arbol);

/**
 * Funcion auxiliar empleada para imprimir un arbol en inorder.
 * Toma un arbol y un doble puntero a intervalos.
 * Este ultimo funciona como un contenedor de *IntervaloE de esta forma,
 * se puede pasar en la primer recursion como NULL y que luego se vaya
 * modificando.
 * El objetivo de esta forma de hacerlo fue que este imprimiendo siempre el
 * "nodo anterior" de esta forma, al finalizar la funcion se tiene una
 * referencia al ultimo intervalo y se puede imprimir con un formato diferente.
 */
void itree_imprimir_util (ITree arbol, IntervaloE **ant);

/**
 * Toma un arbol y libera todos sus nodos.
 */
void itree_destruir (ITree raiz);

/* ------------------------------ BALANCEO -----------------------------------*/

/**
 * Dado un arbol, obtiene su factor de balance y de ser nesecario lo balancea
 * aplicando las rotaciones correspondientes y actualizando su campo de altura.
 * Devuelve el arbol rotado.
 */
ITree itree_balancear (ITree arbol);

/**
 * Dado un arbol, realiza una rotacion simple a derecha. Ademas se actualiza
 * el campo de altura de forma que el arbol resultante sea correcto.
 * Devuelve el arbol luego de la rotacion.
 */
ITree itree_rotacion_der (ITree arbol);

/**
 * Dado un arbol, realiza una rotacion simple a izquierda. Ademas se actualiza
 * el campo de altura de forma que el arbol resultante sea correcto.
 * Devuelve el arbol luego de la rotacion.
 */
ITree itree_rotacion_izq (ITree arbol);

/* ----------------------------- FUNDAMENTALES -------------------------------*/

/**
 * Copia de arobl.
 */
ITree itree_copiar (ITree arbol);

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
 *  Toma un arbol y un intervalo.
 *  Busca si dentro del arbol hay por lo menos un intervalo que interseque con
 *  el intervalo parametro. En caso de ser asi devuelve un subarbol cuyo primer
 *  nodo interseca con el intervalo parametro. En caso contrario devuelve NULL.
 */
ITree itree_intersecar (ITree, IntervaloE);

/* ----------------------------- CONJUNTOS -----------------------------------*/

/**
 * Funcion auxiliar que se utiliza para las funciones de conjuntos 'resta' e
 * 'interseccion'.
 * Se toman dos arboles considerados origen1 y origen2.
 * Una funcion auxiliar que tomara el ARBOL origen2 y lo recorrera realizando
 * comparaciones con un INTERVALO y almacenando los resultados en el ARBOL
 * destino.
 * Y un arbol destino que sera el que almacene el resultado final.
 *
 * La funcion recoore el arbol origen1 y aplica la funcion auxiliar con cada
 * intervalo de este, al arbol origen2, y almacenando los resultados en el
 * arbol destino.
 */
void itree_dfs_origen_destino (ITree origen1, ITree origen2, FuncionAux aux,
                               ITree *destino);

/**
 *  Toma dos arboles.
 *  Se identifica cual es el arbol mas alto y se copia.
 *  Luego se recorre el arbol mas pequeño y se va insertando los intervalos
 *  de a uno en la copia realizada anteriormente.
 */
ITree itree_unir (ITree arbol1, ITree arbol2);

/**
 * Toma un arbol origen, y un arbol resultado.
 * Recorre el arbol origen, insertando cada nodo en el arbol resultado.
 */
void itree_dfs_union (ITree arbol, ITree *arbolU);

/**
 *  Dados dos arboles.
 *  Devuelve un nuevo arbol con la interseccion de estos.
 */
ITree itree_interseccion (ITree arbol1, ITree arbol2);


/**
 *  Toma un arbol a intersecar, un intervalo y un arbol resultado.
 *  Interseca el intervalo con el arbol "arbolAInt" completo, insertando cada
 *  nodo interseccion en el arbol resultado.
 *  De esta manera el arbol resultado termina siendo un acumulador de las
 *  intersecciones entre arbolAInt y el intervalo.
 *  Si esta funcion se utiliza con todos los intervalos de otro arbol, se
 *  obtiene la interseccion entre los arboles.
 */
void itree_intersecarV (ITree arbolAInt, IntervaloE intervalo, ITree *arbolRes);

/**
 *  Toma un conjunto y calcula su complemento.
 *  Considera los casos especiales de si el conjunto es vacio, o es el universo
 *  y de ser los dos casos falsos, llama a la funcion auxiliar
 *  itree_complemento_aux.
 */
ITree itree_complemento (ITree origen);

/**
 * Funcion auxiliar empleada para calcular el complemento de un arbol que es
 * no vacio ni el universo.
 * La idea del funcionamiento es que siempre se este tratando de insertar el
 * intervalo correspondiente al nodo anterior del arbol. Se puede decir que
 * el arbol va recorriendo y arrastrando el nodo anterior a su paso para asi
 * calcular cada intervalo en el momento necesario.
 * Ademas cuando se finalize la funcion, en el ambito donde esta fue llamada
 * se dispondra del ultimo intervalo del arbol para realizar la operacion
 * necesaria.
 */
void itree_complemento_aux (ITree origen, ITree *nuevoArbol, IntervaloE *ant);

/**
 * Toma dos arboles, arbol1 y arbol2.
 * Devuelve el resultado de hacer arbol1 - arbol2, es decir, un nuevo arbol con
 * los elementos de arbol1 que no estan en arbol2.
 * Basicamente, recorro el arbol1 completo y guardo solamente los nodos que
 * no tienen interseccion con el arbol2.
 * Si un nodo de arbol1, tiene interseccion con otro de arbol2, no necesariamente
 * siginfiica que ya hay que descartarlo, puede ser que esta interseccion no sea
 * completa, mas bien parcial, por lo tanto hay que actualizar el intervalo con
 * el que se recorre en ese momento.
 */
ITree itree_resta (ITree arbol1, ITree arbol2);

/**
 *  Dados dos arboles ni vacios ni que representen el conjunto universal.
 *  Se va recorriendo el arbol 1, buscando intersecciones en el arbol2 de forma
 *  tal que los intervalos contenidos en el arbol1, que no intersequen con
 *  ninguno del arbol2, seran añadidos al arbol destino.
 */
void itree_resta_aux (ITree arbol1, IntervaloE intervalo, ITree *destino);

/* ----------------------------- AUXILIARES ----------------------------------*/

/**
 * Definimos estas 2 funciones para imprimir el arbol de una forma legible
 * dentro de la consola de comandos.
 * COUNT es la constante que marca la cantidad de espacios que hay entre cada
 * nodo y sus hijos.
 */
#define COUNT 10

void print2D(ITree arbol);

void print2DUtil(ITree arbol, int space);



#endif
