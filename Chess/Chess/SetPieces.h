#ifndef SETPIECES_
#define SETPIECES_

#ifndef COMMONGAMEBOARD_
#include "CommonGameboard.h"
#endif

#ifndef SETTINGMENU
#include "SettingMenu.h"
#endif


/////////////////////
// Global Variables//
/////////////////////

extern int guiQuit;

extern control* selectedSquare_Control;
extern control* selectedPiece_Control;

extern UINode* board_node;



/////////////
//Functions//
/////////////


int PlacePiece(char** error);

void SetPiecesWindow();

#endif