#include "MainMenu.h"

void StartNewGame_ButtonClick(control* input)
{
	curSettings = malloc(sizeof(game_settings));
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

	SaveLoadMenu();
}

int MainMenu()
{
	releaseResouces();
	InitGlobalVariable();
	EventHandler_init(&Quit);

	control* window = Create_window(MAINMENU_W, MAINMENU_H);
	tree = CreateTree(window);

	control* background_control = Create_panel_from_bmp(
		MAINMENUFILENAME,
		MAINMENUNAME,
		0,
		0,
		(Uint16)MAINMENU_W,
		(Uint16)MAINMENU_H);
	UINode* background_node = CreateAndAddNodeToTree(background_control, tree);

	control* newGameButton = Create_Button_from_bmp(
		BUTTONNEWGAMEFILENAME,
		BUTTONNEWGAMEFILENAME,
		BUTTONNEWGAMENAME,
		MAINMENU_BUTTONLOCATION_X_CENTER,
		0.25* MAINMENU_H,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&StartNewGame_ButtonClick);
	UINode* newGameButton_node = CreateAndAddNodeToTree(newGameButton, background_node);
	AddToListeners(newGameButton);

	control* loadGameButton = Create_Button_from_bmp(
		BUTTONLOADGAMEFILENAME,
		BUTTONLOADGAMEFILENAME,
		BUTTONLOADGAMENAME,
		MAINMENU_BUTTONLOCATION_X_CENTER,
		0.50* MAINMENU_H,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&LoadGame_ButtonClick);
	UINode* loadGameButton_node = CreateAndAddNodeToTree(loadGameButton, background_node);
	AddToListeners(loadGameButton);

	control* quitButton = Create_Button_from_bmp(
		BUTTONQUITFILENAME,
		BUTTONQUITFILENAME,
		BUTTONQUITNAME,
		MAINMENU_BUTTONLOCATION_X_CENTER,
		0.75* MAINMENU_H,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&Quit_ButtonClick);
	UINode* quitButton_node = CreateAndAddNodeToTree(quitButton, background_node);
	AddToListeners(quitButton);

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}