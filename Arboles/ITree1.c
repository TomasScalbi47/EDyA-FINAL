#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ITree1.h"
#include "Cola/cola.h"
#include "Pila/pila.h"


/* ------------------- BASICAS ----------------------------*/
ITree itree_crear (){
  return NULL;
}

int itree_es_vacio (ITree arbol){
  return arbol == NULL;
}

int itree_altura(ITree arbol){
  // Se define la altura de un arbol vacio como -1.
  int altura = -1;

  if(!itree_es_vacio(arbol))
    altura = arbol->altura;

  return altura;
}

int itree_factor_balance (ITree arbol){
  int factorBalance = 0;
  if (!itree_es_vacio(arbol))
   factorBalance = itree_altura(arbol->left) - itree_altura(arbol->right);
  return factorBalance;
}

void itree_actualizar_altura (ITree *arbol){
  // La altura del nodo actual va a ser el maximo entre la altura de los hijos
  // mas 1.
  (*arbol)->altura = max2 (itree_altura((*arbol)->left),
    itree_altura((*arbol)->right)) + 1;
}

void itree_mayor_extDer (ITree *arbol){
  // Siempre que el arbol no sea vacio...
  if(!itree_es_vacio(*arbol)){
    double maxExtDer = (*arbol)->intervalo.extDer;

    // Si el hijo izquiedo es no vacio, se actualiza el maxExtDer contra este.
    if (!itree_es_vacio((*arbol)->left))
      maxExtDer = max2 (maxExtDer, (*arbol)->left->maxExtDer);

    // Si el hijo derecho es no vacio, se actualiza el maxExtDer contra este.
    if (!itree_es_vacio((*arbol)->right))
      maxExtDer = max2 (maxExtDer, (*arbol)->right->maxExtDer);

    // Una vez que se obtuvo el valor de maxExtDer, se le asigna al arbol actual.
    (*arbol)->maxExtDer = maxExtDer;
  }
}

/* ------------------- BALANCEO ----------------------------*/

ITree itree_balancear (ITree arbol){
  // Si se le pasa un arbol vacio, itree_factor_balance devolveria 0 y no
  // entraria a ninguna otra funcion.
  int factorBalance = itree_factor_balance (arbol);

  // Si la altura del subarbol izquierdo es mayor...
  if (factorBalance > 1){
    // En el caso de balance tras insercion, nunca va a ser igual a 0, pues
    // justamente por algo esta desbalanceado.
    // Ahora bien, cuando estamos balanceando tras eliminacion, puede ser que
    // sea 0, y en ese caso daria lo mismo, por lo que optamos por hacer
    // solo una rotacion simple.
    if (itree_factor_balance (arbol->left) >= 0)
      // Se tiene un caso de izquierda-izquierda, que requiere una rotacion der.
      arbol = itree_rotacion_der (arbol);
    // Si la altura del subarbol derecho del subarbol izquierdo es mayor.
    else {
      // se tiene un caso de izquierda-derecha, que requiere una rotacion doble.
      arbol->left = itree_rotacion_izq (arbol->left);
      arbol = itree_rotacion_der (arbol);
    }
  }
  else if (factorBalance < -1){
    // En el caso de balance tras insercion, nunca va a ser igual a 0, pues
    // justamente por algo esta desbalanceado.
    // Ahora bien, cuando estamos balanceando tras eliminacion, puede ser que
    // sea 0, y en ese caso daria lo mismo, por lo que optamos por hacer
    // solo una rotacion simple.
    if (itree_factor_balance (arbol->right) <= 0){
      // Se tiene un caso de derecha-derecha, que requiere una rotacion izq.
      arbol = itree_rotacion_izq (arbol);
    }
    else {
      // se tiene un caso de derecha-izquierda, que requiere una rotacion doble.
      arbol->right = itree_rotacion_der (arbol->right);
      arbol = itree_rotacion_izq (arbol);
    }
  }

  return arbol;
}

