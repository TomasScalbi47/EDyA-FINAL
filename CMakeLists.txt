cmake_minimum_required(VERSION 3.15)
project(EDyA-FINAL C)

set(CMAKE_C_STANDARD 11)

include_directories(Arboles)
include_directories(AVL)
include_directories(Hash)
include_directories(HashAVL)
include_directories(Interprete)
include_directories(Intervalos)
include_directories(Listas)

add_executable(EDyA-FINAL
    Arboles/ITree1.c
    Arboles/ITree1.h
    Arboles/pruebaArboles.c
    AVL/avl.c
    AVL/avl.h
    Hash/tablahash.c
    Hash/tablahash.h
    HashAVL/hashavl.c
    HashAVL/hashavl.h
    Interprete/interprete.c
    Interprete/interprete.h
    Intervalos/intervaloE.c
    Intervalos/intervaloE.h
    Listas/hlist.c
    Listas/hlist.h
    )