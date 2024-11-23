#ifndef PLAYER_H
#define PLAYER_H

#include "grid.h"

#define MINPLAYERS 2
#define MAXPLAYERS 4

typedef struct{
    int score;//The score of the player
    char username[20];//The name chosen by the player in the game
}Player;

typedef struct{
    Player *player;//The array that contains all the players
    int players;//The number of players in the current game
    int currentPlayer;//The player whose turn it is currently
}PlayersInfo;

PlayersInfo createPlayers(WINDOW *win);

#endif