ITree itree_rotacion_der (ITree arbol){
  // arbol: A.
  // nodoRelevante: B.
  ITree nodoRelevante = arbol->left;
  // Se cambia el hijo izquierdo de A a el hijo derecho de B.
  arbol->left = nodoRelevante->right;
  // Es necesario actualizar los valores de altura y maxExtDer de A puesto que
  // cambio el hijo izquierdo de A y no sabemos si se siguen manteniendo.
  itree_actualizar_altura(&arbol);
  itree_mayor_extDer (&arbol);
  // Se cambia el hijo derecho de B a A.
  nodoRelevante->right = arbol;
  // Es necesario actualizar los valores de altura y maxExtDer de B por
  // motivos analogos
  itree_actualizar_altura(&nodoRelevante);
  itree_mayor_extDer (&nodoRelevante);

  return nodoRelevante;
}

ITree itree_rotacion_izq (ITree arbol){
  // arbol: A.
  // nodoRelevante: B.
  ITree nodoRelevante = arbol->right;
  // Se cambia el hijo derecho de A a el hijo izquierdo de B.
  arbol->right = nodoRelevante->left;
  // Es necesario actualizar los valores de altura y maxExtDer de A puesto que
  // cambio el hijo derecho de A y no sabemos si se siguen manteniendo.
  itree_actualizar_altura(&arbol);
  itree_mayor_extDer (&arbol);
  // Se cambia el hijo izquierdo de B a A.
  nodoRelevante->left = arbol;
  // Es necesario actualizar los valores de altura y maxExtDer de B por
  // motivos analogos.
  itree_actualizar_altura(&nodoRelevante);
  itree_mayor_extDer (&nodoRelevante);

  return nodoRelevante;
}

/* ------------------- FUNDAMENTALES ----------------------------*/

ITree itree_copiar (ITree arbol){
  // Si el arbol es vacio...
  if (arbol == NULL)
    return NULL;
  // El arbol a copiar es no vacio.
  ITree nuevoArbol = malloc (sizeof (ITreeNodo));
  nuevoArbol->intervalo = arbol->intervalo;
  nuevoArbol->altura = arbol->altura;
  nuevoArbol->maxExtDer = arbol->maxExtDer;

  if (arbol->left != NULL)
    nuevoArbol->left = itree_copiar (arbol->left);
  else
    nuevoArbol->left = NULL;

  if (arbol->right != NULL)
   nuevoArbol->right = itree_copiar (arbol->right);
  else
    nuevoArbol->right = NULL;

  return nuevoArbol;
}

void itree_insertar (ITree *arbol, IntervaloE nIntervalo){
  // Si se quiere insertar sobre un arbol vacio, entonces no hay que hacer nada.
  if (!itree_es_vacio(*arbol)){
    // Sabiendo que el arbol es no vacio, para mantener la propiedad de arbol
    // de intervalos disjuntos es necesario eliminar las colisiones del
    // intervalo a insertar en el arbol. Al mismo tiempo se debera actualizar
    // una variable que contenga la union de todos estos que se agregara al
    // finalizar.

    // intervaloExp sera la version expandida de nIntervalo.
    IntervaloE intervaloExp;
    intervaloExp = intervaloE_expandir (nIntervalo);

    ITree interseccion = NULL;
    interseccion = itree_intersecar (*arbol, intervaloExp);

    // Si hubo interseccion.
    while (interseccion != NULL) {
      // Unir intervalo que colisiona con el intervalo a ingresar.
      nIntervalo = intervaloE_unir (nIntervalo, interseccion->intervalo);
      // Eliminar nodo que colisiona con el intervalo a ingresar.
      itree_eliminar_dato (arbol, interseccion->intervalo);

      // Volver a intersecar el arbol con la expansion del nuevo intervalo que
      // acumula las uniones.
      intervaloExp = intervaloE_expandir (nIntervalo);
      interseccion = itree_intersecar (*arbol, intervaloExp);
    }
  }
  itree_insercion (arbol, nIntervalo);
}

