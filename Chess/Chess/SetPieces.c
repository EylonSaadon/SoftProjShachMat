#include "SetPieces.h"

control* selectedSquare_Control;
control* selectedPiece_Control;

UINode* board_node;

position* GetPosOfSquare(control* square)
{
	position* pos = malloc(sizeof(position));
	pos->col = (square->location_rect->x-MARGIN) / SQUARE_W;
	pos->row = (square->location_rect->y-MARGIN) / SQUARE_H;
	return pos;
}

void PlacePiece()
{
	position* pos = GetPosOfSquare(selectedSquare_Control);
	char piece;

	if (strcmp(selectedPiece_Control->name, WHITE_PAWN_NAME) == 0)
	{
		piece = WHITE_P;
	}
	else if (strcmp(selectedPiece_Control->name, WHITE_ROOK_NAME) == 0)
	{
		piece = WHITE_R;
	}
	else if (strcmp(selectedPiece_Control->name, WHITE_BISHOP_NAME) == 0)
	{
		piece = WHITE_B;
	}
	else if (strcmp(selectedPiece_Control->name, WHITE_KNIGHT_NAME) == 0)
	{
		piece = WHITE_N;
	}
	else if (strcmp(selectedPiece_Control->name, WHITE_QUEEN_NAME) == 0)
	{
		piece = WHITE_Q;
	}
	else if (strcmp(selectedPiece_Control->name, WHITE_KING_NAME) == 0)
	{
		piece = WHITE_K;
	}
	if (strcmp(selectedPiece_Control->name, BLACK_PAWN_NAME) == 0)
	{
		piece = BLACK_P;
	}
	else if (strcmp(selectedPiece_Control->name, BLACK_ROOK_NAME) == 0)
	{
		piece = BLACK_R;
	}
	else if (strcmp(selectedPiece_Control->name, BLACK_BISHOP_NAME) == 0)
	{
		piece = BLACK_B;
	}
	else if (strcmp(selectedPiece_Control->name, BLACK_KNIGHT_NAME) == 0)
	{
		piece = BLACK_N;
	}
	else if (strcmp(selectedPiece_Control->name, BLACK_QUEEN_NAME) == 0)
	{
		piece = BLACK_Q;
	}
	else if (strcmp(selectedPiece_Control->name, BLACK_KING_NAME) == 0)
	{
		piece = BLACK_K;
	}
	else if (strcmp(selectedPiece_Control->name, DELETE_NAME) == 0)
	{
		piece = EMPTY;
	}

	board[pos->col][BOARD_SIZE - 1 - pos->row] = piece;
	free(pos);
}



void SetPiecesBoardSquare_ButtonClick(control* input)
{ 
	if (selectedSquare_Control != NULL)
	{
		SwitchButtonHighlight(selectedSquare_Control);
	}
	else{
		selectedSquare_Control = input;
		if (selectedPiece_Control != NULL)
		{
			PlacePiece();
			SetPiecesWindow();
		}
		else
		{
			SwitchButtonHighlight(input);
		}
	}

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}

void SetPiecesSidePanelPiece_ButtonClick(control* input)
{
	if (selectedPiece_Control!= NULL)
	{
		SwitchButtonHighlight(selectedPiece_Control);
	}
	else{
		selectedPiece_Control = input;
		if (selectedSquare_Control != NULL)
		{
			PlacePiece();
			SetPiecesWindow();
		}
		else
		{
			SwitchButtonHighlight(input);
		}
	}

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}

void SetPiecesCancel_ButtonClick(control* input)
{
	if (curSettings->game_mode == PLAYER_VS_AI_GAME_MODE)
	{
		AISetting();
	}
	else
	{
		SettingMenu();
	}
}

void SetPiecesStart_ButtonClick(control* input)
{
	if (is_valid_board_init(board)) {
		StartGame();
	}
}

void DrawBoardGui()
{
	int i, j;
	for (j = (BOARD_SIZE - 1); j >= 0; j--)
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
					(BOARD_H - MARGIN - (j+1)*SQUARE_W),
					(Uint16)SQUARE_W,
					(Uint16)SQUARE_H);
				UINode* chessPiece_node = CreateAndAddNodeToTree(chessPiece_control, board_node);
			}
		}
	}
}

void DrawPiecesOnSidePanel(UINode* panel_node)
{
	char* Pieces = "mrnbqkMRNBQK ";
	for (int i = 0; i < 13; i++)
	{
		char* fileName = NULL;
		char* name = NULL;
		switch (Pieces[i])
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
		case(' ') :
			fileName = DELETE_FILENAME;
			name = DELETE_NAME;
			break;
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
				&SetPiecesSidePanelPiece_ButtonClick);
			UINode* chessPiece_node = CreateAndAddNodeToTree(chessPiece_control, panel_node);
			AddToListeners(chessPiece_control);
		}
	}

}



void SetPiecesWindow()
{
	FreeTree(tree);
	EventHandler_init(&Quit);

	selectedSquare_Control = NULL;
	selectedPiece_Control = NULL;

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
	board_node = CreateAndAddNodeToTree(board_control, tree);


	DrawSquareButtons();

	DrawBoardGui();

	DrawPiecesOnSidePanel(gameBoarBackground_node);

	int cancelButton_x_location = GAMEBOARDBACKGROUND_W - BUTTON_W - 0.5 * MARGIN;
	int cancelButton_y_location = GAMEBOARDBACKGROUND_H - BUTTON_H - 1.5 * MARGIN;
	control* cancelButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONCANCELFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONCANCELNAME,
		cancelButton_x_location,
		cancelButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&SetPiecesCancel_ButtonClick);
	UINode* cancelButton_node = CreateAndAddNodeToTree(cancelButton_control, gameBoarBackground_node);
	AddToListeners(cancelButton_control);

	int startButton_x_location = cancelButton_x_location;
	int startButton_y_location = cancelButton_y_location - BUTTON_H - 2 * MARGIN;
	control* startButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONSTARTFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONSTARTNAME,
		startButton_x_location,
		startButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&SetPiecesStart_ButtonClick);
	UINode* startButton_node = CreateAndAddNodeToTree(startButton_control, gameBoarBackground_node);
	AddToListeners(startButton_control);

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}

void DrawSquareButtons()
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
				&SetPiecesBoardSquare_ButtonClick);
			UINode* newGameButton_node = CreateAndAddNodeToTree(square, board_node);
			AddToListeners(square);
		}
	}
}
