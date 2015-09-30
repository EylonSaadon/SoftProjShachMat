#include "GUI.h"

void releaseResouces()
{
	FreeTree(tree);
	FreeEventHandler();
	free(curSettings);
}

void Quit()
{
	releaseResouces();
	guiQuit = 1;
}

void Quit_ButtonClick(control* input)
{
	Quit();
}



void SwitchButtonHighlight(control* input)
{
	if (input->ishighlighted == 0){
		input->ishighlighted = 1;
	}
	else
	{
		input->ishighlighted = 0;
	}
}

void SwitchOffHighlightbyName(char* name){
	UINode* node = SearchTreeByName(tree, name);
	if (node != NULL){
		if (node->control->ishighlighted == 1){
			SwitchButtonHighlight(node->control);
		}
	}
}

void SwitchOnHighlightbyName(char* name)
{
	UINode* node = SearchTreeByName(tree, name);
	if (node != NULL){
		if (node->control->ishighlighted == 0){
			SwitchButtonHighlight(node->control);
		}
	}
}

void Square_ButtonClick(control* input)
{
	SwitchButtonHighlight(input);

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

	control* window = Create_window(BOARD_W, BOARD_H);
	tree = CreateTree(window);

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
				&Square_ButtonClick);
			UINode* newGameButton_node = CreateAndAddNodeToTree(square, board_node);
			AddToListeners(square);
		}
	}

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}



void StartNewGame_ButtonClick(control* input)
{
	curSettings = malloc(sizeof(game_settings));
	curSettings->game_mode = TWO_PLAYERS_GAME_MODE;
	curSettings->minimax_depth = 1;
	curSettings->next_turn = WHITE;
	curSettings->user_color = WHITE;

	SettingMenu();
}

void LoadGame_ButtonClick(control* input)
{
	// TODO: implement
}

int MainMenu()
{
	FreeTree(tree);
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

int main()
{
	/* Initialize SDL and make sure it quits*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	SDL_WM_SetCaption("Chess", NULL);
	MainMenu();

	while (!guiQuit) {
		HandleEvents();
		SDL_Delay(125);
	}

	return 1;
}



