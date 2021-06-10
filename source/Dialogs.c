#include "../header/Dialogs.h"
#include "../header/Missiles.h"
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
    dialogArray[CHOOSE_ROW].question = L"║  Choose the row of your target (from A to J).                                  ║\n"
                                       "╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[CHOOSE_COLUMN].question = L"║  Choose the column of your target (from 0 to 9).                               ║\n"
                                          "╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[CHOOSE_MISSILE].question = L"║  Which missile do you want to use?                                             ║\n"
                                           "║    ► Artillery missile (Enter '1')                                             ║\n"
                                           "║    ► Tactical missile (Enter '2')                                              ║\n"
                                           "║    ► Bomb (Enter '3')                                                          ║\n"
                                           "║    ► Simple missile (Enter '4')                                                ║\n"
                                           "╚════════════════════════════════════════════════════════════════════════════════╝\n";
    dialogArray[RESTART].question = L"║  Do you want to play again?                                                    ║\n"
                                    "║    ► Press '1' to start a new game                                             ║\n"
                                    "║    ► Press '2' to quit                                                         ║\n"
                                    "╚════════════════════════════════════════════════════════════════════════════════╝\n";

}


void show_dialog(int dialogID, int errorCode, Dialog *dialogArray) {
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
        case NO_SAVEFILE:
            wprintf(L"\x1b[97m║                     \x1b[91mError: There is no save file to load.                      \x1b[0m║\n"
                    "║                                                                                ║\n");
            break;
        default:
            wprintf(L"\x1b[97m║\x1b[91mERROR: the error you caused is not listed. Congratulations, you broke the game  \x1b[0m║\n"
                    "║                                                                                ║\n");
            break;

    }

    wprintf(L"%s", dialogArray[dialogID].question);
}


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


int check_answer(int answer, int dialogID, Inventory inv) {

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
            case RESTART:
                if (answer == 1 || answer == 2) {
                    return 0;
                } else {
                    return OUT_OF_BOUNDS;
                }
            case CHOOSE_MISSILE:
                switch (answer) {
                    case 1:
                        if (inv.artilleryCnt > 0) {
                            return 0;
                        } else {
                            return OUT_OF_AMMO;
                        }
                    case 2:
                        if (inv.tacticalCnt > 0) {
                            return 0;
                        } else {
                            return OUT_OF_AMMO;
                        }
                    case 3:
                        if (inv.bombCnt > 0) {
                            return 0;
                        } else {
                            return OUT_OF_AMMO;
                        }
                    case 4:
                        if (inv.singleCnt > 0) {
                            return 0;
                        } else {
                            return OUT_OF_AMMO;
                        }
                    default:
                        return OUT_OF_BOUNDS;
                }
            case CHOOSE_ROW:
                if (answer >= 97 && answer <= 106) {
                    return 0;
                } else {
                    return OUT_OF_BOUNDS;
                }
            case CHOOSE_COLUMN:
                if (answer >= 0 && answer <= 9) {
                    return 0;
                } else {
                    return OUT_OF_BOUNDS;
                }
            default:
                return UNKNOWN_DIALOG_ID;
        }
    }
}



