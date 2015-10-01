#include "SetPieces.h"

void PlacePiece()
{
	position* pos = GetPosOfSquare(selectedSquare_Control);

	char piece = ResolveLetterFromButtonName(selectedPiece_Control->name);
	COLOR c;
	if ('a' < piece && piece <'z')
	{
		c = WHITE;
	}
	else
	{
		c = BLACK;
	}
	if (piece != ' '){
		if (is_valid_set(board, piece, *pos, c)){
			board[pos->col][pos->row] = piece;
		}
	}
	else
	{
		board[pos->col][pos->row] = piece;
	}
	free(pos);
}


void SetPiecesBoardSquare_ButtonClick(control* input)
{ 
	if (selectedSquare_Control != NULL)
	{
		SwitchButtonHighlight(selectedSquare_Control);
		selectedSquare_Control = NULL;
	}
	else{
		selectedSquare_Control = input;
		if (selectedPiece_Control != NULL)
		{
			PlacePiece();
			SetPiecesWindow();
			return;
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
		selectedPiece_Control = NULL;
	}
	else{
		selectedPiece_Control = input;
		if (selectedSquare_Control != NULL)
		{
			PlacePiece();
			SetPiecesWindow();
			return;
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
	if (is_valid_board_init(board) == true) {
		Game();
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


	DrawSquareButtons(board_node, &SetPiecesBoardSquare_ButtonClick);

	DrawBoardGui(board_node);

	DrawPiecesOnSidePanel(gameBoarBackground_node, &SetPiecesSidePanelPiece_ButtonClick);

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


