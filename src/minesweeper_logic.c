#include "minesweeper_logic.h"
struct gameState game;

struct gameState* initGame(){
    game.numMines = NUM_MINES;
    game.numRevealed = 0;
    game.hasLost = false;
    game.hasWon = false;
    int i = 0;
    for(int i = 0; i < BOARD_SIZE;i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            game.board[i][j] = 0;
            game.isFlagged[i][j] = false;
            game.isRevealed[i][j] = false;
        }
    }
    while(i < game.numMines){
        int row = rand() % BOARD_SIZE;
        int column = rand() % BOARD_SIZE;
        if(game.board[row][column] != -1){
            game.board[row][column] = -1;
            i++;
        }
    }
    for(i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(game.board[i][j] != -1){
                game.board[i][j] = calculateNumAdjacent(i, j);
            }
        }
    }
    return &game;
}

int calculateNumAdjacent(int i, int j){
    int numAdjacent = 0;
    if(i == 0){
        if(j > 0){
            if(game.board[i][j-1] == -1){
                numAdjacent++;
            }
            if(game.board[i+1][j-1] == -1){
                numAdjacent++;
            }
        }
        if(game.board[i+1][j] == -1){
            numAdjacent++;
        }
        if(j < BOARD_SIZE-1){
            if(game.board[i+1][j+1] == -1){
                numAdjacent++;
            }
            if(game.board[i][j+1] == -1){
                numAdjacent++;
            }
        }
    }else if(i == BOARD_SIZE - 1){
        if(game.board[i-1][j-1] == -1){
            numAdjacent++;
        }
        if(game.board[i-1][j] == -1){
            numAdjacent++;
        }
        if(game.board[i-1][j+1] == -1){
            numAdjacent++;
        }
        if(game.board[i][j-1] == -1){
            numAdjacent++;
        }
        if(game.board[i][j+1] == -1){
            numAdjacent++;
        }
    }else{
        if(game.board[i-1][j] == -1){
            numAdjacent++;
        }
        if(game.board[i+1][j] == -1){
            numAdjacent++;
        }
        if(j != 0){
            if(game.board[i][j-1] == -1){
                numAdjacent++;
            }
            if(game.board[i-1][j-1] == -1){
                numAdjacent++;
            }
            if(game.board[i+1][j-1] == -1){
                numAdjacent++;
            }
        }
        if(j != BOARD_SIZE-1){
            if(game.board[i-1][j+1] == -1){
                numAdjacent++;
            }
            if(game.board[i][j+1] == -1){
                numAdjacent++;
            }
            if(game.board[i+1][j+1] == -1){
                numAdjacent++;
            }
        }
    }
    return numAdjacent;
}

void playAllAdjacent(int i, int j){
    if(i == 0){
        if(j > 0){
            if(game.isRevealed[i][j-1] == false){
                play(i, j-1);
            }
        }
        if(game.isRevealed[i+1][j] == false){
            play(i+1, j);
        }
        if(j < BOARD_SIZE-1){
            if(game.isRevealed[i][j+1] == false){
                play(i, j+1);
            }
        }
    }else if(i == BOARD_SIZE - 1){
        if(j != 0){
            if(game.isRevealed[i][j-1] == false){
                play(i, j-1);
            }
        }
        if(game.isRevealed[i-1][j] == false){
            play(i-1, j);
        }
        if(j != BOARD_SIZE-1){
            if(game.isRevealed[i][j+1] == false){
                play(i, j+1);
            }
        }
    }else{
        if(game.isRevealed[i-1][j] == false){
            play(i-1, j);
        }
        if(game.isRevealed[i+1][j] == false){
            play(i+1, j);
        }
        if(j != 0){
            if(game.isRevealed[i][j-1] == false){
                play(i, j-1);
            }
        }
        if(j != BOARD_SIZE-1){
            if(game.isRevealed[i][j+1] == false){
                play(i, j+1);
            }
        }
    }
}

struct gameState* play(int i, int j){
    game.isRevealed[i][j] = true;
    game.numRevealed++;
    if(game.board[i][j] == -1){
        game.hasLost = true;
    }else if(game.numRevealed == BOARD_SIZE * BOARD_SIZE - NUM_MINES){
        game.hasWon = true;
    }

    if(game.board[i][j] == 0){
        playAllAdjacent(i, j);
    }

    return &game;
}

struct gameState* flag(int i, int j){
    game.isFlagged[i][j] = !game.isFlagged[i][j];
    return &game;
}