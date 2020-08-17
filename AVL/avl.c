//
// Created by scalbi on 16/8/20.
//

#include "avl.h"
#include <stdlib.h>
#include <string.h>

/* -------------------------------- BASICAS ----------------------------------*/
AVLClavesTree avlClavesTree_crear (){
  return NULL;
}

int avlClavesTree_es_vacio (AVLClavesTree arbol){
  return arbol == NULL;
}

int avlClavesTree_altura (AVLClavesTree arbol){
  // Se define la altura de un arbol vacio como -1.
  int altura = -1;

  if(!avlClavesTree_es_vacio(arbol))
    altura = arbol->altura;

  return altura;
}

int avlClavesTree_factor_balance (AVLClavesTree arbol){
  int factorBalance = 0;
  if (!avlClavesTree_es_vacio (arbol))
    factorBalance = avlClavesTree_altura (arbol->left) -
                    avlClavesTree_altura (arbol->right);
  return factorBalance;
}

void avlClavesTree_actualizar_altura (AVLClavesTree *arbol){
  // La altura del nodo actual va a ser el maximo entre la altura de los hijos
  // mas 1.
  (*arbol)->altura = max2 (avlClavesTree_altura ((*arbol)->left),
                           avlClavesTree_altura ((*arbol)->right)) + 1;
}

void avlClavesTree_destruir (AVLClavesTree arbolClaves){
  // Si hay algo para destruir, se destruye.
  if (!avlClavesTree_es_vacio(arbolClaves)){
    // Se destruyen los dos hijos del arbol.
    avlClavesTree_destruir (arbolClaves->left);
    avlClavesTree_destruir (arbolClaves->right);
    // Liberamos el nodo actual.
    itree_destruir (arbolClaves->conjunto);
    free (arbolClaves->clave);
    free (arbolClaves);
  }
}

/* ------------------------------ BALANCEO -----------------------------------*/

AVLClavesTree avlClavesTree_rotacion_der (AVLClavesTree arbol){
  // arbol: A.
  // nodoRelevante: B.
  AVLClavesTree nodoRelevante = arbol->left;
  // Se cambia el hijo izquierdo de A a el hijo derecho de B.
  arbol->left = nodoRelevante->right;
  // Es necesario actualizar el valor de altura de A puesto que
  // cambio el hijo izquierdo de A y no sabemos si se sigue manteniendo.
  avlClavesTree_actualizar_altura (&arbol);

  // Se cambia el hijo derecho de B a A.
  nodoRelevante->right = arbol;
  // Es necesario actualizar el valor de altura de B por motivos analogos
  avlClavesTree_actualizar_altura (&nodoRelevante);

  return nodoRelevante;
}

AVLClavesTree avlClavesTree_rotacion_izq (AVLClavesTree arbol){
  // arbol: A.
  // nodoRelevante: B.
  AVLClavesTree nodoRelevante = arbol->right;
  // Se cambia el hijo derecho de A a el hijo izquierdo de B.
  arbol->right = nodoRelevante->left;
  // Es necesario actualizar el valores de altura de A puesto que
  // cambio el hijo derecho de A y no sabemos si se sigue manteniendo.
  avlClavesTree_actualizar_altura (&arbol);

  // Se cambia el hijo izquierdo de B a A.
  nodoRelevante->left = arbol;
  // Es necesario actualizar el valor de altura de B por
  // motivos analogos.
  avlClavesTree_actualizar_altura (&nodoRelevante);

  return nodoRelevante;
}

