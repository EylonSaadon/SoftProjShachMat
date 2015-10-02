#ifndef COMMONGAMEBOAD_
#define COMMONGAMEBOAD_

#ifndef GUI_
#include "GUI.h"
#endif


// Game Window Defs 
#define CHESSBOARDNAME "Chess_Board"
#define CHESSBOARDFILENAME "Chess_Board.bmp"
#define BOARD_W 600
#define BOARD_H 600

#define GAMEBOARDBACKGROUNDNAME "GameBoardBackground"
#define GAMEBOARDBACKGROUNDFILENAME "GameBoardBackground.bmp"
#define GAMEBOARDBACKGROUND_W 1000
#define GAMEBOARDBACKGROUND_H 600

#define MARGIN 20
#define ACTUALBOARD_W (BOARD_W-2*MARGIN)
#define ACTUALBOARD_H (BOARD_H-2*MARGIN)

#define SQUAREBUTTONNAME "TransparentSquare"
#define SQUAREBUTTONFILENAME "TransparentSquare.bmp"
#define SQUAREBUTTONHIGHLIGHTEDFILENAME "TransparentSquare_Highlighted.bmp"

#define DELETE_NAME "Chess_Piece_Delete"
#define DELETE_FILENAME "Chess_Piece_Delete.bmp"

#define BUTTONSTARTNAME "Button_Start"
#define BUTTONSTARTFILENAME "Button_Start.bmp"

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

#define LABELBLACKCHECKNAME "Label_BlackCheck"
#define LABELBLACKCHECKFILENAME "Label_BlackCheck.bmp"
#define LABELWHITECHECKNAME "Label_WhiteCheck"
#define LABELWHITECHECKFILENAME "Label_WhiteCheck.bmp"
#define LABELBLACKWINSNAME "Label_BlackWins"
#define LABELBLACKWINSFILENAME "Label_BlackWins.bmp"
#define LABELWHITEWINSNAME "Label_WhiteWins"
#define LABELWHITEWINSFILENAME "Label_WhiteWins.bmp"
#define LABELCHECKMATENAME "Label_CheckMate"
#define LABELCHECKMATEFILENAME "Label_CheckMate.bmp"
#define LABELTIENAME "Label_Tie"
#define LABELTIEFILENAME "Label_Tie.bmp"
#define LABELGAMEOVERNAME "Label_GameOver"
#define LABELGAMEOVERFILENAME "Label_GameOver.bmp"

#define BUTTONBESTMOVENAME "Button_BestMove"
#define BUTTONBESTMOVEFILENAME "Button_BestMove.bmp"

/////////////////////
// Global Variables//
/////////////////////





/////////////
//Functions//
/////////////


position* GetPosOfSquare(control* square);

char* ResolveFileNameFromLetter(char piece);
char* ResolveNameFromLetter(char piece);
char ResolveLetterFromButtonName(char* name);

void DrawSquareButtons(UINode* node, ButtonAction FuncPtr);
void DrawBoardGui(UINode* node);
void DrawPiecesOnSidePanel(UINode* panel_node, ButtonAction FuncPtr);
void DrawPiecesOnSidePanelFilterColor(UINode* panel_node, ButtonAction FuncPtr, COLOR c);
#endif
