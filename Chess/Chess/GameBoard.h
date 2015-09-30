#ifndef GAMEBOARD_
#define GAMEBOARD_

#ifndef GUI_
#include "GUI.h"
#endif


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

extern UINode* tree;

extern int setPieces;

extern game_settings* curSettings;

extern char board[BOARD_SIZE][BOARD_SIZE];

void Square_ButtonClick(control input);

int StartGame();


#endif
