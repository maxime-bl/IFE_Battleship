//
// Created by maxim on 08/05/2021.
//

#include "../header/Dialogs.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void init_dialogs(Dialog *dialogArray) {
    dialogArray[MAIN_MENU].question = L"╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[DIFF_MENU].question = L"╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[GAMEMODE_MENU].question = L"╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[PLAY_OR_QUIT].question = L"║  What do you want to do next?                                                  ║\n"
                                         "║    ► Play (Enter '1')                                                          ║\n"
                                         "║    ► Save and Quit (Enter '2')                                                 ║\n"
                                         "╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[CHOOSE_ROW].question = L"Default dialog\n";
    dialogArray[CHOOSE_COLUMN].question = L"Default dialog\n";
    dialogArray[CHOOSE_MISSILE].question = L"Default dialog\n";
    dialogArray[7].question = L"Default dialog\n";

}


// Prints a dialog and an error message if the last answer was invalid
void show_dialog(int dialogID, int errorCode, Dialog *dialogArray) {
    //insert error code
    switch (errorCode) {
        case 0:
            break;
        case INVALID_INPUT:
            wprintf(L"\x1b[97m║                    \x1b[91mThe input is incorrect. Please try again                    \x1b[0m║\n"
                    "║                                                                                ║\n");
            break;
        case OUT_OF_BOUNDS:
            wprintf(L"\x1b[97m║                   \x1b[91mThis value is not valid. Please try again                    \x1b[0m║\n"
                    "║                                                                                ║\n");
            break;
        case UNKNOWN_DIALOG_ID:
            wprintf(L"\x1b[97m║              \x1b[91mSomething that was not supposed to happen did happen              \x1b[0m║\n"
                    "║                                                                                ║\n");
            break;
        case OUT_OF_AMMO:
            wprintf(L"\x1b[97m║               \x1b[91mThis weapon is out of ammunition. Try another one                \x1b[0m║\n"
                    "║                                                                                ║\n");
            break;
        default:
            wprintf(L"\x1b[97m║\x1b[91mERROR: the error you caused is not listed. Congratulations, you broke the game  \x1b[0m║\n"
                    "║                                                                                ║\n");
            break;

    }

    wprintf(L"%s", dialogArray[dialogID].question);
}


// Wait for the player input, get the answer and format it
// Returns the ASCII code (lowercase) when a letter in entered
// Returns -1 if the answer couldn't be formatted
int get_answer() {
    char input[2];
    fgets(input, 100, stdin);

    int numResult = atoi(input);
    if (numResult == 0 & input[0] != '0') {
        //input is not a number

        if (input[1] == 10) {
            //input is a single char
            if (isalpha(input[0])) {
                //input is a letter
                char charResult = tolower(input[0]);
                return charResult;
            } else {
                //input is not a letter
                return -1;
            }

        } else {
            //multiples non-numeric chars
            return -1;
        }

    } else {
        //input is a number
        if (numResult <= 10) {
            return numResult;
        } else {
            return -1;
        }
    }
}


/* check if the answer to the dialog shown is valid and returns an error code
*  0 = no error
*  1 = invalid input
*  2 = out of bounds
*  3 = unknown dialogID
*  4 = out of ammunition (missile choice)
*/
int check_answer(int answer, int dialogID) {

    if (answer == -1) {
        // input was not an integer or a letter
        return INVALID_INPUT;
    } else {
        // input was valid
        switch (dialogID) {
            case MAIN_MENU:
            case DIFF_MENU:
            case GAMEMODE_MENU:
                if (answer >= 1 && answer <= 3) {
                    return 0;
                } else {
                    return OUT_OF_BOUNDS;
                }
            case PLAY_OR_QUIT:
            case 7:
            case 8:
                if (answer == 1 || answer == 2) {
                    return 0;
                } else {
                    return OUT_OF_BOUNDS;
                }
            case CHOOSE_MISSILE:
                if (answer >= 1 && answer <= 4) {
                    return 0;
                } else {
                    return OUT_OF_BOUNDS;
                }
            case CHOOSE_ROW:
                if (answer >= 97 && answer < 106) {
                    return 0;
                } else {
                    return OUT_OF_BOUNDS;
                }
            case CHOOSE_COLUMN:
                if (answer >= 1 && answer <= 10) {
                    return 0;
                } else {
                    return OUT_OF_BOUNDS;
                }
            default:
                return UNKNOWN_DIALOG_ID;
        }
    }
}



