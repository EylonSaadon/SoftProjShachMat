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

// MainMenu Window Defs
#define MAINMENUNAME "MainMenuBackGround"
#define MAINMENUFILENAME "MainMenu.bmp"
#define MAINMENU_W 800
#define MAINMENU_H 600

#define BUTTONNEWGAMENAME "Button_NewGame"
#define BUTTONNEWGAMEFILENAME "Button_NewGame.bmp"
#define BUTTONLOADGAMENAME "Button_LoadGame"
#define BUTTONLOADGAMEFILENAME "Button_LoadGame.bmp"
#define MAINMENU_BUTTONLOCATION_X_CENTER (0.5*MAINMENU_W - 0.5*BUTTON_W)



// Game Window Defs 
#define CHESSBOARDNAME "Chess_Board"
#define CHESSBOARDFILENAME "Chess_Board.bmp"
#define BOARD_W 600
#define BOARD_H 600

#define MARGIN 20
#define ACTUALBOARD_W (BOARD_W-2*MARGIN)
#define ACTUALBOARD_H (BOARD_H-2*MARGIN)

#define SQUAREBUTTONNAME "TransparentSquare"
#define SQUAREBUTTONFILENAME "TransparentSquare.bmp"
#define SQUAREBUTTONHIGHLIGHTEDFILENAME "TransparentSquare_Highlighted.bmp"

#define BLACK_KING_NAME "chess_piece_black_king"
#define BLACK_KING_FILENAME "chess_piece_black_king.bmp"
#define BLACK_QUEEN_NAME "chess_piece_black_queen"
#define BLACK_QUEEN_FILENAME "chess_piece_black_queen.bmp"
#define BLACK_ROOK_NAME "chess_piece_black_rook"
#define BLACK_ROOK_FILENAME "chess_piece_black_rook.bmp"
#define BLACK_PAWN_NAME "chess_piece_black_pawn"
#define BLACK_PAWN_FILENAME "chess_piece_black_pawn.bmp"
#define BLACK_BISHOP_NAME "chess_piece_black_bishop"
#define BLACK_BISHOP_FILENAME "chess_piece_black_bishop.bmp"
#define BLACK_KNIGHT_NAME "chess_piece_black_knight"
#define BLACK_KNIGHT_FILENAME "chess_piece_black_knight.bmp"

#define WHITE_KING_NAME "chess_piece_white_king"
#define WHITE_KING_FILENAME "chess_piece_white_king.bmp"
#define WHITE_QUEEN_NAME "chess_piece_white_queen"
#define WHITE_QUEEN_FILENAME "chess_piece_white_queen.bmp"
#define WHITE_ROOK_NAME "chess_piece_white_rook"
#define WHITE_ROOK_FILENAME "chess_piece_white_rook.bmp"
#define WHITE_PAWN_NAME "chess_piece_white_pawn"
#define WHITE_PAWN_FILENAME "chess_piece_white_pawn.bmp"
#define WHITE_BISHOP_NAME "chess_piece_white_bishop"
#define WHITE_BISHOP_FILENAME "chess_piece_white_bishop.bmp"
#define WHITE_KNIGHT_NAME "chess_piece_white_knight"
#define WHITE_KNIGHT_FILENAME "chess_piece_white_knight.bmp"

#define SQUARE_W 70
#define SQUARE_H 70

static int guiQuit = 0;
control* window;
UINode* tree;

int setPieces;

game_settings* curSettings;

char board[BOARD_W][BOARD_H];

SDL_Surface* LoadBMP(char* fileName);

void releaseResouces();

void Quit();

void Square_ButtonClick(control input);

void StartNewGame_ButtonClick(control input);

void LoadGame_ButtonClick(control input);

void Quit_ButtonClick(control input);

void SwitchButtonHighlight(control* input);

void SwitchOffHighlightbyName(char* name);

void SwitchOnHighlightbyName(char* name);

int MainMenu();

int StartGame();

#endif

