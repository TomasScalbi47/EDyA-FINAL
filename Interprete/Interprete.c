//
// Created by scalbi on 7/8/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "interprete.h"
#define TAM_INICIAL_BUFF 1

int main (){
    int tamBuffer = TAM_INICIAL_BUFF;
    char *entradaFinal = leer_entrada (&tamBuffer);

    printf ("entradaFinal: |%s|", entradaFinal);
    return 0;
}

char* leer_entrada (int *tamBuffer){
    int cantElementos = 0;
    char *buffer = malloc (sizeof(char) * *tamBuffer);
    char entrada = getchar();

    while (entrada != '\n'){
        if (cantElementos == *tamBuffer - 1)
            buffer = aumentar_tamanio(buffer, tamBuffer);
        buffer[cantElementos] = entrada;
        cantElementos += 1;
        entrada = getchar();
    }
    buffer[cantElementos] = '\0';
    // Reajustando el tamaño del buffer al minimo.
    buffer = realloc (buffer, cantElementos * sizeof(char) + 1);
    return buffer;
}

char* aumentar_tamanio (char* buffer, int *tamAnterior){
    int nuevoTamanio = *tamAnterior * 2;
    char* nuevoBuffer = malloc (sizeof(char) * nuevoTamanio);
    for (int i = 0; i < *tamAnterior; ++i)
        nuevoBuffer[i] = buffer[i];
    *tamAnterior = nuevoTamanio;

    return nuevoBuffer;
}