void itree_insercion (ITree *arbol, IntervaloE nIntervalo){
  // Si se quiere insertar sobre un arbol que es vacio entonces se genera un
  // nuevo subarbol y se asigna al arbol actual.
  if (itree_es_vacio(*arbol)){
    ITree nuevoSubarbol = malloc (sizeof (ITreeNodo));
    nuevoSubarbol->intervalo = nIntervalo;
    nuevoSubarbol->maxExtDer = nIntervalo.extDer;
    nuevoSubarbol->altura = 0; // La altura de un arbol con un solo nodo es 0.
    nuevoSubarbol->left = itree_crear ();
    nuevoSubarbol->right = itree_crear ();
    *arbol = nuevoSubarbol;
  }
  else {
    // Sabiendo que el arbol no es vacio, se compara el intervalo que se quiere
    // insertar con el intervalo contenido en el nodo actual para saber si
    // hay que hacer la recursion sobre el hijo izquierdo o el derecho.

    int comparacion = intervaloE_comparacion (nIntervalo, (*arbol)->intervalo);

    // Si ambos intervalos son iguales significa que el intervalo que se quiere
    // ingresar ya se encuentra en el arbol y no hay que realizar mas acciones.
    if (comparacion != 0){
      // Se realiza la recursion sobre el hijo izquierdo o el derecho segun
      // el valor que devolvio la funcion de comparacion.
      if (comparacion > 0){
        itree_insercion ((&(*arbol)->right), nIntervalo);
      }
      else if (comparacion < 0){
        itree_insercion ((&(*arbol)->left), nIntervalo);
      }

      // Luego de insertar el intervalo, se actualizan los valores de maxExtDer
      // y de altura del nodo.
      itree_mayor_extDer (arbol);
      itree_actualizar_altura(arbol);

      // Por ultimo se balancea el arbol.
      *arbol = itree_balancear (*arbol);
    }
  }
}

void itree_eliminar_dato (ITree *arbol, IntervaloE datoQueEliminar){
  // Si se quiere eliminar un intervalo de un arbol vacio no se realizan mas
  // acciones.
  if (!itree_es_vacio(*arbol)){

    int comparacion = intervaloE_comparacion (datoQueEliminar,
      (*arbol)->intervalo);

    // Si la funcion de comparacion devuelve 0 es porque el intervalo que se
    // busca esta en este nodo.
    if (comparacion == 0){
      // Creamos un arbol auxiliar para liberar el nodo que vamos a eliminar
      // una vez que ya no este en el arbol.
      ITree nodoLiberar = itree_crear();

      // Si el nodo actual es una hoja, se libera y se le asigna el valor
      // de un arbol vacio.
      if (itree_es_vacio((*arbol)->left) && itree_es_vacio((*arbol)->right)){
        free((*arbol));
        *arbol = itree_crear();
      }
      // Sabiendo que al menos uno de los hijos no es un arbol vacio,
      // se procede a analizar los casos restantes.

      // Si el hijo izquierdo es vacio, cambiamos el valor del nodo por el
      // hijo derecho y liberamos el nodo eliminado.
      else if (itree_es_vacio((*arbol)->left)){
        nodoLiberar = *arbol;
        *arbol = (*arbol)->right;
        free(nodoLiberar);
        nodoLiberar = itree_crear();
      }

      // Si el hijo derecho es vacio, cambiamos el valor del nodo por el
      // hijo izquierdo y liberamos el nodo eliminado.
      else if (itree_es_vacio((*arbol)->right)){
        nodoLiberar = *arbol;
        *arbol = (*arbol)->left;
        free(nodoLiberar);
        nodoLiberar = itree_crear();
      }

      // Si ninguno de los hijos es nulo, se elimina el minimo valor del hijo
      // derecho y se asigna el intervalo que se encontraba en el nodo
      // eliminado al nodo actual.
      else
        (*arbol)->intervalo = itree_eliminar_minimo(&((*arbol)->right));
    }

    // Si la funcion de comparacion no devuelve 0 es porque hay que seguir
    // buscando en el arbol el nodo a eliminar.
    else{

      // Si la funcion de comparacion devuelve menor a 0 es porque el intervalo
      // a eliminar es menor que el intervalo del nodo actual. Asi que se
      // realiza la recursion sobre el hijo izquierdo.
      if (comparacion < 0)
        itree_eliminar_dato (&((*arbol)->left), datoQueEliminar);

      // En caso contrario, el intervalo a eliminar es mayor que el intervalo
      // del nodo actual. Asi que se realiza la recursion sobre el hijo
      // derecho.
      else
        itree_eliminar_dato (&((*arbol)->right), datoQueEliminar);

      // Luego de eliminar el nodo, se actualizan los valores de maxExtDer
      // y de altura del nodo.
      itree_mayor_extDer (arbol);
      itree_actualizar_altura(arbol);

      // Por ultimo se balancea el arbol.
      *arbol = itree_balancear (*arbol);
    }
  }
}

