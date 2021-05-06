#include <stdio.h>

 int mainMenu(){
    int choice=0;
    printf("--- BATTLESHIP ---\n\n");
    printf("1 - Start a new game\n");
    printf("2 - Load an existing game\n");
    printf("3 - Quit\n");
    scanf(" %d", &choice);

    return choice;

}
int main( )
{
    mainMenu();
}
