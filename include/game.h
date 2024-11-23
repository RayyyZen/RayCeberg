#ifndef GAME_H
#define GAME_H

#include "display.h"

int playerMovement(Grid *grid, PlayersInfo *info, WINDOW *win);
int playerTurn(Grid *grid, PlayersInfo *info, WINDOW *win);

#endif