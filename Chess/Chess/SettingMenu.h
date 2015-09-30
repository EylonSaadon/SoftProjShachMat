#ifndef SETTINGMENU_
#define SETTINGMENU_

#ifndef GUI_
#include "GUI.h"
#endif

#ifndef SETPIECES_
#include "SetPieces.h"
#endif

// GameSettings Window Defs 
#define GAMESETTINGNAME "GameSettingsMenu"
#define GAMESETTINGFILENAME "GameSettingsMenu.bmp"
#define GAMESETTING_W 800
#define GAMESETTING_H 600

#define LABELCHOOSEMODENAME "Label_ChooseMode"
#define LABELCHOOSEMODEFILENAME "Label_ChooseMode.bmp"
#define LABELNEXTPLAYERNAME "Label_NextPlayer"
#define LABELNEXTPLAYERFILENAME "Label_NextPlayer.bmp"
#define LABELSETPIECESNAME "Label_SetPieces"
#define LABELSETPIECESFILENAME "Label_SetPieces.bmp"

#define BUTTONPVCNAME "Button_PlayerVsComputer"
#define BUTTONPVCFILENAME "Button_PlayerVsComputer.bmp"
#define BUTTONPVPNAME "Button_PlayerVsPlayer"
#define BUTTONPVPFILENAME "Button_PlayerVsPlayer.bmp"
#define BUTTONSETPIECESNAME "Button_SetPieces"
#define BUTTONSETPIECESFILENAME "Button_SetPieces.bmp"


#define GAMESETTING_BUTTONLOCATION_X_CENTER (0.5*GAMESETTING_W - 0.5*BUTTON_W)


extern UINode* tree;

extern game_settings* curSettings;

extern int setPieces;

int SettingMenu();

#endif
