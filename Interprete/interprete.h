#ifndef __interprete_h__
#define __interprete_h__

#include "Arboles/Intervalos/intervaloE.h"

/**
 * Crea un arbol y un intervalo.
 * Luego comienza la iteracion.
 * Lee lo ingresado por la entrada estandar y realiza distintas acciones segun
 * el comando ingresado.
 * Si lo ingresado no es un comando valido, devuelve un mensaje de error.
 * Si no realiza la accion correspondiente en el arbol creado:
 * "i [a,b]" ==> inserta el intervalo [a,b] en el arbol.
 * "e [a,b]" ==> elimina el intervalo [a,b] del arbol.
 * "? [a,b]" ==> interseca el intervalo [a,b] con los intervalos del arbol
 *                  Imprime "No"        <=> no hay interseccion.
 *                          "Si, [x,y]" <=> existe un intervalo que interseque.
 *                                          siendo [x,y] este.
 * "dfs" ==> imprime los intervalos de larbol con recorrido primero en profundidad.
 * "bfs" ==> imprime los intervalos del arbol con recorrido primero a lo ancho.
 * "salir" ==> corta la iteracion.
 *
 * Como fue indicado arriba, la iteracion se hace hasta que se ingresa el comando "salir".
 */
void interprete ();


/**
 * Dada una entrada y un apuntador a un intervalo.
 * Devuelve si esta es valida o no, tambien modifica el intervalo de tal forma
 * que se corresponda con el ingresado.
 * 0: salir
 */
char validar_entrada (char*, IntervaloE* );

/**
 * Dado un apuntador a caracteres que representa lo siguiente al nombre
 * del comando indicado.
 * Determina si el argumento es considerado valido, devolviendo:
 *  1 si lo es.
 *  0 si no lo es.
 */
int validar_argumento (char *entrada);

/**
 * Dado un apuntador a caracteres, una bandera, y un entero.
 * Determina si la coma (lugar donde apunta entrada) colocada es valida,
 * teniendo en cuenta su ubicacion y contexto, devolviendo:
 *  1 si lo es.
 *  0 si no lo es.
 */
int validar_coma (char *entrada, int bandera, int i);

/**
 * Dado un apuntador a caracteres, una bandera, y un entero.
 * Determina si el signo menos (lugar donde apunta entrada) colocado es valido,
 * teniendo en cuenta su ubicacion y contexto, devolviendo:
 *  1 si lo es.
 *  0 si no lo es.
 */
int validar_sign_menos (char *entrada, int bandera, int i);

/**
 * Dado un apuntador a caracteres, una bandera, y un entero.
 * Determina si el punto (lugar donde apunta entrada) colocado es valido,
 * teniendo en cuenta su ubicacion y contexto, devolviendo:
 *  1 si lo es.
 *  0 si no lo es.
 */
int validar_punto (char *entrada, int bandera, int i);

/**
 * Dado un caracter.
 * Determina si este es un numero o no, devolviendo:
 *  1 si lo es.
 *  0 si no lo es.
 */
int validar_numero (char entrada);

/**
 * Dado un apuntador a caracteres, y un entero.
 * Determina si el espacio (lugar donde apunta entrada) colocado es valido,
 * teniendo en cuenta su ubicacion, devolviendo:
 *  1 si lo es.
 *  0 si no lo es.
 */
int validar_espacio (char* entrada, int i);

/**
 * Dado un apuntador a caracteres, y un entero.
 * Determina si la e (lugar donde apunta entrada) colocada es valido,
 * teniendo en cuenta su ubicacion y contexto, devolviendo:
 *  1 si lo es.
 *  0 si no lo es.
 */
int validar_exp (char* entrada, int bandera, int i);

#endif
