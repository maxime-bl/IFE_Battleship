//
// Created by maxim on 08/05/2021.
//

#include "../header/Dialogs.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* ID:
 * 0 - Main menu
 * 1 - Difficulty choice
 * 2 - Game mode choice
 * 2 - What do you want to do ? (ingame)
 */

void init_dialogs(Dialog *dialogArray) {
    dialogArray[0].question = L"╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[1].question = L"╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[2].question = L"╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[3].question = L"║  What do you want to do next?                                                  ║\n"
                              "║    ► Play (Enter '1')                                                          ║\n"
                              "║    ► Save and Quit (Enter '2')                                                 ║\n"
                              "╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[4].question = L"Default dialog\n";
    dialogArray[5].question = L"Default dialog\n";
    dialogArray[6].question = L"Default dialog\n";
    dialogArray[7].question = L"Default dialog\n";

}


// Prints a dialog and an error message if the last answer was invalid
void show_dialog(int dialogID, int errorCode, Dialog *dialogArray) {
    //insert error code
    if (errorCode){
        wprintf(L"\x1b[97m║                    \x1b[91mThe input is incorrect. Please try again                    \x1b[0m║\n"
                "║                                                                                ║\n");
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
        return 1;
    } else {
        // input was valid
        switch (dialogID) {
            case 0:
            case 1:
            case 2:
                if (answer >= 1 && answer <= 3) {
                    return 0;
                } else {
                    return 2;
                }
            case 3:
            case 7:
            case 8:
                if (answer == 1 || answer == 2) {
                    return 0;
                } else {
                    return 2;
                }
            case 4:
                if (answer >= 1 && answer <= 4) {
                    return 0;
                } else {
                    return 2;
                }
            case 5:
                if (answer >= 97 && answer < 106) {
                    return 0;
                } else {
                    return 2;
                }
            case 6:
                if (answer >= 1 && answer <=10 ) {
                    return 0;
                } else {
                    return 2;
                }
            default:
                return 3;
        }
    }
}



