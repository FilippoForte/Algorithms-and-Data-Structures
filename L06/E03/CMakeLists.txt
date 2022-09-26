cmake_minimum_required(VERSION 3.20)
project(E03 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(E03
        equipArray.h
        gdr.c
        inv.h
        invArray.h
        pg.h
        pgList.h inv.c invArray.c equipArray.c pg.c pgList.c)
