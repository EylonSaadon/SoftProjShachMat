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



