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

#ifndef SETTINGMENU_
#include "SettingMenu.h"
#endif

#ifndef SAVELOADWINDOW_
#include "SaveLoadWindow.h"
#endif


// GLOBAL
#define NUMBUTTON_W 50
#define NUMBUTTON_H 48
#define BESTBUTTON_W 101
#define BESTBUTTON_H 48
#define NUMBUTTONHIGHLIGHTEDFILENAME "Button_NumHighlight.bmp"

#define MARGIN 18

#define BLINKNUM 6

#define BUTTON_W 205
#define BUTTON_H 52
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


/////////////////////
// Global Variables//
/////////////////////

int guiQuit;
char* error_global;

control* window;
UINode* tree;

//GameBoard
control* selectedSquare_Control;
control* selectedPiece_Control;

UINode* board_node;

move_list* curMovesList;
move_list* posMovesFromCurPos;
move* chosenMove;

bool gameOver;
bool check;
bool tie;
bool isUpgrade;
bool showDepthOptions;

char board[BOARD_SIZE][BOARD_SIZE];
control*** buttonsBoard;

//SaveLoad
bool isSaveMode;


//Settings
int setPieces;

game_settings* curSettings;


/////////////
//Functions//
/////////////

// helper
char* concat(char *s1, char *s2);

// Starts the main gui contains the event handleing loop.
void start_gui();

// Releases All resources in an orderly fashion in case of quitting.
void releaseResouces();

// Releases the Buttonboard in an orderly fashion.
void FreeButtonsBoard();

// This is the Function the Event handler calls when the X button at the top right of the window is clicked.
void Quit();

// The Function linked to the alls Quit Buttons across all windows.
void Quit_ButtonClick(control* input);

// Switches the Highlight flag of the control given as an argument.
void SwitchButtonHighlight(control* input);

// Sets the Highlight flag of the control given as an argument to 0.
void SwitchOffHighlightbyName(char* name);

// Sets the Highlight flag of the control given as an argument to 1.
void SwitchOnHighlightbyName(char* name);

// initializtion
void InitGlobalVariable();

// sets the ishighlighted of all the depths potions to 0.
void SwitchOffHighlightAllMinimaxDepths();

int FlipTree(char** error);
#endif

