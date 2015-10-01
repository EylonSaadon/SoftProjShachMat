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

extern UINode* tree;

extern int setPieces;

extern game_settings* curSettings;

extern char board[BOARD_SIZE][BOARD_SIZE];

void Square_ButtonClick(control input);

void HightlightPosMoves(move_list* move_list);

int isPawnUpgradePossible(move move);

void buildBoardUITree();

void ComputerTurn();

int Game();


#endif
