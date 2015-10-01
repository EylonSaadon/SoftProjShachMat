#include "GUI.h"

void FreeButtonsBoard()
{
	// might be reduntent since we free the tree and all controls are there;
	/*for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			free(buttonsBoard[i][j]);
		}
	}*/
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		free(buttonsBoard[i]);
	}
	free(buttonsBoard);
	buttonsBoard = NULL;
}

void releaseResouces()
{
	FreeTree(tree);
	FreeEventHandler();
	free(curSettings);
	if (buttonsBoard != NULL){
		FreeButtonsBoard();
	}
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

void start_gui()
{
	/* Initialize SDL and make sure it quits*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	atexit(SDL_Quit);
	buttonsBoard = NULL;
	SDL_WM_SetCaption("Chess", NULL);
	MainMenu();

	while (!guiQuit) {
		HandleEvents();
		SDL_Delay(125);
	}
}



