#include <stdio.h>

#include "../header/Display.h"


 int getMainMenuChoice(){
    int choice=0;
    scanf(" %d", &choice);

    return choice;
}


int main( )
{
    initializeDisplay();
    displayMenu();

    int mainMenuChoice;
    mainMenuChoice = getMainMenuChoice();
}
