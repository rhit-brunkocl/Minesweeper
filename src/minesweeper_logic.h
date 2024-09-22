#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <stdlib.h>
#include <stdbool.h>
#include "minesweeper_logic.h"

#define BOARD_SIZE 8
#define NUM_MINES 10

struct gameState{
    int board[BOARD_SIZE][BOARD_SIZE];
    bool isRevealed[BOARD_SIZE][BOARD_SIZE];
    bool isFlagged[BOARD_SIZE][BOARD_SIZE];
    int numMines;
    int numRevealed;
    bool hasLost;
    bool hasWon;
};

struct gameState* initGame(void);
struct gameState* play(int i, int j);
struct gameState* flag(int i, int j);

#endif 