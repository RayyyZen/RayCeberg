#ifndef LIBRARY_H
#define LIBRARY_H

#define MLINES 30
//Because LINES already exists
#define MCOLUMNS 118
//Because COLUMNS already exists

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

void initializeColor();
int verifyNumber(char string[3], int min, int max);

#endif