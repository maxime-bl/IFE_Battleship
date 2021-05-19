//
// Created by maxim on 06/05/2021.
//
#include "../header/Dialogs.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#include <windows.h>

#include "../header/Display.h"
#include "../header/Grid.h"
#include "../header/Boats.h"
#include "../header/Missiles.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif


int init_display() {
    // enables unicode font in the console
    _setmode(_fileno(stdout), _O_U16TEXT);

    // enables colors in the console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return GetLastError();
    }

}


void fifty_line_breaks() {
    for (int i = 0; i < 50; i++) {
        wprintf(L"\n");
    }
}


void show_main_menu() {
    fifty_line_breaks();
    wprintf(L"╔════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                               ╔──────────────────╗                             ║\n"
            "║▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│    BATTLESHIP    │▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒║\n"
            "║                               ╚──────────────────╝                             ║\n"
            "╠════════════════════════════════════════════════════════════════════════════════╣\n"
            "║                                                                                ║     \n"
            "║                  ╔════════════════════════════════════════╗                    ║\n"
            "║                  ║ ░   Press '1' to start a new game    ░ ║                    ║\n"
            "║                  ╟────────────────────────────────────────╢                    ║\n"
            "║                  ║ ░     Press '2' to load last game    ░ ║                    ║\n"
            "║                  ╟────────────────────────────────────────╢                    ║\n"
            "║                  ║ ░         Press '3' to quit          ░ ║                    ║\n"
            "║                  ╚════════════════════════════════════════╝                    ║\n"
            "║                                                                                ║\n"
            "║                   ||                                                           ║\n"
            "║                   ||             _____________                                 ║\n"
            "║                   ||     ________[><><>|<><><]  _______                        ║\n"
            "║               [___|]_____[_______[___________] ///|\\\\\\\\_________               ║\n"
            "║               \\  o  o  o  o  o  o  o  o  o   \\[_______==========`              ║\n"
            "║          ~~~~~~\\                              ]]]]]]]]/~~~~~~~                 ║\n"
            "║           ~~~~~~\\____________________________________/~~~~~~~~~~~~             ║\n"
            "║          ~~~~~~~~~~~~~~~~~~~~~~~~~~~ `-> ~~ `-> ~~~~~~~~~~~~~~~~~~~~           ║\n"
            "║          ~~~~~~~~~~~~~~~~~~~~~~ `-> ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~          ║\n"
            "╟────────────────────────────────────────────────────────────────────────────────╢\n"
            "║            © 2021 IFE Project by Maxime Blanchard and Manon Truchet            ║\n");
}


// prints one row of the grid
void print_row(char *arr, int rowLength) {
    for (int i = 0; i < rowLength; i++) {
        wprintf(L" %c │", arr[i]);
    }
}


// show the boat's number of hit squares and its state
void show_boat_health(Boat boat) {
    int health=0;

    for (int i = 0; i < boat.size; i++) {
        if (boat.squares[0] > 0) {
            wprintf(L" ●");
            health++;
        } else {
            wprintf(L" ◯");
        }
    }

    for (int j = 0; j < 8 - boat.size; j++) {
        wprintf(L"  ");
    }

    unsigned short *state;

    if (health == 0) {
        state = L"DESTROYED";
    } else if (health < boat.size) {
        state = L"HIT      ";
    } else {
        state = L"INTACT   ";
    }

    wprintf(L"│%s",state);
}


