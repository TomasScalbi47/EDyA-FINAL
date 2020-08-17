#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include "../Arboles/ITree1.h"
// ITree1.h contiene IntervaloE.h...
//#include "../Hash/tablahash.h"
#include "../HashAVL/hashavl.h"

/**
 * A medida que se va leyendo la entrada, se identifican si hay errores de
 * sintaxis y de no haberlos, realizan la operacion indicada.
 */
void operaciones (char *entradaParser, char *destino, char* nombre1,
                  char *operacion, TablaHash *tabla);
/**
 * Funcion realicionada al comando complemento.
 * A medida que se va leyendo la entrada, de identifican si hay errores de
 * sintaxis y de no haberlos, se guarda en la tabla hash, el complemento del
 * conjunto 'origen' con el nombre 'destino'.
 */
void complemento (char *destino, char *origen, TablaHash *tabla);

/**
 * Funcion relacionada al comando imprimir.
 * De no haber errores de sintaxis. Se corrobora que el conjunto que se quiere
 * imprimir exista en la tablahash, y de ser asi lo imprime segun el tipo de
 * impresion que se le pase.
 */
void imprimir (char *entradaParser, char *origen, TablaHash *tabla,
               FuncionImpresion imprimir);

/**
 * Funcion relacionada al comando de crear por extension.
 * De no haber errores de sintaxis, sean estos numeros invalidos, caracteres
 * extraños.
 * Se van insertando los intervalos en el conjunto resultado, y al final si la
 * entrada termino siendo totalmente valida, se guarda este nuevo conjunto
 * en la tablahash con su alias correspondiente.
 * Si se llegase a econtrar algun error durante la creacion del conjunto, este
 * se destruye.
 */
void crear_extension (char* palabra3, char* destino, TablaHash *tabla,
                      ITree *arbolNuevo);

/**
 * Funcion relacionada al comando de crear por compresion.
 * De no haber errores de sintaxis, sean estos numeros, simbolos invalidos
 * que no haya caracteres extraños, espacios mal colocados etc...
 * Se crea un nuevo conjunto y se guarda en la tabla hash con la clave 'destino'.
 * Si el intervalo es de la forma: "... a <= x <= b}" siendo a > b.
 *      Se guarda como se indico en la consigna, como conjunto vacio.
 */
void crear_compresion (char* entradaPars, char* destino, char *variable,
                       TablaHash *tabla, ITree *arbolNuevo);

/**
 * Lee la entrada completa y devuelve un string con su contenido.
 */
char* leer_entrada ();

/**
 * Dado un buffer con su tamaño anterior.
 * Crea uno nuevo, y aumenta su tamaño multiplicandolo por 2.
 */
char* aumentar_tamanio (char* buffer, int *tamAnterior);

/**
 * Se imprime el menu con la informacion necesaria para utilizar el interprete.
 */
void imprimir_menu ();

/**
 * Dada una cadena de caracteres, se corrobora que todos sus elementos sean
 * o caracteres alfanumericos (sin la ñ ni tildes) o bien digitos del 0-9.
 * Devuelve 1 si el alias es valido, 0 caso contrario.
 */
int validar_alias_entrada(char* alias);

/**
 * Dado un numero long, corrobora si esta dentro de los limites de int.
 */
int validar_int (long numero);

/**
 * Funcion que contiene todos los mensajes de error que el interprete devuelve.
 * Se dividen los mensajes de error en 2 categorias.
 *      1) Errores de sintaxis.
 *      2) Errores de uso.
 * Dependiendo el indentificador del error, se devolvera el mensaje de error
 * adecuado.
 * La variable data existe para aportar informacion extra en algunos casos.
 */
void mensaje_error (char* ident, char* data);

/**
 * Funcion principal.
 * Crea la tabla hash que almacenara todos los conjuntos.
 * Lee la entrada, corrobora su sintaxis, identifica los errores, y deriva a
 * las funciones correspondientes segun el requerimento.
 */
void interpretar ();

#endif __INTERPRETE_H__
