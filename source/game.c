#include "game.h"

//This function allows the player to move from an iceberg to another or quit the game by typing some keys on keyboard
int playerMovement(Grid *grid, PlayersInfo *info, WINDOW *win){
    char direction=0;
    int line=0,column=0;

    while(1){
        line=grid->x;
        column=grid->y;
        displayScreen(grid,info,win);
        direction=wgetch(win);
        switch(direction){
            case '\n' :
                return 1;
            case 'l' :
                return 0;
            case 'a' :
                if(checkNorthWest(grid,line,column)==1){
                    grid->x=line-(1+(column+1)%2)/2;
                    grid->y=column-1;
                }
                break;
            case 'z' :
                if(checkNorth(grid,line,column)==1){
                    grid->x=line-1;
                }
                break;
            case 'e' :
                if(checkNorthEast(grid,line,column)==1){
                    grid->x=line-(1+(column+1)%2)/2;
                    grid->y=column+1;
                }
                break;
            case 'q' :
                if(checkSouthWest(grid,line,column)==1){
                    grid->x=line+(1+column%2)/2;
                    grid->y=column-1;
                }
                break;
            case 's' :
                if(checkSouth(grid,line,column)==1){
                    grid->x=line+1;
                }
                break;
            case 'd' :
                if(checkSouthEast(grid,line,column)==1){
                    grid->x=line+(1+column%2)/2;
                    grid->y=column+1;
                }
                break;
        }
    }
}



//This function simulates the turn of the current player
int playerTurn(Grid *grid, PlayersInfo *info, WINDOW *win){
    int movement=0,px=0,py=0,validMovement=0;
    Iceberg empty={{0},0,0};

    do{
        werase(win);
        searchPlayer(grid,info->currentPlayer,&px,&py);
        if(checkPossibilities(grid,px,py)==0){
            return 1;
        }
        grid->x=px;
        grid->y=py;
        movement=playerMovement(grid,info,win);
        if(movement==0){
            return 0;
        }
        else if(movement==1){
            if(validNorthWest(grid,px,py)==1 || validNorth(grid,px,py)==1 || validNorthEast(grid,px,py)==1 ||
               validSouthWest(grid,px,py)==1 || validSouth(grid,px,py)==1 || validSouthEast(grid,px,py)==1){
                grid->tab[grid->x][grid->y].nbrplayer=info->currentPlayer;
                info->player[info->currentPlayer-1].score+=grid->tab[px][py].fish[0]+grid->tab[px][py].fish[1]+grid->tab[px][py].fish[2];
                grid->tab[px][py]=empty;
                validMovement=1;
            }
        }
    }while(validMovement==0);

    return 1;
}