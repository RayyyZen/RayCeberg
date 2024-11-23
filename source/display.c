#include "display.h"

//This function displays the emoji that represents each player
void displayEmojiPlayer(int numberPlayer, int line, int column, WINDOW *win){
    if(numberPlayer==1){
        mvwprintw(win,line,column,"🦞");
    }
    else if(numberPlayer==2){
        mvwprintw(win,line,column,"🐳");
    }
    else if(numberPlayer==3){
        mvwprintw(win,line,column,"🐙");
    }
    else if(numberPlayer==4){
        mvwprintw(win,line,column,"🐊");
    }
}

//This function displays the emoji that represents each type of fish
void displayEmojiFish(Fish typeFish, int line, int column, int isEmpty, WINDOW *win){
    if(isEmpty==1){
        mvwprintw(win,line,column,"🌫");
    }
    else{
        if(typeFish==ROTTEN){
            mvwprintw(win,line,column,"🦈");
        }
        else if(typeFish==NORMAL){
            mvwprintw(win,line,column,"🐟");
        }
        else if(typeFish==GOLDEN){
            mvwprintw(win,line,column,"🐠");
        }
        else{
            mvwprintw(win,line,column,"  ");
        }
    }
}

//This function displays the grid of the game
void displayGrid(Grid *grid, int currentPlayer, WINDOW *win){
    int i=0,j=0,isEmpty=0,line=MLINES/2-(grid->M*4+2)/2,column=MCOLUMNS/2-(grid->N*4-2)/2;
    box(win,0,0);
    mvwprintw(win,line,column,"     ");
    for(j=0;j<grid->N;j++){
        mvwprintw(win,line,column+5+6*j,"%d     ",j+1);
    }
    mvwprintw(win,line+1,column,"    ");
    for(j=0;j<grid->N;j=j+2){
        mvwprintw(win,line+1,column+4+12*(j/2),"____        ");
    }
    for(i=0;i<grid->M;i++){
        mvwprintw(win,line+2+4*i,column,"   ");
        for(j=0;j<grid->N;j=j+2){
            if(grid->tab[i][j].nbrplayer!=0){
                mvwprintw(win,line+2+4*i,column+3+12*(j/2),"/ ");
                displayEmojiPlayer(grid->tab[i][j].nbrplayer,line+2+4*i,column+5+12*(j/2),win);
                mvwprintw(win,line+2+4*i,column+7+12*(j/2)," \\      ");
            }
            else{
                mvwprintw(win,line+2+4*i,column+3+12*(j/2),"/    \\      ");
            }
        }
        if(grid->N%2==0 && i!=0){mvwprintw(win,line+2+4*i,column+3+12*(j/2),"/");}
        mvwprintw(win,line+3+4*i,column,"%d ",i+1);
        for(j=0;j<grid->N-(2*(grid->N%2));j=j+2){
            mvwprintw(win,line+3+4*i,column+2+12*(j/2),"/");
            if(grid->x==i && grid->y==j){
                wattron(win,COLOR_PAIR(8+currentPlayer) | A_BOLD);
            }
            isEmpty=0;
            if(grid->tab[i][j].fish[0]==EMPTY && grid->tab[i][j].fish[1]==EMPTY && grid->tab[i][j].fish[2]==EMPTY){isEmpty=1;}
            displayEmojiFish(grid->tab[i][j].fish[0],line+3+4*i,column+3+12*(j/2),isEmpty,win);
            displayEmojiFish(grid->tab[i][j].fish[1],line+3+4*i,column+5+12*(j/2),isEmpty,win);
            displayEmojiFish(grid->tab[i][j].fish[2],line+3+4*i,column+7+12*(j/2),isEmpty,win);
            wattroff(win,COLOR_PAIR(8+currentPlayer) | A_BOLD);
            mvwprintw(win,line+3+4*i,column+9+12*(j/2),"\\____");
        }
        if(grid->N%2==1){
            mvwprintw(win,line+3+4*i,column+2+12*(j/2),"/");
            if(grid->x==i && grid->y==j){
                wattron(win,COLOR_PAIR(8+currentPlayer) | A_BOLD);
            }
            isEmpty=0;
            if(grid->tab[i][j].fish[0]==EMPTY && grid->tab[i][j].fish[1]==EMPTY && grid->tab[i][j].fish[2]==EMPTY){isEmpty=1;}
            displayEmojiFish(grid->tab[i][j].fish[0],line+3+4*i,column+3+12*(j/2),isEmpty,win);
            displayEmojiFish(grid->tab[i][j].fish[1],line+3+4*i,column+5+12*(j/2),isEmpty,win);
            displayEmojiFish(grid->tab[i][j].fish[2],line+3+4*i,column+7+12*(j/2),isEmpty,win);
            wattroff(win,COLOR_PAIR(8+currentPlayer) | A_BOLD);
            mvwprintw(win,line+3+4*i,column+9+12*(j/2),"\\");
            j+=2;
        }
        else if(grid->N%2==0 && i!=0){mvwprintw(win,line+3+4*i,column+2+12*(j/2),"/");}
        mvwprintw(win,line+4+4*i,column,"  ");
        for(j=0;j<grid->N-1;j=j+2){
            if(grid->tab[i][j+1].nbrplayer!=0){
                mvwprintw(win,line+4+4*i,column+2+12*(j/2),"\\      / ");
                displayEmojiPlayer(grid->tab[i][j+1].nbrplayer,line+4+4*i,column+11+12*(j/2),win);
            }
            else{
                mvwprintw(win,line+4+4*i,column+2+12*(j/2),"\\      /   ");
            }
        }
        if(grid->N%2==0){mvwprintw(win,line+4+4*i,column+2+12*(j/2),"\\");}
        else{mvwprintw(win,line+4+4*i,column+2+12*(j/2),"\\      /    ");}
        mvwprintw(win,line+5+4*i,column,"   ");
        for(j=0;j<grid->N-1;j=j+2){
            mvwprintw(win,line+5+4*i,column+3+12*(j/2),"\\____/");
            if(grid->x==i && grid->y==j+1){
                wattron(win,COLOR_PAIR(8+currentPlayer) | A_BOLD);
            }
            isEmpty=0;
            if(grid->tab[i][j+1].fish[0]==EMPTY && grid->tab[i][j+1].fish[1]==EMPTY && grid->tab[i][j+1].fish[2]==EMPTY){isEmpty=1;}
            displayEmojiFish(grid->tab[i][j+1].fish[0],line+5+4*i,column+9+12*(j/2),isEmpty,win);
            displayEmojiFish(grid->tab[i][j+1].fish[1],line+5+4*i,column+11+12*(j/2),isEmpty,win);
            displayEmojiFish(grid->tab[i][j+1].fish[2],line+5+4*i,column+13+12*(j/2),isEmpty,win);
            wattroff(win,COLOR_PAIR(8+currentPlayer) | A_BOLD);
        }
        if(grid->N%2==1){mvwprintw(win,line+5+4*i,column+3+12*(j/2),"\\____/");}
        else{mvwprintw(win,line+5+4*i,column+3+12*(j/2),"\\");}
    }
    mvwprintw(win,line+2+4*i,column,"        ");
    for(j=0;j<grid->N-(2*(grid->N%2));j=j+2){
        mvwprintw(win,line+2+4*i,column+8+12*(j/2),"\\      /    ");
    }
    mvwprintw(win,line+3+4*i,column,"         ");
    for(j=0;j<grid->N-(2*(grid->N%2));j=j+2){
        mvwprintw(win,line+3+4*i,column+9+12*(j/2),"\\____/      ");
    }
}

