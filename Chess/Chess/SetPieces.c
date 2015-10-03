#include "SetPieces.h"

void PlacePiece()
{
	position* pos;
	if (-1 == GetPosOfSquare(selectedSquare_Control, &pos, &error))
	{
		guiQuit = -1;
	}

	char piece = ResolveLetterFromButtonName(selectedPiece_Control->name);
	COLOR c;
	if ('a' < piece && piece < 'z')
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

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}

void SetPiecesSidePanelPiece_ButtonClick(control* input)
{
	if (selectedPiece_Control != NULL)
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

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
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
	if (-1 == EventHandler_init(&Quit, &error))
	{
		guiQuit = -1;
	}

	control* window;
	if (-1 == Create_window(GAMEBOARDBACKGROUND_W, GAMEBOARDBACKGROUND_H, &window, &error))
	{
		guiQuit = -1;
	}
	if (-1 == CreateTree(window, &tree, &error))
	{
		guiQuit = -1;
	}
	selectedSquare_Control = NULL;
	selectedPiece_Control = NULL;


	control* gameBoarBackground_control;
	if (-1 == Create_panel_from_bmp(
		SETTINGGAMEBOARDBACKGROUNDFILENAME,
		STTINGGAMEBOARDBACKGROUNDNAME,
		0,
		0,
		(Uint16)GAMEBOARDBACKGROUND_W,
		(Uint16)GAMEBOARDBACKGROUND_H,
		&gameBoarBackground_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* gameBoarBackground_node;
	if (-1 == CreateAndAddNodeToTree(gameBoarBackground_control, tree, &gameBoarBackground_node, &error))
	{
		guiQuit = -1;
	}

	control* board_control;
	if (-1 == Create_panel_from_bmp(
		CHESSBOARDFILENAME,
		CHESSBOARDNAME,
		0,
		0,
		(Uint16)BOARD_W,
		(Uint16)BOARD_H,
		&board_control,
		&error))
	{
		guiQuit = -1;
	}

	if (-1 == CreateAndAddNodeToTree(board_control, tree, &board_node, &error))
	{
		guiQuit = -1;
	}


	DrawSquareButtons(board_node, &SetPiecesBoardSquare_ButtonClick);

	DrawBoardGui(board_node);

	DrawPiecesOnSidePanel(gameBoarBackground_node, &SetPiecesSidePanelPiece_ButtonClick);

	control* chessPiece_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		DELETE_FILENAME,
		SQUAREBUTTONHIGHLIGHTEDFILENAME,
		DELETE_NAME,
		BOARD_W +MARGIN,
		0,
		(Uint16)SQUARE_W,
		(Uint16)SQUARE_H,
		&SetPiecesSidePanelPiece_ButtonClick,
		&chessPiece_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* chessPiece_node;
	if (-1 == CreateAndAddNodeToTree(chessPiece_control, gameBoarBackground_node, &chessPiece_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(chessPiece_control, &error))
	{
		guiQuit = -1;
	}


	int cancelButton_x_location = GAMEBOARDBACKGROUND_W - 160 - SQUARE_W - 13;
	int cancelButton_y_location = GAMEBOARDBACKGROUND_H - BUTTON_H - MARGIN;
	control* cancelButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONCANCELFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONCANCELNAME,
		cancelButton_x_location,
		cancelButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&SetPiecesCancel_ButtonClick,
		&cancelButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* cancelButton_node;
	if (-1 == CreateAndAddNodeToTree(cancelButton_control, gameBoarBackground_node, &cancelButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(cancelButton_control, &error))
	{
		guiQuit = -1;
	}

	int startButton_x_location = cancelButton_x_location;
	int startButton_y_location = cancelButton_y_location - BUTTON_H - 1 * MARGIN;
	control* startButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONSTARTFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONSTARTNAME,
		startButton_x_location,
		startButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&SetPiecesStart_ButtonClick,
		&startButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* startButton_node;
	if (-1 == CreateAndAddNodeToTree(startButton_control, gameBoarBackground_node, &startButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(startButton_control, &error))
	{
		guiQuit = -1;
	}

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}


