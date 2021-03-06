#ifndef UIFRAMEWORK_
#define UIFRAMEWORK_

#ifndef DATA_STRUCTURES_
#include "Data_Structures.h"
#endif


#define WINDOWTYPE "window"
#define PANELTYPE "panel"
#define BUTTONTYPE "button"



control* Create_window(int window_w, int window_h);

control* Create_panel_from_bmp(char* background_filename, char* name, Sint16 x_location, Sint16 y_location, Uint16 picture_width, Uint16 picture_height);

control* Create_Button_from_bmp(char* background_filename, char* background_filename_highlighted, char* name, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr);

control* Create_Button_from_bmp_transHighlight(char* background_filename, char* highligted_transparent_button_filename, char* name, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr);

void HighlightButtonSurface(SDL_Surface* button_surface, SDL_Surface* button_highlighted_transparent);

void DrawTree(UINode* node);

void FreeControl(control* control);

void FreeTree(UINode* node);

UINode* SearchTreeByName(UINode* node, char* name);
#endif
