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
void print_row(Grid grid, int rowNumber) {
    for (int i = 0; i < grid.width; i++) {
        switch (grid.array[rowNumber][i]) {
            case '_':
                wprintf(L"\x1b[34m");
                break;
            case 'X':
                wprintf(L"\x1b[91m");
                break;
            case 'O':
                wprintf(L"\x1b[36m");
                break;
            default:
                break;
        }
        wprintf(L" %c \x1b[0m│", grid.array[rowNumber][i]);
    }
}


// show the boat's number of hit squares and its state
void show_boat_health(Boat boat) {
    int health = 0;
    wprintf(L"     ║");

    //get boat health
    for (int i = 0; i < boat.size; i++) {
        if (boat.squares[i]){
            health++;
        }
    }

    //get state
    unsigned short *state;
    if (health == 0) {
        state = L"\x1b[91mDESTROYED\x1b[0m";
    } else if (health < boat.size) {
        state = L"\x1b[93mHIT      \x1b[0m";
    } else {
        state = L"\x1b[92mINTACT   \x1b[0m";
    }

    //show health bar
    for (int i = 0; i < boat.size; i++) {
        if (health > 0) {
            wprintf(L" ●");
            health--;
        } else {
            wprintf(L" X");
        }
    }

    for (int j = 0; j < 8 - boat.size; j++) {
        wprintf(L"  ");
    }

    //show state
    wprintf(L"│%s║", state);
}


