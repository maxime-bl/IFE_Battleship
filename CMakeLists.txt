cmake_minimum_required(VERSION 3.19)
project(IFE_Project C)

set(CMAKE_C_STANDARD 99)

add_executable(IFE_Project source/main.c source/SaveFiles.c header/SaveFiles.h source/Display.c header/Display.h)