IntervaloE itree_eliminar_minimo (ITree *arbol){
  // Por el contexto en el que se llama a la funcion el arbol nunca puede
  // ser nulo.

  IntervaloE minimo;

  // Si el hijo izquierdo del nodo es nulo, entonces este es el nodo que
  // contiene al minimo intervalo del arbol.
  if (itree_es_vacio((*arbol)->left)){
    // Guardamos el intervalo del nodo actual para devolverlo.
    minimo = (*arbol)->intervalo;
    // Eliminamos este nodo del arbol actual.
    itree_eliminar_dato(arbol, minimo);
  }
  else{
    // En caso de no estar en el nodo con el minimo intervalo aun, se sigue
    // recorriendo el arbol hacia la izquierda hasta encontrarlo.
    minimo = itree_eliminar_minimo(&((*arbol)->left));

    // Luego de eliminar el nodo, se actualizan los valores de maxExtDer
    // y de altura del nodo.
    itree_mayor_extDer (arbol);
    itree_actualizar_altura(arbol);
  }
  return minimo;
}

ITree itree_intersecar (ITree arbol, IntervaloE intervalo){
  ITree resultado = itree_crear();
  // Si el arbol es vacio no hay interseccion con el intervalo parametro
  // y se devuelve un arbol vacio.
  if (!itree_es_vacio(arbol)){
    int interseccion = intervaloE_interseccion(arbol->intervalo, intervalo);

    if (interseccion)
      resultado = arbol;
      // Si el extremo izquierdo de intervalo, es menor que el extremo izquierdo
      // del intervalo con el que se quizo intersecar. Entonces puede haber
      // mas intersecciones a la izquierda.
    else if (intervalo.extIzq < arbol->intervalo.extIzq)
      itree_intersecar(arbol->left, intervalo);

      // Si el extremo derecho de intervalo, es mayor que el extremo derecho
      // del intervalo con el que se quizo intersecar. Entonces puede haber
      // mas intersecciones a la derecha.
    else if(intervalo.extDer > arbol->intervalo.extDer)
      itree_intersecar (arbol->right, intervalo);
  }
  return resultado;
}

/* ------------------- CONJUNTOS ----------------------------*/

ITree itree_unir (ITree arbol1, ITree arbol2){
  ITree nuevoArbol = NULL;
  // nuevoArobl es el duplicado del arbol con mas altura.
  if (itree_es_vacio (arbol1))
    nuevoArbol = itree_copiar (arbol2);
  else if (itree_es_vacio (arbol2))
    nuevoArbol = itree_copiar (arbol1);
    // Ninguno de los dos arboles a unir es vacio..
  else if (arbol1->altura >= arbol2->altura){
    nuevoArbol = itree_copiar (arbol1);
    itree_recorrer_dfs_union (arbol2, itree_insertar, &nuevoArbol);
  }
  else {
    nuevoArbol = itree_copiar (arbol2);
    itree_recorrer_dfs_union (arbol1, itree_insertar, &nuevoArbol);
  }

  return nuevoArbol;
}

void itree_recorrer_dfs_union (ITree origen, FuncionAplicar visit, ITree *arbolU){
  // Si el arbol es vacio no hay nada que recorrer.
  if (!itree_es_vacio(origen)){
    // Se crea la pila.
    Pila stack = pila_crear ();
    // Se apila el nodo raiz.
    pila_apilar (&stack, origen);
    // Nodo auxiliar que se va a usar para moverse por el arbol origen.
    ITree nodo;

    // Minetras queden elementos en la pila...
    while (!pila_es_vacia (stack)){
      // Se guarda el primer elemento de la pila.
      nodo = pila_ultimo (stack);
      // Se desapila ese elemento.
      pila_desapilar (&stack);
      // Se aplica la funcion visitante al nodo actual.
      visit (arbolU, nodo->intervalo);
      // Se apilan los hijos del nodo actual mientras no sean vacios.
      if (!itree_es_vacio(nodo->right))
        pila_apilar (&stack, nodo->right);
      if (!itree_es_vacio(nodo->left))
        pila_apilar (&stack, nodo->left);
    }
  }
}

