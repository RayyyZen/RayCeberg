#include "grid.h"

//This function creates and initialize the grid containing the icebergs of the game
Grid createGrid(WINDOW *win){
    Grid grid={NULL,0,0,0,0};
    int i=0;
    char string[3];

    box(win,0,0);
    mvwprintw(win,2,2,"Choose the height of the grid between %d and %d : ",MINHEIGHT,MAXHEIGHT);
    wrefresh(win);
    mvwgetnstr(win,2,50,string,2);
    //The use of a string rather than an integer is to handle the case where the player enters a character rather than an integer
    grid.M=verifyNumber(string,MINHEIGHT,MAXHEIGHT);

    box(win,0,0);
    mvwprintw(win,4,2,"Choose the width of the grid between %d and %d : ",MINWIDTH,MAXWIDTH);
    wrefresh(win);
    mvwgetnstr(win,4,50,string,2);
    //The use of a string rather than an integer is to handle the case where the player enters a character rather than an integer
    grid.N=verifyNumber(string,MINWIDTH,MAXWIDTH);

    grid.tab=malloc(grid.M*sizeof(Iceberg*));
    if(grid.tab==NULL){
        exit(1);
    }
    for(i=0;i<grid.M;i++){
        grid.tab[i]=malloc(grid.N*sizeof(Iceberg));
        if(grid.tab[i]==NULL){
            exit(i+2);
        }
    }
    return grid;
}

//This function fills the grid containing the icebergs of the game
void fillGrid(Grid *grid, int players){
    int i=0,j=0,k=0,line=0,column=0;
    Fish type[3]={ROTTEN,NORMAL,GOLDEN};

    for(i=0;i<grid->M;i++){
        for(j=0;j<grid->N;j++){
            grid->tab[i][j].nbrplayer=0;
            grid->tab[i][j].fishes=rand()%3+1;
            for(k=0;k<3;k++){
                if(k<grid->tab[i][j].fishes){
                    if(k==0){
                        grid->tab[i][j].fish[k]=type[rand()%3];
                    }
                    else{
                        grid->tab[i][j].fish[k]=type[rand()%2+1];
                        //To avoid having more than 1 ROTTEN fish on an iceberg
                    }
                }
                else{
                    grid->tab[i][j].fish[k]=0;
                }
            }
        }
    }

    for(k=0;k<players;k++){
        do{
            line=rand()%grid->M;
            column=rand()%grid->N;
        }while(grid->tab[line][column].nbrplayer!=0);
        grid->tab[line][column].fishes=1;
        grid->tab[line][column].fish[0]=1;
        grid->tab[line][column].fish[1]=0;
        grid->tab[line][column].fish[2]=0;
        //To make the players start on an iceberg with just one normal fish

        grid->tab[line][column].nbrplayer=k+1;
    }
    grid->x=-1;
    grid->y=-1;
}

//This function checks if a movement to one iceberg to the North West is valid
int checkNorthWest(Grid *grid, int line, int column){
    if(line-(1+(column+1)%2)/2>=0 && column-1>=0 && grid->tab[line-(1+(column+1)%2)/2][column-1].nbrplayer==0 && grid->tab[line-(1+(column+1)%2)/2][column-1].fishes!=0){
        return 1;
    }
    return 0;
}

//This function checks if a movement to one iceberg to the North is valid
int checkNorth(Grid *grid, int line, int column){
    if(line-1>=0 && grid->tab[line-1][column].nbrplayer==0 && grid->tab[line-1][column].fishes!=0){
        return 1;
    }
    return 0;
}

//This function checks if a movement to one iceberg to the North East is valid
int checkNorthEast(Grid *grid, int line, int column){
    if(line-(1+(column+1)%2)/2>=0 && column+1<=grid->N-1 && grid->tab[line-(1+(column+1)%2)/2][column+1].nbrplayer==0 && grid->tab[line-(1+(column+1)%2)/2][column+1].fishes!=0){
        return 1;
    }
    return 0;
}

//This function checks if a movement to one iceberg to the South West is valid
int checkSouthWest(Grid *grid, int line, int column){
    if(line+(1+column%2)/2<=grid->M-1 && column-1>=0 && grid->tab[line+(1+column%2)/2][column-1].nbrplayer==0 && grid->tab[line+(1+column%2)/2][column-1].fishes!=0){
        return 1;
    }
    return 0;
}

