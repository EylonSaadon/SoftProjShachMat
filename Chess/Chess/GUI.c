#include "GUI.h"

int quit = 0;
control* window;
UINode* tree;


void releaseResouces()
{
	FreeTree(tree);
	FreeEventHandler();
}

void Quit()
{
	releaseResouces();
	quit = 1;
}


void Quit_ButtonClick(control input)
{
	Quit();
}

void StartNewGame_ButtonClick(control input)
{
	FreeTree(tree);
	EventHandler_init(&Quit);

	control* window = Create_window(WIN_W, WIN_H);
	tree = CreateTree(window);

	control* panel = Create_panel_from_bmp(MAINMENUFILENAME, 0, 0, (Uint16)WIN_W, (Uint16)WIN_H);
	UINode* panel_node = CreateAndAddNodeToTree(panel, tree);

	control* newGameButton = Create_Button_from_bmp(BUTTONNEWGAMEFILENAME, BUTTONNEWGAMEFILENAME, BUTTONLOCATION_X_CENTER, 0.25* WIN_H, (Uint16)BUTTON_W, (Uint16)BUTTON_H, &StartNewGame_ButtonClick);
	UINode* newGameButton_node = CreateAndAddNodeToTree(newGameButton, panel_node);
	AddToListeners(newGameButton);

	control* loadGameButton = Create_Button_from_bmp(BUTTONLOADGAMEFILENAME, BUTTONLOADGAMEFILENAME, BUTTONLOCATION_X_CENTER, 0.50* WIN_H, (Uint16)BUTTON_W, (Uint16)BUTTON_H, &LoadGame_ButtonClick);
	UINode* loadGameButton_node = CreateAndAddNodeToTree(loadGameButton, panel_node);
	AddToListeners(loadGameButton);

	control* quitButton = Create_Button_from_bmp(BUTTONQUITFILENAME, BUTTONQUITFILENAME, BUTTONLOCATION_X_CENTER, 0.75* WIN_H, (Uint16)BUTTON_W, (Uint16)BUTTON_H, &Quit_ButtonClick);
	UINode* quitButton_node = CreateAndAddNodeToTree(quitButton, panel_node);
	AddToListeners(quitButton);

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}

void LoadGame_ButtonClick(control input)
{
	// TODO: implement
}

int MainMenu()
{
	FreeTree(tree);
	EventHandler_init(&Quit);

	control* window = Create_window(WIN_W, WIN_H);
	UINode* tree = CreateTree(window);

	control* panel = Create_panel_from_bmp(MAINMENUFILENAME,0,0, (Uint16)WIN_W, (Uint16)WIN_H);
	UINode* panel_node = CreateAndAddNodeToTree(panel, tree);

	control* newGameButton = Create_Button_from_bmp(BUTTONNEWGAMEFILENAME, BUTTONNEWGAMEFILENAME, BUTTONLOCATION_X_CENTER, 0.25* WIN_H, (Uint16)BUTTON_W, (Uint16)BUTTON_H, &StartNewGame_ButtonClick);
	UINode* newGameButton_node = CreateAndAddNodeToTree(newGameButton, panel_node);
	AddToListeners(newGameButton);

	control* loadGameButton = Create_Button_from_bmp(BUTTONLOADGAMEFILENAME, BUTTONLOADGAMEFILENAME, BUTTONLOCATION_X_CENTER, 0.50* WIN_H, (Uint16)BUTTON_W, (Uint16)BUTTON_H, &LoadGame_ButtonClick);
	UINode* loadGameButton_node = CreateAndAddNodeToTree(loadGameButton, panel_node);
	AddToListeners(loadGameButton);

	control* quitButton = Create_Button_from_bmp(BUTTONQUITFILENAME, BUTTONQUITFILENAME, BUTTONLOCATION_X_CENTER, 0.75* WIN_H, (Uint16)BUTTON_W, (Uint16)BUTTON_H, &Quit_ButtonClick);
	UINode* quitButton_node = CreateAndAddNodeToTree(quitButton, panel_node);
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

	while (!quit) {
		HandleEvents();
	}

	return 1;
}



