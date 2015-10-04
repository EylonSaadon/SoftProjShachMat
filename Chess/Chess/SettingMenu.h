#ifndef SETTINGMENU_
#define SETTINGMENU_

#ifndef MAINMENU_
#include "MainMenu.h"
#endif

#ifndef AISETTINGS_
#include "AISettings.h"
#endif

#ifndef GAMEBOARD_
#include "GameBoard.h"
#endif

// GameSettings Window Defs 
#define GAMESETTINGNAME "GameSettingsMenu"
#define GAMESETTINGFILENAME "GameSettingsMenu.bmp"
#define GAMESETTING_W 800
#define GAMESETTING_H 565

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

/////////////////////
// Global Variables//
/////////////////////


extern UINode* tree;

extern game_settings* curSettings;

extern int setPieces;



/////////////
//Functions//
/////////////


void ChooseMode_ButtonClick(control* input);

void SetPiece_ButtonClick(control* input);

void NextPlayer_ButtonClick(control* input);

void GameSettingsCancel_ButtonClick(control* input);

void GameSettingsNext_ButtonClick(control* input);

void SettingMenu();

#endif