//nightmare
void show_grid(Grid grid, Boat *boatArr, Inventory inv, int mode, int hitCnt, int destroyedCnt) {
    fifty_line_breaks();

    // TO-DO :  make the top message functional
    wprintf(L"╔════════════════════════════════════════════════════════════════════════════════╗\n"
            "║ Last round, \x1b[92m%d\x1b[0m ships were hit and \x1b[92m%d\x1b[0m were destroyed                              ║\n"
            "╟────────────────────────────────────────────────────────────────────────────────╢\n"
            "║                 ┌──────────────┐                 ╔══════════════════════════╗  ║\n"
            "║                 │     GRID     │                 ║ Remaining missiles       ║  ║\n"
            "║                 └──────────────┘                 ╠════════════════════╤═════╣  ║\n"
            "║      0   1   2   3   4   5   6   7   8   9       ║ Artillery          │%02d/%02d║  ║\n"
            "║    ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐     ╟────────────────────┼─────╢  ║\n"
            "║  A │", hitCnt, destroyedCnt, inv.artilleryCnt, inv.maxArtillery);
    print_row(grid, 0);

    wprintf(L"     ║ Tactical           │%02d/%02d║  ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ╟────────────────────┼─────╢  ║\n"
            "║  B │", inv.tacticalCnt, inv.maxTactical);
    print_row(grid, 1);

    wprintf(L"     ║ Bomb               │%02d/%02d║  ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ╟────────────────────┼─────╢  ║\n"
            "║  C │", inv.bombCnt, inv.maxBomb);
    print_row(grid, 2);

    wprintf(L"     ║ Single             │%02d/%02d║  ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ╚════════════════════╧═════╝  ║\n"
            "║  D │", inv.singleCnt, inv.maxSingle);
    print_row(grid, 3);

    wprintf(L"                                   ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ╔══════════════════════════╗  ║\n"
            "║  E │");
    print_row(grid, 4);

    wprintf(L"     ║ Remaining fleet          ║  ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ╠════════════════╤═════════╣  ║\n"
            "║  F │");
    print_row(grid, 5);

    show_boat_health(boatArr[0]);
    wprintf(L"  ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ╟────────────────┼─────────╢  ║\n"
            "║  G │");
    print_row(grid, 6);

    show_boat_health(boatArr[1]);
    wprintf(L"  ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ╟────────────────┼─────────╢  ║\n"
            "║  H │");
    print_row(grid, 7);

    show_boat_health(boatArr[2]);
    wprintf(L"  ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ╟────────────────┼─────────╢  ║\n"
            "║  I │");
    print_row(grid, 8);

    show_boat_health(boatArr[3]);
    wprintf(L"  ║\n"
            "║    ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ╟────────────────┼─────────╢  ║\n"
            "║  J │");
    print_row(grid, 9);

    show_boat_health(boatArr[4]);
    wprintf(L"  ║\n"
            "║    └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘     ╚════════════════╧═════════╝  ║\n"
            "╟────────────────────────────────────────────────────────────────────────────────╢\n");


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


void show_victory_menu(){
    fifty_line_breaks();
    wprintf(L"╔════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                                                                                ║\n"
            "║                                                  .''.                          ║\n"
            "║                      .''.      .        *''*    :_\\/_:     .                   ║\n"
            "║                     :_\\/_:   _\\(/_  .:.*_\\/_*   : /\\ :  .'.:.'.                ║\n"
            "║                 .''.: /\\ :   ./)\\   ':'* /\\ * :  '..'.  -=:o:=-                ║\n"
            "║                :_\\/_:'.:::.    ' *''*    * '.\\'/.' _\\(/_'.':'.'                ║\n"
            "║                : /\\ : :::::     *_\\/_*     -= o =-  /)\\    '  *                ║\n"
            "║                 '..'  ':::'     * /\\ *     .'/.\\'.   '                         ║\n"
            "║                     *            *..*         :                                ║\n"
            "║                       *                                                        ║\n"
            "║                       *      .                 |                               ║\n"
            "║                              +                 |                               ║\n"
            "║                     .        |                *+W+-*                           ║\n"
            "║        .           +y        +W+              . H                 .            ║\n"
            "║     .  +y            |I.   y  |               ! H= .           .  ^            ║\n"
            "║     !   \\     .     |H '. /   |  ___.        .! H  !   +--.--y !  V            ║\n"
            "║     !    \\     \\  +=|H|=='.=+ | |====\\   _  '_H_H__H_. H_/=  J !  !            ║\n"
            "║   . !     \\'    VVV_HHH_/__'._H |  E  \\_|=|_|========|_|==|____H. ! _______.   ║\n"
            "║   I-H_I=I=HH_==_|I_IIIII_I_I_=HH|======.I-I-I-=======-I=I=I=I_=H|=H'===I=I/    ║\n"
            "║   \\                                                                      ,     ║\n"
            "║    |                                                                    /      ║\n"
            "║    .___________________________________________________________________'       ║\n"
            "║                                                                                ║\n"
            "║                         ┌─────────────────────────────┐                        ║\n"
            "║                         │  CONGRATULATION, YOU WON !  │                        ║\n"
            "║                         └─────────────────────────────┘                        ║\n"
            "╟────────────────────────────────────────────────────────────────────────────────╢\n");
}


void show_defeat_menu(){
    fifty_line_breaks();
    wprintf(L"╔════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                                                                                ║\n"
            "║                                _.-^^---....,,--                                ║\n"
            "║                           _--                  --_                             ║\n"
            "║                          <                        >)                           ║\n"
            "║                          |                         |                           ║\n"
            "║                           \\._                   _./                            ║\n"
            "║                              ```--. . , ; .--'''                               ║\n"
            "║                                    | |   |                                     ║\n"
            "║                                 .-=||  | |=-.                                  ║\n"
            "║                                 `-=#$%&%$#=-'                                    ║\n"
            "║                                    | ;  :|                                     ║\n"
            "║                           _____.,-#%&$@%#&#~,._____                               ║\n"
            "║                                                                                ║\n"
            "║                               ┌────────────────┐                               ║\n"
            "║                               │    YOU LOST    │                               ║\n"
            "║                               └────────────────┘                               ║\n"
            "╟────────────────────────────────────────────────────────────────────────────────╢\n");
}

void display_window(int windowID, Grid grid, Boat *boatArray, Inventory inv, int mode, int hitCnt, int DestroyedCnt) {
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
            show_grid(grid, boatArray, inv, mode, hitCnt, DestroyedCnt);
            /*for (int i=0; i<5; i++){
                wprintf(L"%c %d, %d %d\n", boatArray[i].orientation, boatArray[i].size, boatArray[i].row, boatArray[i].col);
            }*/
            break;
        case VICTORY_WINDOW:
            show_victory_menu();
            break;
        case DEFEAT_WINDOW:
            show_defeat_menu();
            break;
    }
}