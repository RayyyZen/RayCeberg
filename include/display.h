#ifndef DISPLAY_H
#define DISPLAY_H

#include "player.h"

void displayEmojiPlayer(int numberPlayer, int line, int column, WINDOW *win);
void displayEmojiFish(Fish typeFish, int line, int column, int isEmpty, WINDOW *win);
void displayGrid(Grid *grid, int currentPlayer, WINDOW *win);
void displayTitle(WINDOW *win);
void displayScreen(Grid *grid, PlayersInfo *info, WINDOW *win);
void displayRanking(PlayersInfo *info, WINDOW *win);
void displayEndScreen(Grid *grid, PlayersInfo *info, WINDOW *win);

#endif