#include "player.h"

//This function creates and initialize the array that contains all the players
PlayersInfo createPlayers(WINDOW *win){
    PlayersInfo info;
    int i=0;
    char string[3];

    box(win,0,0);
    mvwprintw(win,6,2,"Choose the number of players between 2 and 4 : ");
    wrefresh(win);
    mvwgetnstr(win,6,49,string,1);
    info.players=verifyNumber(string,MINPLAYERS,MAXPLAYERS);
    info.currentPlayer=1;

    info.player=malloc(info.players*sizeof(Player));
    if(info.player==NULL){
        exit(10);
    }
    for(i=0;i<info.players;i++){
        info.player[i].score=0;
        box(win,0,0);
        mvwprintw(win,8+2*i,2,"Player %d choose a username : ",i+1);
        wrefresh(win);
        mvwgetnstr(win,8+2*i,31,info.player[i].username,8);
    }
    return info;
}