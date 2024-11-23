#include "game.h"
#include "file.h"
#include "menu.h"

int main(){
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    //To remove the mark of the cursor
    clear();
    //To reset the display, and it is essential before every display
    keypad(stdscr,TRUE);
    noecho();
    srand(time(NULL));
    initializeColor();

    WINDOW *win =newwin(MLINES,MCOLUMNS,0,0);
    //To create a new window
    wclear(win);
    keypad(win,TRUE);
    Grid grid;
    PlayersInfo info;
    int choice=0;
    char car=0;

    do{
        werase(win);
        choice=menu(&grid,&info,win);
        if(choice==2){
            wclear(win);
            clear();
            delwin(win);
            endwin();
            return 0;
        }

        while(checkAllPossibilities(&grid)==1){
            if(playerTurn(&grid,&info,win)==0){
                break;
            }
            info.currentPlayer=(info.currentPlayer)%(info.players)+1;
        }

        displayEndScreen(&grid,&info,win);

        if(checkAllPossibilities(&grid)==1){
            saveIcebergs(grid);
            savePlayers(info);
            destroyGrid(&grid);
            free(info.player);
            info.player=NULL;
            saveGame(grid,info);
        }
        else{
            destroyGrid(&grid);
            free(info.player);
            removeSave();
        }

        do{
            car=wgetch(win);
        }while(car!='l' && car!='r');

    }while(car=='r');

    wclear(win);
    clear();
    delwin(win);
    endwin();
    return 0;
}