void show_grid(Grid grid, Boat *boatArr, Inventory inv, int mode) {
    fifty_line_breaks();

    // TO-DO :  make the top message functional
    wprintf(L"╔════════════════════════════════════════════════════════════════════════════════╗\n"
            "║ Last round, %d ships were touched and %d destroyed                               ║\n"
            "╟────────────────────────────────────────────────────────────────────────────────╢\n"
            "║                                                 ┌────────────────────────────┐ ║\n"
            "║                 ┌──────────────┐                │╔══════════════════════════╗│ ║\n"
            "║                 │     GRID     │                │║ Remaining missiles       ║│ ║\n"
            "║                 └──────────────┘                │╠════════════════════╤═════╣│ ║\n"
            "║      0   1   2   3   4   5   6   7   8   9      │║ Artillery          │%02d/%02d║│ ║\n"
            "║    ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐    │╟────────────────────┼─────╢│ ║\n"
            "║  A │", 0, 0, inv.artilleryCnt, inv.maxArtillery);
    print_row(grid.array[0], grid.width);

    wprintf(L"    │║ Tactical           │%02d/%02d║│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │╟────────────────────┼─────╢│ ║\n"
            "║  B │", inv.tacticalCnt, inv.maxTactical);
    print_row(grid.array[1], grid.width);

    wprintf(L"    │║ Bomb               │%02d/%02d║│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │╟────────────────────┼─────╢│ ║\n"
            "║  C │", inv.bombCnt, inv.maxBomb);
    print_row(grid.array[2], grid.width);

    wprintf(L"    │║ Single             │%02d/%02d║│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │╚════════════════════╧═════╝│ ║\n"
            "║  D │", inv.singleCnt, inv.maxSingle);
    print_row(grid.array[3], grid.width);

    wprintf(L"    │╔══════════════════════════╗│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║ Remaining fleet          ║│ ║\n"
            "║  E │");
    print_row(grid.array[4], grid.width);

    wprintf(L"    │╠════════════════╤═════════╣│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║");
    show_boat_health(boatArr[0]);
    wprintf(L"║│ ║\n"
            "║  F │");
    print_row(grid.array[5], grid.width);

    wprintf(L"    │╟────────────────┼─────────╢│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║");
    show_boat_health(boatArr[1]);
    wprintf(L"║│ ║\n"
            "║  G │");
    print_row(grid.array[6], grid.width);

    wprintf(L"    │╟────────────────┼─────────╢│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║");
    show_boat_health(boatArr[2]);
    wprintf(L"║│ ║\n"
            "║  H │");
    print_row(grid.array[7], grid.width);

    wprintf(L"    │╟────────────────┼─────────╢│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║");
    show_boat_health(boatArr[3]);
    wprintf(L"║│ ║\n"
            "║  I │");
    print_row(grid.array[8], grid.width);

    wprintf(L"    │╟────────────────┼─────────╢│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║");
    show_boat_health(boatArr[4]);
    wprintf(L"║│ ║\n"
            "║  J │");
    print_row(grid.array[9], grid.width);

    wprintf(L"    │╚════════════════╧═════════╝│ ║\n"
            "║    └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘    └────────────────────────────┘ ║\n"
            "║                                                                                ║\n"
            "╟────────────────────────────────────────────────────────────────────────────────╢\n");


    /*      "╔════════════════════════════════════════════════════════════════════════════════╗\n"
            "║ Last round, x ships were touched and y destroyed                               ║\n"
            "╟────────────────────────────────────────────────────────────────────────────────╢\n"
            "║                                                 ┌────────────────────────────┐ ║\n"
            "║                 ┌──────────────┐                │╔══════════════════════════╗│ ║\n"
            "║                 │     GRID     │                │║ Remaining missiles       ║│ ║\n"
            "║                 └──────────────┘                │╠════════════════════╤═════╣│ ║\n"
            "║      A   B   C   D   E   F   G   H   I   J      │║ Artillery          │ ./. ║│ ║\n"
            "║    ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐    │╟────────────────────┼─────╢│ ║\n"
            "║  1 │   │   │   │   │   │   │   │   │   │   │    │║ Tactical           │ ./. ║│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │╟────────────────────┼─────╢│ ║\n"
            "║  2 │   │   │   │   │   │   │   │   │   │ - │    │║ Bomb               │ ./. ║│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │╟────────────────────┼─────╢│ ║\n"
            "║  3 │   │   │   │   │   │   │   │   │   │ - │    │║ Single             │ ./. ║│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │╚════════════════════╧═════╝│ ║\n"
            "║  4 │   │   │   │   │   │   │   │   │   │   │    │╔══════════════════════════╗│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║ Remaining fleet          ║│ ║\n"
            "║  5 │   │   │   │   │   │   │   │   │   │   │    │╠════════════════╤═════════╣│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║ ◯ ◯ ◯ ◯ ◯      │DESTROYED║│ ║\n"
            "║  6 │   │   │   │   │   │   │   │   │   │   │    │╟────────────────┼─────────╢│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║ ● ● ● ●        │INTACT   ║│ ║\n"
            "║  7 │   │   │   │   │   │   │   │   │   │   │    │╟────────────────┼─────────╢│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║ ● ● ◯          │HIT      ║│ ║\n"
            "║  8 │   │   │   │   │   │   │   │   │   │   │    │╟────────────────┼─────────╢│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║ ● ● ●          │INTACT   ║│ ║\n"
            "║  9 │   │ x │   │   │   │   │   │   │   │   │    │╟────────────────┼─────────╢│ ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤    │║ ● ●            │INTACT   ║│ ║\n"
            "║ 10 │   │ x │   │   │   │   │   │   │   │   │    │╚════════════════╧═════════╝│ ║\n"
            "║    └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘    └────────────────────────────┘ ║\n"
            "║                                                                                ║\n"
            "╟────────────────────────────────────────────────────────────────────────────────╢\n"*/
}