AVLClavesTree avlClavesTree_balancear (AVLClavesTree arbol){
  // Si se le pasa un arbol vacio, itree_factor_balance devolveria 0 y no
  // entraria a ninguna otra funcion.
  int factorBalance = avlClavesTree_factor_balance (arbol);

  // Si la altura del subarbol izquierdo es mayor...
  if (factorBalance > 1){
    // En el caso de balance tras insercion, nunca va a ser igual a 0, pues
    // justamente por algo esta desbalanceado.
    // Ahora bien, cuando estamos balanceando tras eliminacion, puede ser que
    // sea 0, y en ese caso daria lo mismo, por lo que optamos por hacer
    // solo una rotacion simple.
    if (avlClavesTree_factor_balance (arbol->left) >= 0)
      // Se tiene un caso de izquierda-izquierda, que requiere una rotacion der.
      arbol = avlClavesTree_rotacion_der (arbol);
      // Si la altura del subarbol derecho del subarbol izquierdo es mayor.
    else {
      // se tiene un caso de izquierda-derecha, que requiere una rotacion doble.
      arbol->left = avlClavesTree_rotacion_izq (arbol->left);
      arbol = avlClavesTree_rotacion_der (arbol);
    }
  }
  else if (factorBalance < -1){
    // En el caso de balance tras insercion, nunca va a ser igual a 0, pues
    // justamente por algo esta desbalanceado.
    // Ahora bien, cuando estamos balanceando tras eliminacion, puede ser que
    // sea 0, y en ese caso daria lo mismo, por lo que optamos por hacer
    // solo una rotacion simple.
    if (avlClavesTree_factor_balance (arbol->right) <= 0){
      // Se tiene un caso de derecha-derecha, que requiere una rotacion izq.
      arbol = avlClavesTree_rotacion_izq (arbol);
    }
    else {
      // se tiene un caso de derecha-izquierda, que requiere una rotacion doble.
      arbol->right = avlClavesTree_rotacion_der (arbol->right);
      arbol = avlClavesTree_rotacion_izq (arbol);
    }
  }

  return arbol;
}

/* ----------------------------- FUNDAMENTALES -------------------------------*/

int comparar_claves (char *clave1, char *clave2){
  return strcmp (clave1, clave2);
}

void avlClavesTree_insertar (AVLClavesTree *arbolClaves, ITree conjunto,
                             char* clave){
  // Si se quiere insertar sobre un arbol que es vacio entonces se genera un
  // nuevo subarbol y se asigna al arbol actual.
  if (avlClavesTree_es_vacio (*arbolClaves)){
    AVLClavesTree nuevoSubarbol = malloc (sizeof (AVLClavesNodo));
    nuevoSubarbol->conjunto = conjunto;
    char *claveFinal = malloc (sizeof (char) * strlen(clave) + 1);
    strcpy (claveFinal, clave);
    nuevoSubarbol->clave = claveFinal;
    nuevoSubarbol->altura = 0; // La altura de un arbol con un solo nodo es 0.
    nuevoSubarbol->left = avlClavesTree_crear();
    nuevoSubarbol->right = avlClavesTree_crear ();
    *arbolClaves = nuevoSubarbol;
  }
  else {
    // Sabiendo que el arbol no es vacio, se compara la clave con la que se
    // se quiere insertar con la clave del arbol actual.

    int comparacion = comparar_claves (clave, (*arbolClaves)->clave);

    // Si ambos claves son iguales significa que ya existe un conjunto con
    // ese nombre en el arbol, y se desea pisarlo.
    if (comparacion == 0){
      (*arbolClaves)->conjunto = conjunto;
    }
    else {
      // Se realiza la recursion sobre el hijo izquierdo o el derecho segun
      // el valor que devolvio la funcion de comparacion.
      if (comparacion > 0)
        avlClavesTree_insertar ((&(*arbolClaves)->right), conjunto, clave);
      else if (comparacion < 0)
        avlClavesTree_insertar ((&(*arbolClaves)->left), conjunto, clave);

      // Luego de insertar el conjunto, se actualiza la altura del nodo.
      avlClavesTree_actualizar_altura (arbolClaves);

      // Por ultimo se balancea el arbol.
      *arbolClaves = avlClavesTree_balancear (*arbolClaves);
    }
  }
}

Contenedor avlClavesTree_buscar (AVLClavesTree arbolClaves, char* clave){
  Contenedor resultado = NULL;
  // Si el arbol es vacio, no hay interseccion con la clave parametro y se
  // devuelve un arbol vacio.
  if (!avlClavesTree_es_vacio (arbolClaves)){
    int comparacion = comparar_claves (clave, arbolClaves->clave);

    // Si el arbol sobre el que se esta parado tiene el conjunto con la clave
    // que se busca.
    if (comparacion == 0){
      resultado = malloc (sizeof (struct Contenedor));
      resultado->conjunto = arbolClaves->conjunto;
    }

    else if (comparacion > 0)
      resultado = avlClavesTree_buscar (arbolClaves->right, clave);
    else if (comparacion < 0)
      resultado = avlClavesTree_buscar (arbolClaves->left, clave);
  }
  return resultado;
}