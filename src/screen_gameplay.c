/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "minesweeper_logic.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
Rectangle board[8][8];
struct gameState* g;
Texture2D mine;
Texture2D tile;
Texture2D revealed;
Texture2D flagTex;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    g = initGame();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j].x = 50+i*100;
            board[i][j].y = 50+j*100;
            board[i][j].width = 90;
            board[i][j].height = 90;
        }
    }
    mine = LoadTexture("resources/Mine.png");
    mine.width = 90;
    mine.height = 90;
    flagTex = LoadTexture("resources/Flag.png");
    flagTex.width = 90;
    flagTex.height = 90;
    tile = LoadTexture("resources/Tile.png");
    tile.width = 90;
    tile.height = 90;
    revealed = LoadTexture("resources/Clicked Tile.png");
    revealed.width = 90;
    revealed.height = 90;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    // Press enter or tap to change to ENDING screen
    if(g->hasWon || IsKeyPressed(KEY_ENTER)){
        finishScreen = 1;
        PlaySound(fxCoin);
    }else if(!g->hasLost){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 mousePoint = GetMousePosition();
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(CheckCollisionPointRec(mousePoint, board[i][j])){
                        g = play(i, j);
                    }
                }
            }
        }else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            Vector2 mousePoint = GetMousePosition();
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(CheckCollisionPointRec(mousePoint, board[i][j])){
                        g = flag(i, j);
                    }
                }
            }
        }
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(g->isRevealed[i][j]){
                if(g->board[i][j] == -1){
                    DrawTexture(revealed, board[i][j].x, board[i][j].y, WHITE);
                    DrawTexture(mine, board[i][j].x, board[i][j].y, WHITE);
                }else{
                    DrawTexture(revealed, board[i][j].x, board[i][j].y, WHITE);
                    char text[2];
                    sprintf(text, "%d", g->board[i][j]);
                    DrawText(text, (int)board[i][j].x + 25, (int)board[i][j].y, (int)board[i][j].width, BLACK);
                }
            }else if(g->isFlagged[i][j]){
                DrawTexture(tile, board[i][j].x, board[i][j].y, WHITE);
                DrawTexture(flagTex, board[i][j].x, board[i][j].y, WHITE);
            }else{
                DrawTexture(tile, board[i][j].x, board[i][j].y, WHITE);
            }
        }
    }
}

// Gameplay Screen Unload logic
bool UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    return g->hasWon;
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}