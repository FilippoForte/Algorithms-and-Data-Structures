cmake_minimum_required(VERSION 3.20)
project(E03 C)

set(CMAKE_C_STANDARD 99)

add_executable(E03 main.c ST.c ST.h nodo.c nodo.h Graph.c Graph.h)
