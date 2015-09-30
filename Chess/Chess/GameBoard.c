#include "GameBoard.h"

control* gameSelectedSquare_control;

void GameBoardMainMenu_ButtonClick(control* input)
{
	MainMenu();
}

void GameBoardSave_ButtonClick(control* input)
{
	// TODO: implement
}

void GameBoardSquare_ButtonClick(control* input)
{
	if (gameSelectedSquare_control == NULL)
	{
		SwitchButtonHighlight(input);
		gameSelectedSquare_control = input;
	}
	
	

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}

int StartGame()
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


	DrawSquareButtons(board_node, &GameBoardSquare_ButtonClick);

	DrawBoardGui(board_node);

	int quitButton_x_location = GAMEBOARDBACKGROUND_W - BUTTON_W - 0.5 * MARGIN;
	int quitButton_y_location = GAMEBOARDBACKGROUND_H - BUTTON_H - 1.5 * MARGIN;
	control* quitButton_control = Create_Button_from_bmp(
		BUTTONQUITFILENAME,
		BUTTONQUITFILENAME,
		BUTTONQUITNAME,
		quitButton_x_location,
		quitButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&Quit_ButtonClick);
	UINode* quitButton_node = CreateAndAddNodeToTree(quitButton_control, gameBoarBackground_node);
	AddToListeners(quitButton_control);

	int saveButton_x_location = quitButton_x_location;
	int saveButton_y_location = 2 * MARGIN;
	control* saveButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONSAVEFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONSAVENAME,
		saveButton_x_location,
		saveButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameBoardSave_ButtonClick);
	UINode* saveButton_node = CreateAndAddNodeToTree(saveButton_control, gameBoarBackground_node);
	AddToListeners(saveButton_control);

	int mainMenuButton_x_location = quitButton_x_location;
	int mainMenuButton_y_location = saveButton_y_location + BUTTON_H + 1.5 *MARGIN;
	control* mainMenuButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONMAINMENUFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONMAINMENUNAME,
		mainMenuButton_x_location,
		mainMenuButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameBoardMainMenu_ButtonClick);
	UINode* mainMenuButton_node = CreateAndAddNodeToTree(mainMenuButton_control, gameBoarBackground_node);
	AddToListeners(mainMenuButton_control);

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}
