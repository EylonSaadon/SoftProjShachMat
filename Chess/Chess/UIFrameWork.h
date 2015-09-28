#ifndef UIFRAMEWORK_
#define UIFRAMEWORK_
#include "Data_Structures.h"

#define WINDOWTYPE "window"
#define PANELTYPE "panel"
#define BUTTONTYPE "button"



control* Create_window(int window_w, int window_h);

control* Create_panel_from_bmp(char* background_filename, Sint16 x_location, Sint16 y_location, Uint16 picture_width, Uint16 picture_height);

control* Create_Button_from_bmp(char* background_filename, char* background_filename_highlighted, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr);

void DrawTree(UINode* node);

void FreeControl(control* control);

void FreeTree(UINode* node);

#endif
