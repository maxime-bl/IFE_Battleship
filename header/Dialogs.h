//
// Created by maxim on 08/05/2021.
//

#ifndef IFE_PROJECT_DIALOGS_H
#define IFE_PROJECT_DIALOGS_H


typedef struct {
    int lowestAnswer, highestAnswer;
    unsigned short *question;
} Dialog;

void init_dialogs(Dialog *dialogArray);

void show_dialog(int dialogID, int errorCode, Dialog *dialogArray);

int get_answer();

int check_answer(int answer, int dialogID);


#endif //IFE_PROJECT_DIALOGS_H
