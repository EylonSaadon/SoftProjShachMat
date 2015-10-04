#ifndef GAMEBOARD_
#define GAMEBOARD_

#ifndef COMMONGAMEBOARD_
#include "CommonGameboard.h"
#endif

#ifndef SETPIECES_
#include "SetPieces.h"
#endif

#ifndef MINIMAX_
#include "Minimax.h"
#endif


/////////////////////
// Global Variables//
/////////////////////


extern UINode* tree;

extern int guiQuit;

extern int setPieces;

extern game_settings* curSettings;

extern char board[BOARD_SIZE][BOARD_SIZE];

control* gameSelectedSquare_control;



/////////////
//Functions//
/////////////

int HighlightBestMove(int blinknum, char** error);

void HightlightPosMoves(move_list* move_list);

bool isPawnUpgradePossible(move move, char piece);

int buildBoardUITree(char** error);

void CheckGameOver();

void switchOffAllButtons();

int ComputerTurn(char** error);

void GameBoardMainMenu_ButtonClick(control* input);

void GameBoardBest_ButtonClick(control * input);

void GameBoardSave_ButtonClick(control* input);

void upgradePieces_ButtonClick(control* input);

void GameMinimaxDepth_ButtonClick(control* input);

void GameBoardSquare_ButtonClick(control* input);

void Game();


#endif
