/**
 * Archivo de cabecera de mi implementación de intervalos de numeros enteros.
 */

#ifndef __intervaloE_h__
#define __intervaloE_h__

/**
 * Represento intervalos cerrados de números enteros a través de una estructura
 * compuesta por dos int's, donde el primero representa el extremo izquierdo, y
 * el segundo el extremo derecho del intervalo.
 * El tipo de dato IntervaloE no es un apuntador a la estructura _Intervalo
 * ya que este no se autoreferencia.
 */
 typedef struct _IntervaloE {
   int extIzq;
   int extDer;
 } IntervaloE;

/**
 * Macros utiles.
 */
#define max2(x, y) (((x) > (y)) ? (x) : (y))
#define min2(x, y) (((x) < (y)) ? (x) : (y))

/* -------------------------------BASICAS ------------------------------------*/
/**
 * Dados dos enteros.
 * Devuelve un intervalo que tiene como extremo izquierdo al primero de estos e
 * extremo derecho al segundo.
 */
IntervaloE intervaloE_crear (int,int);

/**
 * Criterio de comparacion de intervalos para conjuntos de intervalos disjuntos.
 * Como los intervalos son disjuntos, nunca se daría el caso de extIzq iguales,
 * por lo que no habría que comparar por extDer.
 * < 0 <=> intervalo1.extIzq < intervalo2.extIzq.
 * = 0 <=> intervalo1.extIzq = intervalo2.extIzq.
 * > 0 <=> intervalo1.extIzq > intervalo2.extIzq.
 */
int intervaloE_comparacion (IntervaloE, IntervaloE);

/**
 * Dados dos intervalos de enteros, determina si estos se intersecan.
 * Devuelve: 1 si hay interseccion.
 *           0 si no la hay.
 */
int intervaloE_interseccion (IntervaloE, IntervaloE);

/**
 * Dado un puntero a intervalos, lo imprime formateado:
 *      1) Si representa un numero: "a" + agregar.
 *      2) Si representa un intervalo: "a:b" + agregar.
 * Donde agregar puede ser o no vacio, dependiendo del momento en el que
 * se este imprimiendo.
 */
void intervaloE_imprimir (IntervaloE intervalo, char* agregar);

/**
 * Dado un intervalo, lo imprime formateado "[a,b]".
 */
void intervaloE_imprimir2D (IntervaloE intervalo);

/* ------------------------------ UTILES -------------------------------------*/
/**
 * Dado un intervalo, devuelve su version expandida.
 * ie. [a, b] -> [a-1, b+1]
 */
IntervaloE intervaloE_expandir (IntervaloE);

/**
 * Dados dos intervalos que colisionan los une.
 * ie. intervaloE_unir ([a ,b], [c,d]) -> [min (a,c),  max(c,d)]
 */
IntervaloE intervaloE_unir (IntervaloE, IntervaloE);

/**
 * Dados dos intervalos que colisionan, devuelve la interseccion.
 */
IntervaloE intervaloE_intersecar (IntervaloE intervalo1, IntervaloE intervalo2);

/**
 * Dado dos intervalos, intervalo1 e intervalo2.
 * Obtiene la no interseccion a la izquierda.
 */
IntervaloE intervaloE_no_interseccion_izq (IntervaloE intervalo1, IntervaloE intervalo2);

/**
 * Dado dos intervalos, intervalo1 e intervalo2.
 * Obtiene la no interseccion a la derecha.
 */
IntervaloE intervaloE_no_interseccion_der (IntervaloE intervalo1, IntervaloE intervalo2);
#endif
