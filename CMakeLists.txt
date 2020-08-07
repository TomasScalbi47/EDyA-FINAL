cmake_minimum_required(VERSION 3.15)
project(EDyA-FINAL C)

set(CMAKE_C_STANDARD 11)

include_directories(Arboles/Intervalos)
include_directories(Arboles)

add_executable(EDyA-FINAL
    Arboles/ITree1.c
    Arboles/ITree1.h
    Arboles/pruebaArboles.c
    Arboles/Intervalos/intervaloE.h
    Arboles/Intervalos/intervaloE.c
        )