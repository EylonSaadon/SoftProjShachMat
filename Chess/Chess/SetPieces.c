#include "SetPieces.h"

void SetPiecesSquare_ButtonClick(control* input)
{
	SwitchButtonHighlight(input);

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}

void DrawBoardGui(UINode* boardNode)
{
	int i, j;
	for (j = 0; j < BOARD_SIZE; j++)
	{
		for (i = 0; i < BOARD_SIZE; i++){
			char* fileName = NULL;
			char* name = NULL;
			switch (board[i][j])
			{
			case(WHITE_P) :
				fileName = WHITE_PAWN_FILENAME;
				name = WHITE_PAWN_NAME;
				break;
			case(WHITE_B) :
				fileName = WHITE_BISHOP_FILENAME;
				name = WHITE_BISHOP_NAME;
				break;
			case(WHITE_K) :
				fileName = WHITE_KING_FILENAME;
				name = WHITE_KING_NAME;
				break;
			case(WHITE_N) :
				fileName = WHITE_KNIGHT_FILENAME;
				name = WHITE_KNIGHT_NAME;
				break;
			case(WHITE_Q) :
				fileName = WHITE_QUEEN_FILENAME;
				name = WHITE_QUEEN_NAME;
				break;
			case(WHITE_R) :
				fileName = WHITE_ROOK_FILENAME;
				name = WHITE_ROOK_NAME;
				break;
			case(BLACK_P) :
				fileName = BLACK_PAWN_FILENAME;
				name = BLACK_PAWN_NAME;
				break;
			case(BLACK_B) :
				fileName = BLACK_BISHOP_FILENAME;
				name = BLACK_BISHOP_NAME;
				break;
			case(BLACK_K) :
				fileName = BLACK_KING_FILENAME;
				name = BLACK_KING_NAME;
				break;
			case(BLACK_N) :
				fileName = BLACK_KNIGHT_FILENAME;
				name = BLACK_KNIGHT_NAME;
				break;
			case(BLACK_Q) :
				fileName = BLACK_QUEEN_FILENAME;
				name = BLACK_QUEEN_NAME;
				break;
			case(BLACK_R) :
				fileName = BLACK_ROOK_FILENAME;
				name = BLACK_ROOK_NAME;
				break;
			}
			if (fileName != NULL){
				control* chessPiece_control = Create_panel_from_bmp(
					fileName,
					name,
					MARGIN + i*SQUARE_W,
					MARGIN + j*SQUARE_W,
					(Uint16)SQUARE_W,
					(Uint16)SQUARE_H);
				UINode* chessPiece_node = CreateAndAddNodeToTree(chessPiece_control, boardNode);
			}
		}
	}
}

void DrawPiecesOnSidePanel(UINode* panel_node)
{
	char* whitePieces = "prnbqk";
	char* blackPieces = "PRNBQK";
	for int
	control* chessPiece_control = Create_panel_from_bmp(
		fileName,
		name,
		MARGIN + i*SQUARE_W,
		MARGIN + j*SQUARE_W,
		(Uint16)SQUARE_W,
		(Uint16)SQUARE_H);
	UINode* chessPiece_node = CreateAndAddNodeToTree(chessPiece_control, boardNode);
}

void SetPiecesWindow()
{
	FreeTree(tree);
	EventHandler_init(&Quit);

	control* window = Create_window(GAMEBOARDBACKGROUND_W, GAMEBOARDBACKGROUND_H);
	tree = CreateTree(window);


	control* gameBoarBackground_control = Create_panel_from_bmp(
		GAMEBOARDBACKGROUNDFILENAME,
		GAMEBOARDBACKGROUNDNAME,
		0,
		0,
		(Uint16)GAMEBOARDBACKGROUND_W,
		(Uint16)GAMEBOARDBACKGROUND_H);
	UINode* gameBoarBackground_node = CreateAndAddNodeToTree(gameBoarBackground_control, tree);

	control* board_control = Create_panel_from_bmp(
		CHESSBOARDFILENAME,
		CHESSBOARDNAME,
		0,
		0,
		(Uint16)BOARD_W,
		(Uint16)BOARD_H);
	UINode* board_node = CreateAndAddNodeToTree(board_control, tree);
	

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
				&SetPiecesSquare_ButtonClick);
			UINode* newGameButton_node = CreateAndAddNodeToTree(square, board_node);
			AddToListeners(square);
		}
	}

	DrawBoardGui(board_node);

	DrawPiecesOnSidePanel(gameBoarBackground_node);

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}