#ifndef FILE_H
#define FILE_H

#include "game.h"

//This structure is used just to save the game in one file
typedef struct{
    Grid grid;//The grid containing the icebergs of the game
    PlayersInfo info;//The informations of all the players of the game
}Game;

void saveIcebergs(Grid grid);
void savePlayers(PlayersInfo info);
void destroyGrid(Grid *grid);
void saveGame(Grid grid, PlayersInfo info);
void recoverIcebergs(Grid *grid);
void recoverPlayers(PlayersInfo *info);
void recoverGame(Grid *grid, PlayersInfo *info);
void removeSave();

#endif