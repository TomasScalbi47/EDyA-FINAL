//
// Created by scalbi on 7/8/2020.
//

#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

/**
 * Simbolos importantes: &, |, =, -, ~.
 * Veo que en una linea pueden aparecer mas de una operacion a la vez.
 */

void imprimir_menu ();

/**
 * Funcion del interprete que hace todo.
 */
void interpretar ();

/**
 * Lee la entrada completa y devuelve un string con su contenido.
 */
char* leer_entrada (int *tamBuffer);

/**
 * Dado un buffer con su tamaño anterior.
 * Crea uno nuevo, y aumenta su tamaño multiplicandolo por 2.
 */
char* aumentar_tamanio (char* buffer, int *tamAnterior);

/**
 * Dada una linea de caracteres.
 * Se genera el comando adecuado.
 */
char generar_comando (char* fuente);

int validar_alias_entrada(char* alias);

int crear_conjunto_extension ();

#endif __INTERPRETE_H__
