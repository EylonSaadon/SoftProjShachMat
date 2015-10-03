#ifndef UIFRAMEWORK_
#define UIFRAMEWORK_

#ifndef DATA_STRUCTURES_
#include "Data_Structures.h"
#endif


#define WINDOWTYPE "window"
#define PANELTYPE "panel"
#define BUTTONTYPE "button"


//Functions
#include "UIFrameWork.h"

int LoadBMP(char* fileName, SDL_Surface** surface, char** error);

int CreateControl(SDL_Surface* Button_Background, SDL_Surface* Button_Background_Highlighted, SDL_Rect* Button_Rect, char* name, ButtonAction action, char* type, control** control_ret, char** error);

int Create_window(int window_w, int window_h, control** control_toRet, char** error);

int Create_panel_from_bmp(char* background_filename, char* name, Sint16 x_location, Sint16 y_location, Uint16 picture_width, Uint16 picture_height, control** control_toRet, char** error);

int Create_Button_from_bmp(char* background_filename, char* background_filename_highlighted, char* name, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr, control** control_toRet, char** error);

int HighlightButtonSurface(SDL_Surface* button_surface, SDL_Surface* button_highlighted_transparent, char** error);

int Create_Button_from_bmp_transHighlight(char* background_filename, char* highligted_transparent_button_filename, char* name, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr, control** control_toRet, char** error);

control* GetRoot(UINode* node);

int DrawTree(UINode* node, char** error);

void FreeControl(control* control);

void FreeTree(UINode* node);

UINode* SearchTreeByName(UINode* node, char* name);
#endif
