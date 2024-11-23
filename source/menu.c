#include "menu.h"

//This function displays the menu of the game
void displayMenu(WINDOW *win, char options[CHOICES][20], int cursor, int existSave){
    int i=0,j=0,line=MLINES/2-9,column=MCOLUMNS/2-25,nbrlines=17,nbrcolumns=25;

    box(win,0,0);
    for(i=0;i<nbrlines;i++){
        for(j=0;j<nbrcolumns;j++){
            if(i==0 || i==nbrlines-1 || j==0 || j==nbrcolumns-1){
                mvwprintw(win,i+line,2*j+column,"🔳");
            }
        }
    }
    for(i=0;i<CHOICES;i++){
        if(cursor==i){
            wattron(win,COLOR_PAIR(7) | A_BOLD);
            mvwprintw(win,10+4*i,MCOLUMNS/2-12,"💨");
            mvwprintw(win,10+4*i,MCOLUMNS/2-strlen(options[i])/2,"%s",options[i]);
            wattroff(win,COLOR_PAIR(7) | A_BOLD);
        }
        else{
            if(i==1 && existSave==0){
                wattroff(win,COLOR_PAIR(1) | A_BOLD);
                mvwprintw(win,10+4*i,MCOLUMNS/2-strlen(options[i])/2,"%s",options[i]);
                wattron(win,COLOR_PAIR(1) | A_BOLD);
            }
            else{
                wattron(win,COLOR_PAIR(1) | A_BOLD);
                mvwprintw(win,10+4*i,MCOLUMNS/2-strlen(options[i])/2,"%s",options[i]);
                wattroff(win,COLOR_PAIR(1) | A_BOLD);
            }
        }
    }
    wrefresh(win);
}

//This function allows the player to move in the menu
int movementMenu(WINDOW *win, int *cursor, int existSave){
    int car=wgetch(win);
    //The use of an integer rather than a character is because KEY_DOWN, KEY_UP ... are > 255
    switch(car){
        case KEY_DOWN :
        case 's' :
            if(*cursor==0 && existSave==0){
                (*cursor)+=2;
            }
            else if(*cursor<CHOICES-1){
                (*cursor)++;
            }
            return -1;
            break;
        case KEY_UP :
        case 'z' :
            if(*cursor==2 && existSave==0){
                (*cursor)-=2;
            }
            if(*cursor>0){
                (*cursor)--;
            }
            return -1;
            break;
        case '\n' :
            return *cursor;
    }
    return -1;
}

//This function returns the choice that the player chose from the options
int choiceMenu(WINDOW *win){
    char options[CHOICES][20]={"New game","Resume game","Exit"};
    int cursor=0;
    int choice=0,existSave=1;
    FILE *file1=NULL,*file2=NULL,*file3=NULL;

    file1=fopen("structureGame.bin","rb");
    if(file1==NULL){
        existSave=0;
    }
    else{
        fclose(file1);
    }
    file2=fopen("icebergGrid.bin","rb");
    if(file2==NULL){
        existSave=0;
    }
    else{
        fclose(file2);
    }
    file3=fopen("playersInfos.bin","rb");
    if(file3==NULL){
        existSave=0;
    }
    else{
        fclose(file3);
    }
    do{
        werase(win);
        displayTitle(win);
        displayMenu(win,options,cursor,existSave);
        choice=movementMenu(win,&cursor,existSave);
    }while(choice==-1);
    werase(win);
    return cursor;
}

//This function makes the changes in the game depending on the choice of the player in the options
int menu(Grid *grid, PlayersInfo *info, WINDOW *win){
    int choice=choiceMenu(win);
    switch(choice){
        case 0 :
                echo();
                displayTitle(win);
                box(win,0,0);
                keypad(stdscr,FALSE);
                keypad(win,FALSE);
                *grid=createGrid(win);
                *info=createPlayers(win);
                keypad(stdscr,TRUE);
                keypad(win,TRUE);
                fillGrid(grid,info->players);
                noecho();
                break;
        case 1 :
                recoverGame(grid,info);
                recoverIcebergs(grid);
                recoverPlayers(info);
                break;
    }
    return choice;
}