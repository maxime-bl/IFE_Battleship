#include <stdio.h>

#include "../header/Display.h"


 int mainMenu(){
    int choice=0;
    initializeDisplay();
    displayGrid();
    scanf(" %d", &choice);
    return choice;

}
int main( )
{
    mainMenu();
}
