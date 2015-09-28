#ifndef EVENTHANDLER_
#define EVENTHANDLER_

#include  "Data_Structures.h"

typedef void(*EmptyArgsProcedure)(void);

int EventHandler_init(EmptyArgsProcedure quitFuncPtr);

int CheckIfClicked(control* button, SDL_Event* event);

int AddToListeners(control* buttonToAdd);

int HandleEvents();

void HandleMouseUpEvent(SDL_Event* event);

void FreeEventHandler();

#endif
