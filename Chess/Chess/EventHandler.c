#include "EventHandler.h"

static control** _listeners;
static int _listenersCount;
static int _listenersSize;
static EmptyArgsProcedure quit_procedure;

int EventHandler_init(EmptyArgsProcedure quitFuncPtr, char** error)
{
	FreeEventHandler();
	quit_procedure = quitFuncPtr; 
	_listenersSize = INITIALlISTENERSSIZE;
	_listeners = malloc(sizeof(control*) * _listenersSize);
	if (NULL == _listeners)
	{
		*error = "ERROR: Failed allocating memory in EvenHandler initializing for _listeners,";
		return -1;
	}
	return 0;
}

int AddToListeners(control* buttonToAdd, char** error)
{
	if (_listenersCount == _listenersSize)
	{
		_listenersSize *= 2;
		control** tmp = malloc(sizeof(control*) * (_listenersSize));
		if (NULL == tmp)
		{
			free(_listeners);
			_listeners = NULL;
			*error = "ERROR: Failed allocating memory in EvenHandler initializing for _listeners,";
			return -1;
		}
		for (int i = 0; i < _listenersCount; i++)
		{
			tmp[i] = _listeners[i];
		}
		free(_listeners);
		_listeners = tmp;
	}
	_listenersCount++;
	_listeners[_listenersCount - 1] = buttonToAdd;
	return 0;
}

bool CheckIfClicked(control* button, SDL_Event* event)
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

void HandleEvents()
{
	SDL_Event e;

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
	_listeners = NULL;
	_listenersCount = 0;
}


