#ifndef AISETTINGS_
#define AISETTINGS_

#ifndef SETTINGMENU_
#include "SettingMenu.h"
#endif

#ifndef GAMEBOARD_
#include "GameBoard.h"
#endif

#ifndef SETPIECES_
#include "SetPieces.h"
#endif


// GameSettings Window Defs 
#define AISETTINGNAME "AISettingsMenu"
#define AISETTINGFILENAME "AISettingsMenu.bmp"
#define AISETTING_W 800
#define AISETTING_H 600

#define LABELMINIMAXNAME "Label_MinimaxDepth"
#define LABELMINIMAXFILENAME "Label_MinimaxDepth.bmp"
#define LABELUSERCOLORNAME "Label_UserColor"
#define LABELUSERCOLORFILENAME "Label_UserColor.bmp"



#define BUTTON1NAME "Button_1"
#define BUTTON1FILENAME "Button_1.bmp"
#define BUTTON2NAME "Button_2"
#define BUTTON2FILENAME "Button_2.bmp"
#define BUTTON3NAME "Button_3"
#define BUTTON3FILENAME "Button_3.bmp"
#define BUTTON4NAME "Button_4"
#define BUTTON4FILENAME "Button_4.bmp"
#define BUTTONBESTNAME "Button_Best"
#define BUTTONBESTFILENAME "Button_Best.bmp"

#define AISETTING_BUTTONLOCATION_X_CENTER (0.5*AISETTING_W - 0.5*AISETTING_H)


/////////////////////
// Global Variables//
/////////////////////


extern UINode* tree;



/////////////
//Functions//
/////////////


void UserColor_ButtonClick(control* input);

void AISetting();

#endif