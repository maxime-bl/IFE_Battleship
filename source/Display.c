//
// Created by maxim on 06/05/2021.
//
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include "../header/Display.h"

void init_display(){
    _setmode(_fileno(stdout), _O_U16TEXT);

}


void show_menu(){
    char *test = L"     ┌────────────────────┐\n"
                 "     │     BATTLESHIP     │\n"
                 "     └────────────────────┘\n";
    wprintf(L"%s", test);
}

void show_grid(){
    wprintf(L"\n"
            "    A   B   C   D   E   F   G   H   I   J\n"
            "  ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐\n"
            "0 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "1 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "2 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "3 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "4 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "5 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "6 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "7 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "8 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "9 │   │ x │   │   │   │   │   │   │   │   │\n"
            "  └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘\n");
}