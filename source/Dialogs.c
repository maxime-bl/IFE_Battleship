//
// Created by maxim on 08/05/2021.
//

#include "../header/Dialogs.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

void init_dialogs(Dialog *dialogArray) {
    dialogArray[0].question = L"<1> Start a new game\n"
                          "<2> Load an existing game\n"
                          "<3> Quit";
    dialogArray[1].question = L"Choose a difficulty";

}

// Prints a dialog and an error message if the last answer was invalid
void show_dialog(int dialogID, int errorCode, Dialog *dialogArray) {
    //insert error code
    wprintf(L"%s", dialogArray[dialogID].question);

}

// Wait for the player input, get its answer and format it
// Returns -1 if the answer couldn't be formatted
int get_answer() {

}


// check if the answer to the dialog shown is valid and returns an error code (0 if no error)
int check_answer(int dialogID) {
    int errorCode;

    return errorCode;
}

// change to the next dialog if there is no error
void change_dialog_ID(int currentDialogID, int errorCode) {

}
