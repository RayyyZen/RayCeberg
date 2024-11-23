#include "library.h"

//This function activates all the existing color combinations
void initializeColor(){
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);

    init_pair(8, COLOR_BLACK, COLOR_WHITE);
    init_pair(9, COLOR_BLACK,COLOR_RED);
    init_pair(10, COLOR_BLACK,COLOR_BLUE);
    init_pair(11, COLOR_BLACK,COLOR_YELLOW);
    init_pair(12, COLOR_BLACK,COLOR_GREEN);
}

//This function takes a string containing the number chosen by the player as a parameter and transforms it into an integer between the minimum and the maximum
int verifyNumber(char string[3], int min, int max){
    int number=0;
    if(string[1]=='\0'){
        //If the number is on one caracter
        number=string[0]-'0';
    }
    else{
        number=(string[0]-'0')*10+string[1]-'0';
    }

    if(number<min || number>max){
        number=(number+(max-min+1)*1000)%(max-min+1)+min;
        //The +(max-min+1)*1000 is to avoid having a negative value of number
    }
    return number;
}