//This function displays the title of the game
void displayTitle(WINDOW *win){
    int x=MLINES-11,y=2;
    wattron(win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(win,x,y,   "   ___                      ");
    mvwprintw(win,x+1,y, "  / _ \\___ ___ __           ");
    mvwprintw(win,x+2,y, " / , _/ _ `/ // /           ");
    mvwprintw(win,x+3,y, "/_/|_|\\_,_/\\_, /            ");
    mvwprintw(win,x+4,y, "  _____   /___/             ");
    mvwprintw(win,x+5,y, " / ___/__ / /  ___ _______ _");
    mvwprintw(win,x+6,y, "/ /__/ -_) _ \\/ -_) __/ _ `/");
    mvwprintw(win,x+7,y, "\\___/\\__/_.__/\\__/_/  \\_, / ");
    mvwprintw(win,x+8,y, "                     /___/");
    wattroff(win,COLOR_PAIR(7) | A_BOLD);
}

//This function displays the screen of the game containing the informations of the players, the grid and the title of the game
void displayScreen(Grid *grid, PlayersInfo *info, WINDOW *win){
    int i=0;

    werase(win);
    wattron(win,COLOR_PAIR(info->currentPlayer+1) | A_BOLD);
    mvwprintw(win,2,2,"It's your turn %s !",info->player[info->currentPlayer-1].username);
    wattroff(win,COLOR_PAIR(info->currentPlayer+1) | A_BOLD);

    wattron(win,COLOR_PAIR(6) | A_BOLD);
    mvwprintw(win,4,2,"'ENTER'");
    wattroff(win,COLOR_PAIR(6) | A_BOLD);
    mvwprintw(win,4,10,": Select");

    wattron(win,COLOR_PAIR(6) | A_BOLD);
    mvwprintw(win,6,4,"'l'");
    wattroff(win,COLOR_PAIR(6) | A_BOLD);
    mvwprintw(win,6,10,": Leave");

    for(i=0;i<info->players;i++){
        wattron(win,COLOR_PAIR(i+2) | A_BOLD);
        displayEmojiPlayer(i+1,8+2*i,2,win);
        mvwprintw(win,8+2*i,5,"%s : %d points",info->player[i].username,info->player[i].score);
        wattroff(win,COLOR_PAIR(i+2) | A_BOLD);
    }

    displayGrid(grid,info->currentPlayer,win);
    displayTitle(win);
    wrefresh(win);
}

//This function displays the ranking between the players according to their score
void displayRanking(PlayersInfo *info, WINDOW *win){
    Player *ranking=malloc(info->players*sizeof(Player));
    int *tab=malloc(info->players*sizeof(int));
    //The tab array will contain the color that represents each player
    int i=0,j=0,tmp1=0;
    Player tmp2;

    if(ranking==NULL || tab==NULL){
        exit(20);
    }
    for(i=0;i<info->players;i++){
        ranking[i]=info->player[i];
        tab[i]=i+2;
    }
    for(i=0;i<info->players-1;i++){
        for(j=i;j<info->players;j++){
            if(ranking[j].score>ranking[i].score){
                tmp2=ranking[j];
                ranking[j]=ranking[i];
                ranking[i]=tmp2;

                tmp1=tab[j];
                tab[j]=tab[i];
                tab[i]=tmp1;
            }
        }
    }
    wattron(win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(win,6,2,"Ranking :");
    wattroff(win,COLOR_PAIR(7) | A_BOLD);
    for(i=0;i<info->players;i++){
        wattron(win,COLOR_PAIR(7) | A_BOLD);
        mvwprintw(win,8+2*i,2,"%d.",i+1);
        wattroff(win,COLOR_PAIR(7) | A_BOLD);
        wattron(win,COLOR_PAIR(tab[i]) | A_BOLD);
        displayEmojiPlayer(tab[i]-1,8+2*i,5,win);
        mvwprintw(win,8+2*i,8," %s / %d points",ranking[i].username,ranking[i].score);
        wattroff(win,COLOR_PAIR(tab[i]) | A_BOLD);
    }
    free(ranking);
    free(tab);
}

//This function displays the ending screen that contains the grid of the icebergs and the ranking between the players
void displayEndScreen(Grid *grid, PlayersInfo *info, WINDOW *win){
    werase(win);
    grid->x=-1;
    grid->y=-1;
    displayTitle(win);
    displayGrid(grid,info->currentPlayer,win);

    wattron(win,COLOR_PAIR(6) | A_BOLD);
    mvwprintw(win,2,2,"'r'");
    wattroff(win,COLOR_PAIR(6) | A_BOLD);
    mvwprintw(win,2,6,": Restart");

    wattron(win,COLOR_PAIR(6) | A_BOLD);
    mvwprintw(win,4,2,"'l'");
    wattroff(win,COLOR_PAIR(6) | A_BOLD);
    mvwprintw(win,4,6,": Leave");

    displayRanking(info,win);
    wrefresh(win);
}