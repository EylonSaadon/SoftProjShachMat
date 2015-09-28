#include "GUI.h"
#include "Data_Structures.h"

control** _listeners;
int _listenersCount;
EmptyArgsProcedure quit_procedure;

int EventHandler_init(EmptyArgsProcedure quitFuncPtr)
{
	FreeEventHandler();
	quit_procedure = quitFuncPtr; 
}

int AddToListeners(control* buttonToAdd)
{
	_listenersCount++;
	// TODO: Check failure
	// TODO: free memory
	_listeners = (control**)realloc(_listeners, sizeof(control*) * _listenersCount);
	_listeners[_listenersCount - 1] = buttonToAdd;
}

//TODO: bool ?
int CheckIfClicked(control* button, SDL_Event* event)
{
	if ((event->button.x < button->location_rect->x + button->location_rect->w) &&
		(event->button.x > button->location_rect->x) &&
		(event->button.y < button->location_rect->y + button->location_rect->h) &&
		(event->button.y > button->location_rect->y)){
		return 1;
	}
	else{
		return 0;
	}
}

int HandleEvents()
{
	SDL_Event e;
	// TODO: Switch case?
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {

			case (SDL_QUIT) :
				quit_procedure();
				return;
			break;
			case (SDL_KEYUP) :
				if (e.key.keysym.sym == SDLK_ESCAPE){
					quit_procedure();
				}
				return;
			break;
			case (SDL_MOUSEBUTTONUP) :
				HandleMouseUpEvent(&e);
				return;
			break;
			default:
			break;
		}
	}
}

void HandleMouseUpEvent(SDL_Event* event)
{
	for (int i = 0; i < _listenersCount; i++)
	{
		if (CheckIfClicked(_listeners[i], event))
		{
			_listeners[i]->Action(_listeners[i]);
			return;
		}
	}
}

void FreeEventHandler()
{
	free(_listeners);
}


