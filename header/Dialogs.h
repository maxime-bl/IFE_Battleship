//
// Created by maxim on 08/05/2021.
//

#ifndef IFE_PROJECT_DIALOGS_H
#define IFE_PROJECT_DIALOGS_H

// error codes
#include "Missiles.h"

#define INVALID_INPUT  1
#define OUT_OF_BOUNDS  2
#define UNKNOWN_DIALOG_ID  3
#define OUT_OF_AMMO  4

// dialogs ID
#define MAIN_MENU 0
#define DIFF_MENU  1
#define GAMEMODE_MENU  2
#define PLAY_OR_QUIT  3
#define CHOOSE_MISSILE  4
#define CHOOSE_ROW  5
#define CHOOSE_COLUMN  6


typedef struct {
    int lowestAnswer, highestAnswer;
    unsigned short *question;
} Dialog;

void init_dialogs(Dialog *dialogArray);

void show_dialog(int dialogID, int errorCode, Dialog *dialogArray);

int get_answer();

int check_answer(int answer, int dialogID, Inventory inv);


#endif //IFE_PROJECT_DIALOGS_H
