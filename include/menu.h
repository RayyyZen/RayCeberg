#ifndef MENU_H
#define MENU_H

#include "game.h"
#include "file.h"

#define CHOICES 3

void displayMenu(WINDOW *win, char options[CHOICES][20], int cursor, int existSave);
int movementMenu(WINDOW *win, int *cursor, int existSave);
int choiceMenu(WINDOW *win);
int menu(Grid *grid, PlayersInfo *info, WINDOW *win);

#endif