#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ITree1.h"

/* -------------------------------- BASICAS ----------------------------------*/
ITree itree_crear (){
  return NULL;
}

int itree_es_vacio (ITree arbol){
  return arbol == NULL;
}

int itree_es_universo (ITree arbol){
    return (arbol->intervalo.extIzq == INT_MIN && arbol->intervalo.extDer == INT_MAX);
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

void itree_imprimir (ITree arbol){
  if (!itree_es_vacio (arbol)) {

    IntervaloE *ant = NULL;
    itree_imprimir_util(arbol, &ant);
    intervaloE_imprimir(*ant, "");
    printf("\n");
  }
}

void itree_imprimir_util (ITree arbol, IntervaloE **ant){
  if (!itree_es_vacio (arbol)){
    itree_imprimir_util (arbol->left, ant);

    if (*ant != NULL)
      intervaloE_imprimir (**ant, ", ");
    *ant = &(arbol->intervalo);
    itree_imprimir_util (arbol->right, ant);
  }
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

/* ------------------------------ BALANCEO -----------------------------------*/

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
  // Es necesario actualizar el valor de altura de A puesto que
  // cambio el hijo izquierdo de A y no sabemos si se sigue manteniendo.
  itree_actualizar_altura(&arbol);

  // Se cambia el hijo derecho de B a A.
  nodoRelevante->right = arbol;
  // Es necesario actualizar el valor de altura de B por motivos analogos
  itree_actualizar_altura(&nodoRelevante);

  return nodoRelevante;
}

ITree itree_rotacion_izq (ITree arbol){
  // arbol: A.
  // nodoRelevante: B.
  ITree nodoRelevante = arbol->right;
  // Se cambia el hijo derecho de A a el hijo izquierdo de B.
  arbol->right = nodoRelevante->left;
  // Es necesario actualizar el valores de altura de A puesto que
  // cambio el hijo derecho de A y no sabemos si se sigue manteniendo.
  itree_actualizar_altura(&arbol);

  // Se cambia el hijo izquierdo de B a A.
  nodoRelevante->left = arbol;
  // Es necesario actualizar el valor de altura de B por
  // motivos analogos.
  itree_actualizar_altura(&nodoRelevante);

  return nodoRelevante;
}

/* ----------------------------- FUNDAMENTALES -------------------------------*/

ITree itree_copiar (ITree arbol){
  // Si el arbol es vacio...
  if (arbol == NULL)
    return NULL;
  // El arbol a copiar es no vacio.
  ITree nuevoArbol = malloc (sizeof (ITreeNodo));
  nuevoArbol->intervalo = arbol->intervalo;
  nuevoArbol->altura = arbol->altura;

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
    while (!itree_es_vacio (interseccion)) {
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

      // Luego de insertar el intervalo, se actualiza la altura del nodo.
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

      // Luego de eliminar el nodo, se actualiza el valor de altura del nodo.
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

    // Luego de eliminar el nodo, se actualiza el valor de altura del nodo.
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
      resultado = itree_intersecar(arbol->left, intervalo);

      // Si el extremo derecho de intervalo, es mayor que el extremo derecho
      // del intervalo con el que se quizo intersecar. Entonces puede haber
      // mas intersecciones a la derecha.
    else if(intervalo.extDer > arbol->intervalo.extDer)
      resultado = itree_intersecar (arbol->right, intervalo);
  }
  return resultado;
}

/* ----------------------------- CONJUNTOS -----------------------------------*/

void itree_dfs_origen_destino (ITree origen1, ITree origen2, FuncionAux aux,
                               ITree *destino){
  if (!itree_es_vacio (origen1)){
    itree_dfs_origen_destino (origen1->left, origen2, aux, destino);
    aux(origen2, origen1->intervalo, destino);
    itree_dfs_origen_destino (origen1->right, origen2, aux, destino);
  }
}


ITree itree_unir (ITree arbol1, ITree arbol2){
  ITree nuevoArbol = itree_crear();
  // Corroboro que ninguno de los dos arboles sea el conjunto vacio o universo.
  if (itree_es_vacio (arbol1) || itree_es_universo (arbol2))
    nuevoArbol = itree_copiar (arbol2);
  else if (itree_es_vacio (arbol2) || itree_es_universo (arbol1))
    nuevoArbol = itree_copiar (arbol1);
  // Ninguno de los arboles es el conjunto vacio o el universo.
  else {
    // Interesa que se pase el arbol mas bajo como primer argumento a la
    // funcion itree_dfs_union. Puesto que copiar el arbol mas alto es mas
    // barato.
    ITree arbolMasAlto, arbolMasBajo;
    if (arbol1->altura >= arbol2->altura) {
      arbolMasAlto = arbol1;
      arbolMasBajo = arbol2;
    }
    else {
      arbolMasAlto = arbol2;
      arbolMasBajo = arbol1;
    }
    nuevoArbol = itree_copiar (arbolMasAlto);
    itree_dfs_union (arbolMasBajo, &nuevoArbol);
  }
  return nuevoArbol;
}

void itree_dfs_union (ITree origen, ITree *arbolU){
  if (!itree_es_vacio(origen)){
    itree_dfs_union(origen->left, arbolU);
    itree_insertar (arbolU, origen->intervalo);
    itree_dfs_union(origen->right, arbolU);
  }
}

ITree itree_interseccion (ITree arbol1, ITree arbol2){
  ITree arbolNuevo = itree_crear ();
  // Si alguno de los 2 arboles es vacio entonces ya debo devolver null.
  if (!itree_es_vacio (arbol1) && !itree_es_vacio (arbol2)){
    // Si alguno de los 2 arboles es el universo, se devuelve el otro.
    if (itree_es_universo (arbol1))
      arbolNuevo = itree_copiar (arbol2);
    else if (itree_es_universo (arbol2))
      arbolNuevo = itree_copiar (arbol1);
    else {
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
      itree_dfs_origen_destino (arbolMasBajo, arbolMasAlto, itree_intersecarV,
                                &arbolNuevo);
    }
  }
  return arbolNuevo;
}

void itree_intersecarV (ITree arbolAInt, IntervaloE intervalo, ITree *arbolRes){
  // Si el arbol a intersecar con el intervalo es no vacio...
  if (!itree_es_vacio (arbolAInt)){
    // Es importante tener en cuenta que estos itree son de intervalos disjuntos.
    int interseccion = intervaloE_interseccion (arbolAInt->intervalo, intervalo);

    if (interseccion){
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
      itree_intersecarV(arbolAInt->left, intervalo, arbolRes);

    // Si el extremo derecho de intervalo, es mayor que el extremo derecho
    // del intervalo con el que se quizo intersecar. Entonces puede haber
    // mas intersecciones a la derecha.
    if (intervalo.extDer > arbolAInt->intervalo.extDer)
      itree_intersecarV(arbolAInt->right, intervalo, arbolRes);
  }
}


ITree itree_complemento (ITree origen){
  ITree nuevoArbol = itree_crear();

  // Si el conjunto no es el universo...
  if (!itree_es_universo (origen)) {
    if (!itree_es_vacio (origen)){
      // Se sabe con seguridad que el arbol origen es != universo y != vacio.
      IntervaloE ant = intervaloE_crear (INT_MIN, INT_MIN);
      // Le doy este valor al intervalo anterior a sabiendas que la funcion
      // recursiva debajo, al ser inorder, comenzara por el nodo mas a la
      // izquierda.
      itree_complemento_aux(origen, &nuevoArbol, &ant);
      // Ahora ant contiene el valor del ultimo intervalo.
      if (ant.extDer != INT_MAX){
        itree_insercion (&nuevoArbol,intervaloE_crear(ant.extDer + 1,
                                                     INT_MAX));
      }
    }
    // El conjunto origen es el vacio, insertando el intervalo universo.
    else
      itree_insertar (&nuevoArbol, intervaloE_crear (INT_MIN, INT_MAX));
  }

  return nuevoArbol;
}

void itree_complemento_aux (ITree origen, ITree *destino, IntervaloE *ant){
  // Mientras el arbol no sea vacio.
  if (!itree_es_vacio (origen)) {
    // Voy lo maximo a la izuierda.
    itree_complemento_aux(origen->left, destino, ant);

    IntervaloE aInsertar;
    // Si el extremo izquierdo es distinto de INT_MIN
    if (origen->intervalo.extIzq != INT_MIN) {
      // Primer caso.
      if (ant->extDer == INT_MIN)
        aInsertar = intervaloE_crear(ant->extDer, origen->intervalo.extIzq - 1);
      // Resto de casos.
      else
        aInsertar = intervaloE_crear(ant->extDer + 1,
                                     origen->intervalo.extIzq - 1);
      itree_insertar(destino, aInsertar);
    }
    *ant = origen->intervalo;

    itree_complemento_aux(origen->right, destino, ant);
  }
}


ITree itree_resta (ITree arbol1, ITree arbol2){
  ITree nuevoArbol = itree_crear();
  // Corroborando que el primer arbol sea no vacio.
  // Pues {} - A = {} & A = {}.
  if (!itree_es_vacio(arbol1)){
    // Corroborando que el segundo arbol sea no vacio.
    // Pues A - {} = A & Universo = A.
    if (itree_es_vacio (arbol2))
      nuevoArbol = itree_copiar (arbol1);
    // Corroborando que el primer arbol no sea el unniverso.
    // Pues Universo - B = Universo & ~ B = ~ B.
    else if (itree_es_universo (arbol1))
      nuevoArbol = itree_complemento (arbol2);
    // Corroborando que el segundo arbol no sea el universo.
    // Pues A - Universo = A & {} = {}
    else if (!itree_es_universo (arbol2)) {
      // Ninguno de los dos arboles es el universo ni vacio.
      itree_dfs_origen_destino (arbol1, arbol2, itree_resta_aux,
                                &nuevoArbol);
    }
  }
  return nuevoArbol;
}

void itree_resta_aux (ITree arbol2, IntervaloE intervalo, ITree *destino){
  // Si el arbol a intersecar con el intervalo es no vacio.
  if (itree_es_vacio(arbol2))
    itree_insertar(destino, intervalo);
  else {
    int interseccion = intervaloE_interseccion(intervalo, arbol2->intervalo);

    if (interseccion){
      // ver si sobra de los costaditos.

      // sobra izquierda
      if (intervalo.extIzq < arbol2->intervalo.extIzq){
        intervalo = intervaloE_no_interseccion_izq(intervalo, arbol2->intervalo);
        itree_resta_aux (arbol2->left, intervalo, destino);
      }
      // sobra derecha
      if (intervalo.extDer > arbol2->intervalo.extDer){
        intervalo = intervaloE_no_interseccion_der(intervalo, arbol2->intervalo);
        itree_resta_aux (arbol2->right, intervalo, destino);
      }
    }
    // Si el extremo izquierdo de intervalo, es menor que el extremo izquierdo
    // del intervalo con el que se quizo intersecar. Entonces puede haber
    // mas intersecciones a la izquierda.
    else if (intervalo.extIzq < arbol2->intervalo.extIzq)
      itree_resta_aux(arbol2->left, intervalo, destino);
    // Si el extremo derecho de intervalo, es mayor que el extremo derecho
    // del intervalo con el que se quizo intersecar. Entonces puede haber
    // mas intersecciones a la derecha.
    else if (intervalo.extDer > arbol2->intervalo.extDer)
      itree_resta_aux(arbol2->right, intervalo, destino);
  }
}

/* ----------------------------- AUXILIARES ----------------------------------*/

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
  intervaloE_imprimir2D(arbol->intervalo);

    // Se procesa el hijo izquierdo.
    print2DUtil(arbol->left, espacio);
}


