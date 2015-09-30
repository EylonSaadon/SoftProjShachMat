#ifndef GAMEBOARD_
#define GAMEBOARD_

#ifndef COMMONGAMEBOARD_
#include "CommonGameboard.h"
#endif

#ifndef SETPIECES_
#include "SetPieces.h"
#endif

extern UINode* tree;

extern int setPieces;

extern game_settings* curSettings;

extern char board[BOARD_SIZE][BOARD_SIZE];

void Square_ButtonClick(control input);

int StartGame();


#endif
