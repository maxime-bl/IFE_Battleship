#ifndef IFE_PROJECT_DIALOGS_H
#define IFE_PROJECT_DIALOGS_H

#include "Missiles.h"

// Error codes
#define INVALID_INPUT  1
#define OUT_OF_BOUNDS  2
#define UNKNOWN_DIALOG_ID  3
#define OUT_OF_AMMO  4
#define SAVING_ERROR 5
#define NO_SAVEFILE 6
#define LOADING_ERROR 7


// dialogs ID
#define MAIN_MENU 0
#define DIFF_MENU  1
#define GAMEMODE_MENU  2
#define PLAY_OR_QUIT  3
#define CHOOSE_MISSILE  4
#define CHOOSE_ROW  5
#define CHOOSE_COLUMN  6
#define RESTART 7


typedef struct {
    int lowestAnswer, highestAnswer;
    unsigned short *question;
} Dialog;

/* Sets the text to display for each of the dialog
 * - Dialog *dialogArray : array which contains all the dialogs */
void init_dialogs(Dialog *dialogArray);

/* Function that displays a dialog, and eventually an error message
 * - int dialogID : index of the dialog to display in the dialog array
 * - int errorCode : code of the error to display
 * - Dialog *dialogArray : array which contains all the dialogs
 * If the given error code is 0, the function will not display any error message */
void show_dialog(int dialogID, int errorCode, Dialog *dialogArray);

/* Waits for the player to answer the dialog, and format its input
 * If the input is letter, returns the ASCII code of the lowercase letter
 * If the input is a number lower or equal to 10, returns the number
 * Returns -1 otherwise */
int get_answer();

/* Checks if the formatted player input matches the possibles answers to the current dialog
 *  * When the player is asked which missiles he wants to shoot, the function checks if there is any ammunition left
 * - int answer : the answer formatted by get_answer
 * - int dialogID : index of the dialog to display in the dialog array
 * - Inventory inv : structures which contains the number of missiles left
 * Returns an error code if the answer is invalid or the wanted missile is out of ammo */
int check_answer(int answer, int dialogID, Inventory inv);


#endif //IFE_PROJECT_DIALOGS_H
