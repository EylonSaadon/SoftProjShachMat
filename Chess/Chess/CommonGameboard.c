#include "CommonGameboard.h"

position* GetPosOfSquare(control* square)
{
	position* pos = malloc(sizeof(position));
	pos->col = (square->location_rect->x - MARGIN) / SQUARE_W;
	pos->row = BOARD_SIZE - 1 - (square->location_rect->y - MARGIN) / SQUARE_H;
	return pos;
}
char* ResolveFileNameFromLetter(char piece)
{
	char* fileName = NULL;
	switch (piece)
	{
	case(WHITE_P) :
		fileName = WHITE_PAWN_FILENAME;
		break;
	case(WHITE_B) :
		fileName = WHITE_BISHOP_FILENAME;
		break;
	case(WHITE_K) :
		fileName = WHITE_KING_FILENAME;
		break;
	case(WHITE_N) :
		fileName = WHITE_KNIGHT_FILENAME;
		break;
	case(WHITE_Q) :
		fileName = WHITE_QUEEN_FILENAME;
		break;
	case(WHITE_R) :
		fileName = WHITE_ROOK_FILENAME;
		break;
	case(BLACK_P) :
		fileName = BLACK_PAWN_FILENAME;
		break;
	case(BLACK_B) :
		fileName = BLACK_BISHOP_FILENAME;
		break;
	case(BLACK_K) :
		fileName = BLACK_KING_FILENAME;
		break;
	case(BLACK_N) :
		fileName = BLACK_KNIGHT_FILENAME;
		break;
	case(BLACK_Q) :
		fileName = BLACK_QUEEN_FILENAME;
		break;
	case(BLACK_R) :
		fileName = BLACK_ROOK_FILENAME;
		break;
	}
	return fileName;
}
char* ResolveNameFromLetter(char piece)
{
	char* name = NULL;
	switch (piece)
	{
	case(WHITE_P) :
		name = WHITE_PAWN_NAME;
		break;
	case(WHITE_B) :
		name = WHITE_BISHOP_NAME;
		break;
	case(WHITE_K) :
		name = WHITE_KING_NAME;
		break;
	case(WHITE_N) :
		name = WHITE_KNIGHT_NAME;
		break;
	case(WHITE_Q) :
		name = WHITE_QUEEN_NAME;
		break;
	case(WHITE_R) :
		name = WHITE_ROOK_NAME;
		break;
	case(BLACK_P) :
		name = BLACK_PAWN_NAME;
		break;
	case(BLACK_B) :
		name = BLACK_BISHOP_NAME;
		break;
	case(BLACK_K) :
		name = BLACK_KING_NAME;
		break;
	case(BLACK_N) :
		name = BLACK_KNIGHT_NAME;
		break;
	case(BLACK_Q) :
		name = BLACK_QUEEN_NAME;
		break;
	case(BLACK_R) :
		name = BLACK_ROOK_NAME;
		break;
	}
	return name;
}
char ResolveLetterFromButtonName(char* name)
{
	char piece = 0;
	if (strcmp(name, WHITE_PAWN_NAME) == 0)
	{
		piece = WHITE_P;
	}
	else if (strcmp(name, WHITE_ROOK_NAME) == 0)
	{
		piece = WHITE_R;
	}
	else if (strcmp(name, WHITE_BISHOP_NAME) == 0)
	{
		piece = WHITE_B;
	}
	else if (strcmp(name, WHITE_KNIGHT_NAME) == 0)
	{
		piece = WHITE_N;
	}
	else if (strcmp(name, WHITE_QUEEN_NAME) == 0)
	{
		piece = WHITE_Q;
	}
	else if (strcmp(name, WHITE_KING_NAME) == 0)
	{
		piece = WHITE_K;
	}
	if (strcmp(name, BLACK_PAWN_NAME) == 0)
	{
		piece = BLACK_P;
	}
	else if (strcmp(name, BLACK_ROOK_NAME) == 0)
	{
		piece = BLACK_R;
	}
	else if (strcmp(name, BLACK_BISHOP_NAME) == 0)
	{
		piece = BLACK_B;
	}
	else if (strcmp(name, BLACK_KNIGHT_NAME) == 0)
	{
		piece = BLACK_N;
	}
	else if (strcmp(name, BLACK_QUEEN_NAME) == 0)
	{
		piece = BLACK_Q;
	}
	else if (strcmp(name, BLACK_KING_NAME) == 0)
	{
		piece = BLACK_K;
	}
	else if (strcmp(name, DELETE_NAME) == 0)
	{
		piece = EMPTY;
	}
	return piece;
}



void DrawSquareButtons(UINode* node, ButtonAction FuncPtr)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			control* square = Create_Button_from_bmp(
				SQUAREBUTTONFILENAME,
				SQUAREBUTTONHIGHLIGHTEDFILENAME,
				SQUAREBUTTONNAME,
				MARGIN + (i*SQUARE_W),
				MARGIN + (j*SQUARE_H),
				(Uint16)SQUARE_W,
				(Uint16)SQUARE_H,
				FuncPtr);
			UINode* newGameButton_node = CreateAndAddNodeToTree(square, node);
			AddToListeners(square);
		}
	}
}
void DrawBoardGui(UINode* node)
{
	int i, j;
	for (j = (BOARD_SIZE - 1); j >= 0; j--)
	{
		for (i = 0; i < BOARD_SIZE; i++){
			char* fileName = ResolveFileNameFromLetter(board[i][j]);
			char* name = ResolveNameFromLetter(board[i][j]);

			if (fileName != NULL){
				control* chessPiece_control = Create_panel_from_bmp(
					fileName,
					name,
					MARGIN + i*SQUARE_W,
					(BOARD_H - MARGIN - (j + 1)*SQUARE_W),
					(Uint16)SQUARE_W,
					(Uint16)SQUARE_H);
				UINode* chessPiece_node = CreateAndAddNodeToTree(chessPiece_control, node);
			}
		}
	}
}

void DrawPiecesOnSidePanel(UINode* panel_node, ButtonAction FuncPtr)
{
	char* Pieces = "mrnbqkMRNBQK ";
	for (int i = 0; i < 13; i++)
	{
		char* fileName = ResolveFileNameFromLetter(Pieces[i]);
		char* name = ResolveNameFromLetter(Pieces[i]);

		if (fileName == NULL){
			if (Pieces[i] == ' ') {
				fileName = DELETE_FILENAME;
				name = DELETE_NAME;
			}
		}

		if (fileName != NULL){
			control* chessPiece_control = Create_Button_from_bmp_transHighlight(
				fileName,
				SQUAREBUTTONHIGHLIGHTEDFILENAME,
				name,
				BOARD_W + MARGIN + (i % 2) * SQUARE_W,
				0.5 * MARGIN + (i / 2) * SQUARE_H,
				(Uint16)SQUARE_W,
				(Uint16)SQUARE_H,
				FuncPtr);
			UINode* chessPiece_node = CreateAndAddNodeToTree(chessPiece_control, panel_node);
			AddToListeners(chessPiece_control);
		}
	}

}

