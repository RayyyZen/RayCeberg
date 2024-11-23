#ifndef GRID_H
#define GRID_H

#include "library.h"

#define MINHEIGHT 3
#define MAXHEIGHT 5
#define MINWIDTH 3
#define MAXWIDTH 12

//This enumeration contains the type of fishes that the player can encounter in the iceberg
typedef enum{
    ROTTEN=-1,EMPTY=0,NORMAL=1,GOLDEN=2
}Fish;

typedef struct{
    Fish fish[3];//An array of the 3 fishes that are on an iceberg
    int fishes;//The number of fishes on an iceberg
    int nbrplayer;//The player that is on an iceberg
}Iceberg;

typedef struct{
    Iceberg **tab;//The array that will contain all the icebergs
    int M;//Height
    int N;//Width
    int x;//Line
    int y;//Column
}Grid;

Grid createGrid(WINDOW *win);
void fillGrid(Grid *grid, int players);
int checkNorthWest(Grid *grid, int line, int column);
int checkNorth(Grid *grid, int line, int column);
int checkNorthEast(Grid *grid, int line, int column);
int checkSouthWest(Grid *grid, int line, int column);
int checkSouth(Grid *grid, int line, int column);
int checkSouthEast(Grid *grid, int line, int column);
int checkPossibilities(Grid *grid, int line, int column);
int checkAllPossibilities(Grid *grid);
int validNorthWest(Grid *grid, int line, int column);
int validNorth(Grid *grid, int line, int column);
int validNorthEast(Grid *grid, int line, int column);
int validSouthWest(Grid *grid, int line, int column);
int validSouth(Grid *grid, int line, int column);
int validSouthEast(Grid *grid, int line, int column);
void searchPlayer(Grid *grid, int currentPlayer, int *line, int *column);

#endif