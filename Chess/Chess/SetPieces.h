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

void SetPiecesBoardSquare_ButtonClick(control* input);

void SetPiecesSidePanelPiece_ButtonClick(control* input);

void SetPiecesCancel_ButtonClick(control* input);

void SetPiecesStart_ButtonClick(control* input);

void SetPiecesWindow();

#endif