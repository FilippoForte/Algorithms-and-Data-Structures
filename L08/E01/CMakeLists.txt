cmake_minimum_required(VERSION 3.20)
project(E01 C)

set(CMAKE_C_STANDARD 99)

add_executable(E01 main.c data.c data.h titolo.c titolo.h listaTitoli.c listaTitoli.h quotazione.c quotazione.h BSTquotazioni.c BSTquotazioni.h)
