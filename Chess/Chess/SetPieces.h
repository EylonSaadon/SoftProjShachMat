#ifndef SETPIECES_
#define SETPIECES_

#ifndef COMMONGAMEBOARD_
#include "CommonGameboard.h"
#endif

#ifndef SETTINGMENU
#include "SettingMenu.h"
#endif

extern control* selectedSquare_Control;
extern control* selectedPiece_Control;

extern UINode* board_node;

void PlacePiece();

void SetPiecesWindow();

#endif