#include "CommonGameboard.h"
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


int GetPosOfSquare(control* square, position** pos_ret, char** error)
{
	position* pos = (position*)malloc(sizeof(position));
	if (NULL == pos)
	{
		*pos_ret = NULL;
		*error = "ERROR: Failed allocating memory for position";
		return -1;
	}
	pos->col = (square->location_rect->x - MARGIN) / SQUARE_W;
	pos->row = BOARD_SIZE - 1 - (square->location_rect->y - MARGIN) / SQUARE_H;
	*pos_ret = pos;
	return 0;
}

int initializeButtonsBoard(char** error)
{
	buttonsBoard = malloc(sizeof(control**)*(BOARD_SIZE));
	if (buttonsBoard == NULL)
	{
		*error = "ERROR: Failed allocating memory for ButtonsBoard.";
		return -1;
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		buttonsBoard[i] = malloc(sizeof(control*)*(BOARD_SIZE));
		if (buttonsBoard[i] == NULL)
		{
			*error = "ERROR: Failed allocating memory for ButtonsBoard.";
			return -1;
		}
	}
	return 0;
}

int DrawSquareButtons(UINode* node, ButtonAction FuncPtr, char** error)
{
	if (-1 == initializeButtonsBoard(error))
	{
		return -1;
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			control* square;
			if (-1 == Create_Button_from_bmp(
				SQUAREBUTTONFILENAME,
				SQUAREBUTTONHIGHLIGHTEDFILENAME,
				SQUAREBUTTONNAME,
				MARGIN + (i*SQUARE_W),
				MARGIN + (j*SQUARE_H),
				(Uint16)SQUARE_W,
				(Uint16)SQUARE_H,
				FuncPtr,
				&square,
				error))
			{
				FreeButtonsBoard();
				return -1;
			}
			UINode* square_node;
			if (-1 == CreateAndAddNodeToTree(square, node, &square_node, error))
			{
				FreeButtonsBoard();
				FreeControl(square);
				return -1;
			}
			if (-1 == AddToListeners(square, error))
			{
				FreeTree(square_node);
				FreeButtonsBoard();
				return -1;
			}
			buttonsBoard[i][j] = square;
		}
	}
	return 0;
}

int DrawBoardGui(UINode* node, char** error)
{
	int i, j;
	for (j = (BOARD_SIZE - 1); j >= 0; j--)
	{
		for (i = 0; i < BOARD_SIZE; i++){
			char* fileName = ResolveFileNameFromLetter(board[i][j]);
			char* name = ResolveNameFromLetter(board[i][j]);

			if (fileName != NULL){
				control* chessPiece_control;
				if (-1 == Create_panel_from_bmp(
					fileName,
					name,
					MARGIN + i * SQUARE_W,
					(BOARD_H - MARGIN - (j + 1)*SQUARE_W),
					(Uint16)SQUARE_W,
					(Uint16)SQUARE_H,
					&chessPiece_control,
					error))
				{
					return -1;
				}

				UINode* chessPiece_node;
				if (-1 == CreateAndAddNodeToTree(chessPiece_control, node, &chessPiece_node, error))
				{
					FreeControl(chessPiece_control);
					return -1;
				}
			}
		}
	}
	return 0;
}

int DrawPiecesOnSidePanel(UINode* panel_node, ButtonAction FuncPtr, char** error)
{
	char* Pieces = "mMrRnNbBqQkK";
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
			control* chessPiece_control;
			if (-1 == Create_Button_from_bmp_transHighlight(
				fileName,
				SQUAREBUTTONHIGHLIGHTEDFILENAME,
				name,
				(Sint16)(GAMEBOARDBACKGROUND_W - 160 - SQUARE_W - 13 + (i % 2) * (SQUARE_W + 22)),
				(Sint16)(0.5 * MARGIN + (i / 2) * SQUARE_H),
				(Uint16)SQUARE_W,
				(Uint16)SQUARE_H,
				FuncPtr,
				&chessPiece_control,
				error))
			{
				return -1;
			}
			UINode* chessPiece_node;
			if (-1 == CreateAndAddNodeToTree(chessPiece_control, panel_node, &chessPiece_node, error))
			{
				FreeControl(chessPiece_control);
				return-1;
			}
			if (-1 == AddToListeners(chessPiece_control, error))
			{
				return-1;
			}
		}
	}
	return 0;

}

int  DrawPiecesOnSidePanelFilterColor(UINode* panel_node, ButtonAction FuncPtr, COLOR c, char** error)
{
	char* Pieces = "mrnbq";
	if (c == BLACK)
	{
		Pieces = "MRNBQ";
	}

	for (int i = 0; i < 6; i++)
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
			control* chessPiece_control;
			if (-1 == Create_Button_from_bmp_transHighlight(
				fileName,
				SQUAREBUTTONHIGHLIGHTEDFILENAME,
				name,
				(Sint16)(BOARD_W + MARGIN + (i % 2) * SQUARE_W),
				(Sint16)(0.5 * MARGIN + (i / 2) * SQUARE_H),
				(Uint16)SQUARE_W,
				(Uint16)SQUARE_H,
				FuncPtr,
				&chessPiece_control,
				error))
			{
				return -1;
			}
			UINode* chessPiece_node;
			if (-1 == CreateAndAddNodeToTree(chessPiece_control, panel_node, &chessPiece_node, error))
			{
				FreeControl(chessPiece_control);
				return -1;
			}
			if (-1 == AddToListeners(chessPiece_control, error))
			{
				return -1;
			}
		}
	}
	return 0;

}