ITree itree_interseccion (ITree arbol1, ITree arbol2){
  ITree arbolNuevo = itree_crear ();
  // Si alguno de los 2 arboles es vacio entonces ya debo devolver null.
  if (!itree_es_vacio (arbol1) && !itree_es_vacio (arbol2)){
    ITree arbolMasAlto, arbolMasBajo;
    // El arbol mas alto sera el arbol a intersecar con.
    if (arbol1->altura >= arbol2->altura){
      arbolMasAlto = arbol1;
      arbolMasBajo = arbol2;
    }
    else{
      arbolMasAlto = arbol2;
      arbolMasBajo = arbol1;
    }
    // Se intersecan los intervalos del arbol petizo con los del arbol alto.
    itree_dfs_interseccion (arbolMasBajo, arbolMasAlto, itree_intersecar2, &arbolNuevo);
  }
  return arbolNuevo;
}

void itree_dfs_interseccion (ITree petizo, ITree alto, FuncionInt visit, ITree *destino){
  // Se recorre el arbol petizo de forma inorder. Haciendo que cada intervalo de
  // este ultimo, se intserseque con tod el arbol mas alto.
  if (!itree_es_vacio (petizo)){
    itree_dfs_interseccion (petizo->left, alto, visit, destino);
    visit (alto, petizo->intervalo, destino);
    itree_dfs_interseccion (petizo->right, alto, visit, destino);
  }
}

void itree_intersecar2 (ITree arbolAInt, IntervaloE intervalo, ITree *arbolRes){
  // Si el arbol a intersecar con el intervalo es no vacio...
  if (!itree_es_vacio (arbolAInt)){
    // Es importante tener en cuenta que estos itree son de intervalos disjuntos.
    int interseccion = intervaloE_interseccion (arbolAInt->intervalo, intervalo);

    if (interseccion == 1){
      // Nuevo intervalo que almacena la interseccion.
      IntervaloE intervaloInt;
      intervaloInt = intervaloE_intersecar (arbolAInt->intervalo, intervalo);
      // Se inserta en el arbol resultado.
      itree_insertar (arbolRes, intervaloInt);
    }
    // Si el extremo izquierdo de intervalo, es menor que el extremo izquierdo
    // del intervalo con el que se quizo intersecar. Entonces puede haber
    // mas intersecciones a la izquierda.
    if (intervalo.extIzq < arbolAInt->intervalo.extIzq)
      itree_intersecar2 (arbolAInt->left, intervalo, arbolRes);

    // Si el extremo derecho de intervalo, es mayor que el extremo derecho
    // del intervalo con el que se quizo intersecar. Entonces puede haber
    // mas intersecciones a la derecha.
    if (intervalo.extDer > arbolAInt->intervalo.extDer)
      itree_intersecar2 (arbolAInt->right, intervalo, arbolRes);
  }
}




void print2D(ITree arbol){
   // Se pasa el espacio inicial como 0.
   print2DUtil(arbol, 0);
}

void print2DUtil(ITree arbol, int espacio){
    // Caso base.
    if (itree_es_vacio(arbol))
        return;

    // Se incrementa el espacio entre niveles.
    espacio += COUNT;

    // Se procesa el hijo derecho primero.
    print2DUtil(arbol->right, espacio);

    // Se imprime el nodo actual luego de la cantidad de espacios que
    // corresponden.
    printf("\n");
    for (int i = COUNT; i < espacio; ++i)
        printf(" ");
    intervaloE_imprimir (arbol->intervalo);

    // Luego, se imprime el maximo extremo derecho del arbol despues de la
    // cantidad de espacios que corresponden.
    printf("\n");
    for (int i = COUNT; i < espacio; ++i)
        printf(" ");
    printf(" %g", arbol->maxExtDer);

    // Se procesa el hijo izquierdo.
    print2DUtil(arbol->left, espacio);
}

void itree_destruir (ITree raiz){
  // Si hay algo para destruir, lo destruimos.
  if (!itree_es_vacio(raiz)){
    // Destruimos los dos hijos del arbol.
    itree_destruir (raiz->left);
    itree_destruir (raiz->right);
    // Liberamos el nodo actual.
    free (raiz);
  }
}
