//
// Created by scalbi on 7/8/2020.
//

#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__


void imprimir_menu ();

/**
 * Funcion del interprete que hace todo.
 */
void interpretar ();

/**
 * Lee la entrada completa y devuelve un string con su contenido.
 */
char* leer_entrada ();

/**
 * Dado un buffer con su tamaño anterior.
 * Crea uno nuevo, y aumenta su tamaño multiplicandolo por 2.
 */
char* aumentar_tamanio (char* buffer, int *tamAnterior);

int validar_alias_entrada(char* alias);



#endif __INTERPRETE_H__
