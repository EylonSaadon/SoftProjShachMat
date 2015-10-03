#ifndef MAINMENU_
#define MAINMENU_

#ifndef GUI_
#include "GUI.h"
#endif

#ifndef SETTINGMENU_
#include "SettingMenu.h"
#endif



// MainMenu Window Defs
#define MAINMENUNAME "MainMenuBackGround"
#define MAINMENUFILENAME "MainMenu2.bmp"

#define MAINMENU_W 800
#define MAINMENU_H 565

#define MAINMENULEFTMARGIN 56
#define MAINMENUTOPMARGIN 142
#define MAINMENUBUTTONMARGIN 33

#define BUTTONNEWGAMENAME "Button_NewGame"
#define BUTTONNEWGAMEFILENAME "Button_NewGame.bmp"
#define BUTTONLOADGAMENAME "Button_LoadGame"
#define BUTTONLOADGAMEFILENAME "Button_LoadGame.bmp"
#define MAINMENU_BUTTONLOCATION_X_CENTER (0.5*MAINMENU_W - 0.5*BUTTON_W)


/////////////////////
// Global Variables//
/////////////////////




/////////////
//Functions//
/////////////

// The Function linked to the New Game button.
void StartNewGame_ButtonClick(control* input);

// The Function linked to the Load Game button.
void LoadGame_ButtonClick(control* input);

// Draws the Main Menu window and creates all the buttons and adds them to the event handler listeners.
int MainMenu();

#endif
