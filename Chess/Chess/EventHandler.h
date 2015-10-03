#ifndef EVENTHANDLER_
#define EVENTHANDLER_

#ifndef DATA_STRUCTURES_
#include  "Data_Structures.h"
#endif

#define INITIALlISTENERSSIZE 100

typedef void(*EmptyArgsProcedure)();

int EventHandler_init(EmptyArgsProcedure quitFuncPtr, char** error);

bool CheckIfClicked(control* button, SDL_Event* event);

int AddToListeners(control* buttonToAdd, char** error);

void HandleEvents();

void HandleMouseUpEvent(SDL_Event* event);

void FreeEventHandler();

#endif
