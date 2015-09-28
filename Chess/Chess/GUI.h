#ifndef GUI_
#define GUI_
#include "Data_Structures.h"
#include "UIFrameWork.h"
#include "EventHandler.h"

#define MAINMENUFILENAME "MainMenu.bmp"
#define WIN_W 800
#define WIN_H 600

#define BUTTONNEWGAMEFILENAME "Button_NewGame.bmp"
#define BUTTONLOADGAMEFILENAME "Button_LoadGame.bmp"
#define BUTTONQUITFILENAME "Button_Quit.bmp"
#define BUTTON_W 227
#define BUTTON_H 47
#define BUTTONLOCATION_X_CENTER (0.5*WIN_W - 0.5*BUTTON_W)

#define CHESSBOARDFILENAME "Chess_Board.bmp"
#define BOARD_W 512
#define BOARD_H 512


#define PIECE_W 63
#define PIECE_H 63


void start_gui();

SDL_Surface* LoadBMP(char* fileName);

void StartNewGame_ButtonClick(control input);

void LoadGame_ButtonClick(control input);

void Quit_ButtonClick(control input);

int MainMenu();

#endif