void show_diff_menu() {
    fifty_line_breaks();
    wprintf(L"╔════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                              ╔──────────────────╗                              ║\n"
            "║▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│     NEW GAME     │▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒║\n"
            "║                              ╚──────────────────╝                              ║\n"
            "╠════════════════════════════════════════════════════════════════════════════════╣\n"
            "║                                                                                ║\n"
            "║                              ┌──────────────────┐                              ║\n"
            "║                              │    DIFFICULTY    │                              ║\n"
            "║                              └──────────────────┘                              ║\n"
            "║                                                                                ║\n"
            "║                    ╔══════════════════════════════════════╗                    ║\n"
            "║                    ║ ░        Press '1' for Easy        ░ ║                    ║\n"
            "║                    ╟──────────────────────────────────────╢                    ║\n"
            "║                    ║ ░       Press '2' for Medium       ░ ║                    ║\n"
            "║                    ╟──────────────────────────────────────╢                    ║\n"
            "║                    ║ ░      Press '3' for Difficult     ░ ║                    ║\n"
            "║                    ╚══════════════════════════════════════╝                    ║\n"
            "║                                                                                ║\n"
            "║                                                                                ║\n");
}


void show_mode_menu() {
    fifty_line_breaks();
    wprintf(L"╔════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                              ╔──────────────────╗                              ║\n"
            "║▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│     NEW GAME     │▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒║\n"
            "║                              ╚──────────────────╝                              ║\n"
            "╠════════════════════════════════════════════════════════════════════════════════╣\n"
            "║                                                                                ║\n"
            "║                              ┌──────────────────┐                              ║\n"
            "║                              │ SELECT GAME MODE │                              ║\n"
            "║                              └──────────────────┘                              ║\n"
            "║                                                                                ║\n"
            "║                    ╔══════════════════════════════════════╗                    ║\n"
            "║                    ║ ░       Press '1' for Classic      ░ ║                    ║\n"
            "║                    ╟──────────────────────────────────────╢                    ║\n"
            "║                    ║ ░       Press '2' for Blind        ░ ║                    ║\n"
            "║                    ╟──────────────────────────────────────╢                    ║\n"
            "║                    ║ ░       Press '3' for Active       ░ ║                    ║\n"
            "║                    ╚══════════════════════════════════════╝                    ║\n"
            "║                                                                                ║\n"
            "║                                                                                ║\n");
}


void display_window(int windowID, Grid grid, Boat *boatArray, Inventory inv, int mode) {
    switch (windowID) {
        case MAIN_MENU:
            show_main_menu();
            break;
        case DIFF_MENU:
            show_diff_menu();
            break;
        case GAMEMODE_MENU:
            show_mode_menu();
            break;
        case GAME_WINDOW:
            show_grid(grid, boatArray, inv, mode);
            break;
    }
}