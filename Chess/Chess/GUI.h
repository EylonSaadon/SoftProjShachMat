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
#define BUTTONNEXTNAME "Button_Next"
#define BUTTONNEXTFILENAME "Button_Next.bmp"
#define BUTTONBLACKNAME "Button_Black"
#define BUTTONBLACKFILENAME "Button_Black.bmp"
#define BUTTONWHITENAME "Button_White"
#define BUTTONWHITEFILENAME "Button_White.bmp"


// Game Window Defs 
#define CHESSBOARDNAME "Chess_Board"
#define CHESSBOARDFILENAME "Chess_Board.bmp"
#define BOARD_W 600
#define BOARD_H 600

#define GAMEBOARDBACKGROUNDNAME "SidePanel"
#define GAMEBOARDBACKGROUNDFILENAME "SidePanel.bmp"
#define GAMEBOARDBACKGROUND_W 900
#define GAMEBOARDBACKGROUND_H 600

#define MARGIN 20
#define ACTUALBOARD_W (BOARD_W-2*MARGIN)
#define ACTUALBOARD_H (BOARD_H-2*MARGIN)

#define SQUAREBUTTONNAME "TransparentSquare"
#define SQUAREBUTTONFILENAME "TransparentSquare.bmp"
#define SQUAREBUTTONHIGHLIGHTEDFILENAME "TransparentSquare_Highlighted.bmp"

#define BLACK_KING_NAME "Chess_Piece_Black_King"
#define BLACK_KING_FILENAME "Chess_Piece_Black_King.bmp"
#define BLACK_QUEEN_NAME "Chess_Piece_Black_Queen"
#define BLACK_QUEEN_FILENAME "Chess_Piece_Black_Queen.bmp"
#define BLACK_ROOK_NAME "Chess_Piece_Black_Rook"
#define BLACK_ROOK_FILENAME "Chess_Piece_Black_Rook.bmp"
#define BLACK_PAWN_NAME "Chess_Piece_Black_Pawn"
#define BLACK_PAWN_FILENAME "Chess_Piece_Black_Pawn.bmp"
#define BLACK_BISHOP_NAME "Chess_Piece_Black_Bishop"
#define BLACK_BISHOP_FILENAME "Chess_Piece_Black_Bishop.bmp"
#define BLACK_KNIGHT_NAME "Chess_Piece_Black_Knight"
#define BLACK_KNIGHT_FILENAME "Chess_Piece_Black_Knight.bmp"

#define WHITE_KING_NAME "Chess_Piece_White_King"
#define WHITE_KING_FILENAME "Chess_Piece_White_King.bmp"
#define WHITE_QUEEN_NAME "Chess_Piece_White_Queen"
#define WHITE_QUEEN_FILENAME "Chess_Piece_White_Queen.bmp"
#define WHITE_ROOK_NAME "Chess_Piece_White_Rook"
#define WHITE_ROOK_FILENAME "Chess_Piece_White_Rook.bmp"
#define WHITE_PAWN_NAME "Chess_Piece_White_Pawn"
#define WHITE_PAWN_FILENAME "Chess_Piece_White_Pawn.bmp"
#define WHITE_BISHOP_NAME "Chess_Piece_White_Bishop"
#define WHITE_BISHOP_FILENAME "Chess_Piece_White_Bishop.bmp"
#define WHITE_KNIGHT_NAME "Chess_Piece_White_Knight"
#define WHITE_KNIGHT_FILENAME "Chess_Piece_White_Knight.bmp"

#define SQUARE_W 70
#define SQUARE_H 70

static int guiQuit = 0;
control* window;
UINode* tree;

int setPieces;

game_settings* curSettings;

char board[BOARD_SIZE][BOARD_SIZE];

SDL_Surface* LoadBMP(char* fileName);

void releaseResouces();

void Quit();

void SwitchButtonHighlight(control* input);

void SwitchOffHighlightbyName(char* name);

void SwitchOnHighlightbyName(char* name);



#endif

