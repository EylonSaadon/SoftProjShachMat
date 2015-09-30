#ifndef EVENTHANDLER_
#define EVENTHANDLER_

#ifndef DATA_STRUCTURES_
#include  "Data_Structures.h"
#endif

#define INITIALlISTENERSSIZE 100

typedef void(*EmptyArgsProcedure)(void);

int EventHandler_init(EmptyArgsProcedure quitFuncPtr);

int CheckIfClicked(control* button, SDL_Event* event);

int AddToListeners(control* buttonToAdd);

int HandleEvents();

void HandleMouseUpEvent(SDL_Event* event);

void FreeEventHandler();

#endif
