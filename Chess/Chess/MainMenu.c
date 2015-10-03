#include "MainMenu.h"

void StartNewGame_ButtonClick(control* input)
{
	curSettings = malloc(sizeof(game_settings));
	if (NULL == curSettings)
	{
		guiQuit = -1;
		error = "ERROR: Failed allocating memory for gameSettings";
	}

	curSettings->game_mode = TWO_PLAYERS_GAME_MODE;
	curSettings->minimax_depth = 1;
	curSettings->next_turn = WHITE;
	curSettings->user_color = WHITE;

	gameOver = false;

	setPieces = 0;

	init_board(board);
	SettingMenu();
}

void LoadGame_ButtonClick(control* input)
{
	isSaveMode = false;
	gameOver = false;
	setPieces = 0;

	curSettings = malloc(sizeof(game_settings));
	if (NULL == curSettings)
	{
		guiQuit = -1;
		error = "ERROR: Failed allocating memory for gameSettings";
	}
	curSettings->minimax_depth = 1;

	SaveLoadMenu();
}

void MainMenu()
{
	releaseResouces();
	InitGlobalVariable();
	if (-1 == EventHandler_init(&Quit, &error))
	{
		guiQuit = -1;
	}

	control* window;
	if (-1 == Create_window(MAINMENU_W, MAINMENU_H, &window, &error))
	{
		guiQuit = -1;
	}


	if( -1 == CreateTree(window, &tree, &error))
	{
		guiQuit = -1;
	}

	control* background_control;
	if(-1 ==Create_panel_from_bmp(
		MAINMENUFILENAME,
		MAINMENUNAME,
		0,
		0,
		(Uint16)MAINMENU_W,
		(Uint16)MAINMENU_H, &background_control, &error))
	{
		guiQuit = -1;
	}
	UINode* background_node;
	if (-1 == CreateAndAddNodeToTree(background_control, tree, &background_node, &error))
	{
		guiQuit = -1;
	}

	int newGameButton_x_location = MAINMENULEFTMARGIN;
	int newGameButton_y_location = MAINMENUTOPMARGIN;
	control* newGameButton;
	if(-1 == Create_Button_from_bmp(
		BUTTONNEWGAMEFILENAME,
		BUTTONNEWGAMEFILENAME,
		BUTTONNEWGAMENAME,
		newGameButton_x_location,
		newGameButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		StartNewGame_ButtonClick, &newGameButton, &error))
	{
		guiQuit = -1;
	}

	UINode* newGameButton_node;
	if (-1 == CreateAndAddNodeToTree(newGameButton, background_node, &newGameButton_node, &error))
	{
		guiQuit = -1;
	}

	if (-1 == AddToListeners(newGameButton, &error))
	{
		guiQuit = -1;
	}

	int loadGameButton_x_location = newGameButton_x_location;
	int loadGameButton_y_location = newGameButton_y_location + BUTTON_H + MAINMENUBUTTONMARGIN;
	control* loadGameButton;
	if( -1 == Create_Button_from_bmp(
		BUTTONLOADGAMEFILENAME,
		BUTTONLOADGAMEFILENAME,
		BUTTONLOADGAMENAME,
		loadGameButton_x_location,
		loadGameButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&LoadGame_ButtonClick, 
		&loadGameButton, 
		&error))
	{
		guiQuit = -1;
	}

	UINode* loadGameButton_node;
	if (-1 == CreateAndAddNodeToTree(loadGameButton, background_node, &loadGameButton_node, &error))
	{
		guiQuit = -1;
	}
	if( -1 == AddToListeners(loadGameButton, &error))
	{
		guiQuit = -1;
	}

	int quitGameButton_x_location = loadGameButton_x_location;
	int quitGameButton_y_location = loadGameButton_y_location + BUTTON_H + MAINMENUBUTTONMARGIN;
	control* quitButton; 
	if( -1 == Create_Button_from_bmp(
		BUTTONQUITFILENAME,
		BUTTONQUITFILENAME,
		BUTTONQUITNAME,
		quitGameButton_x_location,
		quitGameButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		Quit_ButtonClick, &quitButton, &error))
	{
		guiQuit = -1;
	}
	UINode* quitButton_node;
	if (-1 == CreateAndAddNodeToTree(quitButton, background_node, &quitButton_node, &error))
	{
		guiQuit = -1;
	}
	if(-1 == AddToListeners(quitButton, &error))
	{
		guiQuit = -1;
	}

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}