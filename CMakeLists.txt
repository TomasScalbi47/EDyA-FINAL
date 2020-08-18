cmake_minimum_required(VERSION 3.15)
project(EDyA-FINAL C)

set(CMAKE_C_STANDARD 11)

include_directories(Conjuntos)
include_directories(AVL)
include_directories(HashAVL)
include_directories(Interprete)
include_directories(Intervalos)

add_executable(EDyA-FINAL
    Conjuntos/conjuntos.c
    Conjuntos/conjuntos.h
    AVL/avl.c
    AVL/avl.h
    HashAVL/hashavl.c
    HashAVL/hashavl.h
    Interprete/interprete.c
    Interprete/interprete.h
    Intervalos/intervaloE.c
    Intervalos/intervaloE.h
    )