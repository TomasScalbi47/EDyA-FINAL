/**
 * Archivo de cabecera de nuestra implementacion de intervalos.
 */

#ifndef __intervalos_h__
#define __intervalos_h__

/**
 * Representamos intervalos cerrados de numeros reales a traves de una
 * estructura compuesta por dos doubles donde el primero representa el extremo
 * izquierdo, y el segundo el extremo derecho del intervalo.
 * Decidimos que el tipo de dato al que llamamos Intervalo, no sea un apuntador
 * a la estructura _Intervalo puesto que este a diferencia de las demas tipos de
 * datos declarados como GNodo, no se autoreferencian.
 */
typedef struct _Intervalo {
  double extIzq;
  double extDer;
} Intervalo;

/**
 * Dados dos doubles.
 * Devuelve un intervalo que tiene como extremo izquierdo al primero de estos e
 * intervalo derecho al segundo.
 */
Intervalo intervalo_crear (double, double);

/**
 * Criterio de comparacion para intervalos utilizado en arboles de intervalos.
 * Dados dos intervalos devuelve:
 *      1 si el extremo izq del primero es mayor al del segundo.
 *      -1 si el extremo izq del primero es menor al del segundo
 *      Si sus extremos izq son iguales entonces:
 *          1 si el extremo der del primero es mayor al del segundo.
 *          -1 si el extremo der del primero es menor al del segundo.
 *          0 si sus extremos derechos tambien son iguales.
 */
int intervalo_comparacion (Intervalo, Intervalo);


/**
 * Dado un intervalo, lo imprime formateado "[a,b]".
 * Ademas se imprime como %g lo que ayuda a la legibilidad.
 */
void intervalo_imprimir (Intervalo);

/**
 * Dado dos intervalos, determina si se intersecan.
 * Devuelve: 1 si hay interseccion.
 *           0 si no la hay.
 */
int intervalo_interseccion (Intervalo, Intervalo);


/**
 * Dado un intervalo.
 * Devuelve: 1 si tiene sentido.
 *           0 si no lo tiene. (Por ejemplo que el extremo izq sea < al der).
 */
int intervalo_validar (Intervalo);


#endif
