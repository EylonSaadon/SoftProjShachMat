#ifndef GUI_
#define GUI_


#ifndef DEFS_
#include "Defs.h"
#endif

#ifndef DATA_STRUCTURES_
#include "Data_Structures.h"
#endif

#ifndef CHESS_
#include "Chess.h"
#endif

#ifndef UIFRAMEWORK_
#include "UIFrameWork.h"
#endif

#ifndef EVENTHANDLER_
#include "EventHandler.h"
#endif

#ifndef MAINMENU_
#include "MainMenu.h"
#endif

#ifndef SETTINGMENU_
#include "SettingMenu.h"
#endif

// GLOBAL
#define BUTTON_W 227
#define BUTTON_H 47
#define BUTTONCANCELNAME "Button_Cancel"
#define BUTTONCANCELFILENAME "Button_Cancel.bmp"
#define BUTTONTRANSPARENTHIGHLIGHTEDFILENAME "TransparentButton_Highlighted.bmp"
#define BUTTONQUITNAME "Button_Quit"
#define BUTTONQUITFILENAME "Button_Quit.bmp"
#define BUTTONSAVENAME "Button_Save"
#define BUTTONSAVEFILENAME "Button_Save.bmp"
#define BUTTONMAINMENUNAME "Button_MainMenu"
#define BUTTONMAINMENUFILENAME "Button_MainMenu.bmp"
#define BUTTONNEXTNAME "Button_Next"
#define BUTTONNEXTFILENAME "Button_Next.bmp"
#define BUTTONBLACKNAME "Button_Black"
#define BUTTONBLACKFILENAME "Button_Black.bmp"
#define BUTTONWHITENAME "Button_White"
#define BUTTONWHITEFILENAME "Button_White.bmp"


static int guiQuit = 0;
control* window;
UINode* tree;

int setPieces;

game_settings* curSettings;

move_list* curMovesList;
move_list* posMovesFromCurPos;
move* chosenMove;

bool gameOver;
bool isUpgrade;
char board[BOARD_SIZE][BOARD_SIZE];
control*** buttonsBoard;

void start_gui();

SDL_Surface* LoadBMP(char* fileName);

void releaseResouces();

void FreeButtonsBoard();

void Quit();

void SwitchButtonHighlight(control* input);

void SwitchOffHighlightbyName(char* name);

void SwitchOnHighlightbyName(char* name);



#endif

