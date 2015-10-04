#include "SetPieces.h"

int PlacePiece(char** error)
{
	position pos = GetPosOfSquare(selectedSquare_Control);

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
		if (is_valid_set(board, piece, pos, c)){
			set_piece(board, pos, piece);
		}
	}
	else
	{
		set_piece(board, pos, piece);
	}
	return 0;
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
			if (-1 == PlacePiece(&error_global))
			{
				guiQuit = -1;
				return;
			}
			SetPiecesWindow();
			return;
		}
		else
		{
			SwitchButtonHighlight(input);
		}
	}

	// DrawTree
	if (-1 == FlipTree(&error_global))
	{
		guiQuit = -1;
		return;
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
			if (-1 == PlacePiece(&error_global))
			{
				guiQuit = -1;
				return;
			}
			SetPiecesWindow();
			return;
		}
		else
		{
			SwitchButtonHighlight(input);
		}
	}

	// DrawTree
	if (-1 == FlipTree(&error_global))
	{
		guiQuit = -1;
		return;
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
	if (-1 == EventHandler_init(&Quit, &error_global))
	{
		guiQuit = -1;
		return;
	}

	control* window;
	if (-1 == Create_window(GAMEBOARDBACKGROUND_W, GAMEBOARDBACKGROUND_H, &window, &error_global))
	{
		guiQuit = -1;
		return;
	}
	if (-1 == CreateTree(window, &tree, &error_global))
	{
		FreeControl(window);
		guiQuit = -1;
		return;
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
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* gameBoarBackground_node;
	if (-1 == CreateAndAddNodeToTree(gameBoarBackground_control, tree, &gameBoarBackground_node, &error_global))
	{
		FreeControl(gameBoarBackground_control);
		guiQuit = -1;
		return;
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
		&error_global))
	{
		guiQuit = -1;
		return;
	}

	if (-1 == CreateAndAddNodeToTree(board_control, tree, &board_node, &error_global))
	{
		FreeControl(board_control);
		guiQuit = -1;
		return;
	}


	if (-1 == DrawSquareButtons(board_node, &SetPiecesBoardSquare_ButtonClick, &error_global))
	{
		guiQuit = -1;
		return;
	}

	if (-1 == DrawBoardGui(board_node, &error_global))
	{
		guiQuit = -1;
		return;
	}

	if (-1 == DrawPiecesOnSidePanel(gameBoarBackground_node, &SetPiecesSidePanelPiece_ButtonClick, &error_global))
	{
		guiQuit = -1;
		return;
	}

	control* chessPiece_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		DELETE_FILENAME,
		SQUAREBUTTONHIGHLIGHTEDFILENAME,
		DELETE_NAME,
		BOARD_W + MARGIN,
		0,
		(Uint16)SQUARE_W,
		(Uint16)SQUARE_H,
		&SetPiecesSidePanelPiece_ButtonClick,
		&chessPiece_control,
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* chessPiece_node;
	if (-1 == CreateAndAddNodeToTree(chessPiece_control, gameBoarBackground_node, &chessPiece_node, &error_global))
	{
		FreeControl(chessPiece_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(chessPiece_control, &error_global))
	{
		guiQuit = -1;
		return;
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
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* cancelButton_node;
	if (-1 == CreateAndAddNodeToTree(cancelButton_control, gameBoarBackground_node, &cancelButton_node, &error_global))
	{
		FreeControl(cancelButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(cancelButton_control, &error_global))
	{
		guiQuit = -1;
		return;
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
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* startButton_node;
	if (-1 == CreateAndAddNodeToTree(startButton_control, gameBoarBackground_node, &startButton_node, &error_global))
	{
		FreeControl(startButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(startButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	// DrawTree
	if (-1 == FlipTree(&error_global))
	{
		guiQuit = -1;
		return;
	}
}