//This function checks if a movement to one iceberg to the South is valid
int checkSouth(Grid *grid, int line, int column){
    if(line+1<=grid->M-1 && grid->tab[line+1][column].nbrplayer==0 && grid->tab[line+1][column].fishes!=0){
        return 1;
    }
    return 0;
}

//This function checks if a movement to one iceberg to the South East is valid
int checkSouthEast(Grid *grid, int line, int column){
    if(line+(1+column%2)/2<=grid->M-1 && column+1<=grid->N-1 && grid->tab[line+(1+column%2)/2][column+1].nbrplayer==0 && grid->tab[line+(1+column%2)/2][column+1].fishes!=0){
        return 1;
    }
    return 0;
}

//This function checks if the player can move in at least one of the 6 possible directions
int checkPossibilities(Grid *grid, int line, int column){
    if(checkNorthWest(grid,line,column)==1 || checkNorth(grid,line,column)==1 || checkNorthEast(grid,line,column)==1 ||
       checkSouthWest(grid,line,column)==1 || checkSouth(grid,line,column)==1 || checkSouthEast(grid,line,column)==1){
        return 1;
    }
    return 0;
}

//This function checks if all the players on the grid can move in at least one of the 6 possible directions
int checkAllPossibilities(Grid *grid){
    int i=0,j=0;

    for(i=0;i<grid->M;i++){
        for(j=0;j<grid->N;j++){
            if(grid->tab[i][j].nbrplayer!=0){
                if(checkPossibilities(grid,i,j)!=0){
                    return 1;
                }
            }
        }
    }
    return 0;
}

//This functions checks if the iceberg that the player chose to land on is valid in the North West direction
int validNorthWest(Grid *grid, int line, int column){
    while(line>=0 && column>=0){
        if(checkNorthWest(grid,line,column)==0){
            return 0;
        }
        line=line-(1+(column+1)%2)/2;
        column=column-1;
        if(line==grid->x && column==grid->y){
            return 1;
        }
    }
    return 0;
}

//This functions checks if the iceberg that the player chose to land on is valid in the North direction
int validNorth(Grid *grid, int line, int column){
    while(line>=0){
        if(checkNorth(grid,line,column)==0){
            return 0;
        }
        line=line-1;
        if(line==grid->x && column==grid->y){
            return 1;
        }
    }
    return 0;
}

//This functions checks if the iceberg that the player chose to land on is valid in the North East direction
int validNorthEast(Grid *grid, int line, int column){
    while(line>=0 && column<grid->N){
        if(checkNorthEast(grid,line,column)==0){
            return 0;
        }
        line=line-(1+(column+1)%2)/2;
        column=column+1;
        if(line==grid->x && column==grid->y){
            return 1;
        }
    }
    return 0;
}

//This functions checks if the iceberg that the player chose to land on is valid in the South West direction
int validSouthWest(Grid *grid, int line, int column){
    while(line<grid->M && column>=0){
        if(checkSouthWest(grid,line,column)==0){
            return 0;
        }
        line=line+(1+column%2)/2;;
        column=column-1;
        if(line==grid->x && column==grid->y){
            return 1;
        }
    }
    return 0;
}

//This functions checks if the iceberg that the player chose to land on is valid in the South direction
int validSouth(Grid *grid, int line, int column){
    while(line<grid->M){
        if(checkSouth(grid,line,column)==0){
            return 0;
        }
        line=line+1;
        if(line==grid->x && column==grid->y){
            return 1;
        }
    }
    return 0;
}

//This functions checks if the iceberg that the player chose to land on is valid in the South East direction
int validSouthEast(Grid *grid, int line, int column){
    while(line<grid->M && column<grid->N){
        if(checkSouthEast(grid,line,column)==0){
            return 0;
        }
        line=line+(1+column%2)/2;
        column=column+1;
        if(line==grid->x && column==grid->y){
            return 1;
        }
    }
    return 0;
}

//This function returns the line and the column of the iceberg containing the current player
void searchPlayer(Grid *grid, int currentPlayer, int *line, int *column){
    int i=0,j=0;

    *line=-1;
    *column=-1;
    for(i=0;i<grid->M;i++){
        for(j=0;j<grid->N;j++){
            if(grid->tab[i][j].nbrplayer==currentPlayer){
                *line=i;
                *column=j;
                return;
            }
        }
    }
}