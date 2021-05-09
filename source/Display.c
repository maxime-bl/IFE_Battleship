//
// Created by maxim on 06/05/2021.
//
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#include <windows.h>

#include "../header/Display.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif


int init_display(){
    // enables unicode font in the console
    _setmode(_fileno(stdout), _O_U16TEXT);

    // enables colors in the console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }

}


void show_menu(){
    unsigned short *test = L"\x1b[95m     ┌────────────────────┐\n"
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
            "3 │   │   │   │   │   │   │   │ _ │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "4 │   │   │   │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "5 │   │   │   │   │   │   │   │ O │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "6 │   │   │ _ │ _ │ _ │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "7 │   │   │ _ │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "8 │   │   │ _ │   │   │   │   │   │   │   │\n"
            "  ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n"
            "9 │   │ x │   │   │   │   │   │   │   │   │\n"
            "  └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘\n");
}