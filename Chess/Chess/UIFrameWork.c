#include "UIFrameWork.h"


int LoadBMP(char* fileName, SDL_Surface** surface, char** error)
{
	*surface = SDL_LoadBMP(fileName);
	if (*surface != NULL)
	{
		Uint32 green = SDL_MapRGB((*surface)->format, 0, 255, 0);
		SDL_SetColorKey(*surface, SDL_SRCCOLORKEY, green);
		return 0;
	}
	else
	{
		*error = SDL_GetError();
		return -1;
	}
}

int CreateControl(SDL_Surface* control_Background, SDL_Surface* control_Background_Highlighted, SDL_Rect* control_Rect, char* name, ButtonAction action, char* type, control** control_ret, char** error)
{
	*control_ret = (control*)malloc(sizeof(control));
	if (*control_ret == NULL)
	{
		*error = "ERROR: failed to allocate memory for Control";
		return -1;
	}

	(*control_ret)->surface = control_Background;
	(*control_ret)->highlighted_surface = control_Background_Highlighted;
	(*control_ret)->location_rect = control_Rect;
	(*control_ret)->type = type;
	(*control_ret)->Action = action;
	(*control_ret)->ishighlighted = 0;


	if (name != NULL){
		
		(*control_ret)->name = malloc((strlen(name) + 1) * sizeof(char));
		if ((*control_ret)->name == NULL)
		{
			free(*control_ret);
			*control_ret = NULL;
			*error = "ERROR: failed to allocate memory for string";
			return -1;
		}

		for (unsigned int i = 0; i < strlen(name); i++)
		{
			(*control_ret)->name[i] = name[i];
		}
		(*control_ret)->name[strlen(name)] = 0;
	}
	else
	{
		(*control_ret)->name = name;
	}

	return 0;
}

int Create_window(int window_w, int window_h, control** control_toRet, char** error)
{
	SDL_Surface *window = SDL_SetVideoMode(window_w, window_h, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	
	if (window == NULL) {
		*error = SDL_GetError();
		return -1;
	}

	if (-1 == CreateControl(window, NULL, NULL, NULL, NULL, WINDOWTYPE, control_toRet, error))
	{
		SDL_FreeSurface(window);
		window = NULL;
		return -1;
	}
	return 0;
}

int Create_panel_from_bmp(char* background_filename, char* name, Sint16 x_location, Sint16 y_location, Uint16 picture_width, Uint16 picture_height, control** control_toRet, char** error)
{
	SDL_Surface* Panel_Background;

	if ( -1 ==LoadBMP(background_filename, &Panel_Background, error))
	{
		*control_toRet = NULL;
		return -1;
	}

	SDL_Rect* Panel_Rect = malloc(sizeof(SDL_Rect));
	if (Panel_Rect == NULL) {
		SDL_FreeSurface(Panel_Background);
		Panel_Background = NULL;
		*control_toRet = NULL;
		*error = "ERROR: failed to allocate memory for SDL_Rect";
		return -1;
	}
	Panel_Rect->x = x_location;
	Panel_Rect->y = y_location;
	Panel_Rect->h = picture_height;
	Panel_Rect->w = picture_width;

	if (-1 == CreateControl(Panel_Background, NULL, Panel_Rect, name, NULL, WINDOWTYPE, control_toRet, error))
	{
		SDL_FreeSurface(Panel_Background);
		Panel_Background = NULL;
		free(Panel_Rect);
		Panel_Rect = NULL;
		return -1;
	}
	return 0;
}

int Create_Button_from_bmp(char* background_filename, char* background_filename_highlighted, char* name, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr, control** control_toRet, char** error)
{
	SDL_Surface* Button_Background;
	SDL_Surface* Button_Background_Highlighted;
	if (-1 == LoadBMP(background_filename, &Button_Background, error))
	{
		*control_toRet = NULL;
		return -1;
	}
	if (-1 == LoadBMP(background_filename_highlighted, &Button_Background_Highlighted, error))
	{
		SDL_FreeSurface(Button_Background);
		Button_Background = NULL;
		*control_toRet = NULL;
		return -1;
	}

	SDL_Rect* Button_Rect = malloc(sizeof(SDL_Rect));
	if (Button_Rect == NULL) {
		SDL_FreeSurface(Button_Background);
		Button_Background = NULL;
		SDL_FreeSurface(Button_Background_Highlighted);
		Button_Background_Highlighted = NULL;
		*control_toRet = NULL;
		*error = "ERROR: failed to allocate memory for SDL_Rect";
		return -1;
	}

	Button_Rect->x = x_location;
	Button_Rect->y = y_location;
	Button_Rect->h = button_height;
	Button_Rect->w = button_width;

	if (-1 == CreateControl(Button_Background, Button_Background_Highlighted, Button_Rect, name, buttonFunctionPtr, BUTTONTYPE, control_toRet, error))
	{
		SDL_FreeSurface(Button_Background);
		Button_Background = NULL;
		SDL_FreeSurface(Button_Background_Highlighted);
		Button_Background_Highlighted = NULL;
		free(Button_Rect);
		Button_Rect = NULL;
		return -1;
	}
	return 0;
}

int HighlightButtonSurface(SDL_Surface* button_surface, SDL_Surface* button_highlighted_transparent, char** error)
{
	if (SDL_BlitSurface(button_highlighted_transparent, NULL, button_surface, NULL) != 0) {
		*error = SDL_GetError();
		return -1;
	}
	return 0;
}

int Create_Button_from_bmp_transHighlight(char* background_filename, char* highligted_transparent_button_filename, char* name, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr, control** control_toRet, char** error)
{
	SDL_Surface* Button_Background;
	if (-1 == LoadBMP(background_filename, &Button_Background, error))
	{
		*control_toRet = NULL;
		return -1;
	}

	SDL_Surface* Button_Highlighted;
	if (-1 == LoadBMP(background_filename, &Button_Highlighted, error))
	{
		SDL_FreeSurface(Button_Background);
		Button_Background = NULL;
		*control_toRet = NULL;
		return -1;
	}

	SDL_Surface* TranparentHighlightedButton; 
	if (-1 == LoadBMP(highligted_transparent_button_filename, &TranparentHighlightedButton, error))
	{
		SDL_FreeSurface(Button_Background);
		Button_Background = NULL;
		SDL_FreeSurface(Button_Highlighted);
		Button_Highlighted = NULL;
		*control_toRet = NULL;
		return -1;
	}

	// Highlighting the Button Surface;
	if (-1 == HighlightButtonSurface(Button_Highlighted, TranparentHighlightedButton, error))
	{
		SDL_FreeSurface(Button_Background);
		Button_Background = NULL;
		SDL_FreeSurface(Button_Highlighted);
		Button_Highlighted = NULL;
		SDL_FreeSurface(TranparentHighlightedButton);
		TranparentHighlightedButton = NULL;
		*control_toRet = NULL;
		return -1;
	}

	SDL_Rect* Button_Rect = malloc(sizeof(SDL_Rect));
	if (Button_Rect == NULL)
	{
		SDL_FreeSurface(Button_Background);
		Button_Background = NULL;
		SDL_FreeSurface(Button_Highlighted);
		Button_Highlighted = NULL;
		SDL_FreeSurface(TranparentHighlightedButton);
		TranparentHighlightedButton = NULL;
		*control_toRet = NULL;
		*error = "ERROR: failed to allocate memory for SDL_Rect";
		return -1;
	}
	Button_Rect->x = x_location;
	Button_Rect->y = y_location;
	Button_Rect->h = button_height;
	Button_Rect->w = button_width;

	if (-1 == CreateControl(Button_Background, Button_Highlighted, Button_Rect, name, buttonFunctionPtr, BUTTONTYPE, control_toRet, error))
	{
		SDL_FreeSurface(Button_Background);
		Button_Background = NULL;
		SDL_FreeSurface(Button_Highlighted);
		Button_Highlighted = NULL;
		SDL_FreeSurface(TranparentHighlightedButton);
		TranparentHighlightedButton = NULL;
		free(Button_Rect);
		Button_Rect = NULL;
		return -1;
	}
	SDL_FreeSurface(TranparentHighlightedButton);
	TranparentHighlightedButton = NULL;
	return 0;
}

control* GetRoot(UINode* node)
{
	if (node->father == NULL)
	{
		return node->control;
	}
	else
	{
		return GetRoot(node->father);
	}
}

int DrawTree(UINode* node, char** error)
{
	if (node == NULL)
	{
		return 0;
	}
	if (node->father != NULL)
	{
		if (node->control->ishighlighted == 0){
			if (SDL_BlitSurface(node->control->surface, NULL, node->root->control->surface, node->control->location_rect) != 0) {
				*error = SDL_GetError();
				return -1;
			}
		}
		else
		{
			if (SDL_BlitSurface(node->control->highlighted_surface, NULL, node->root->control->surface, node->control->location_rect) != 0) {
				*error = SDL_GetError();
				return -1;
			}
		}
	}
	if (node->children != NULL){
		for (int i = 0; i < node->childrenCount; i++)
		{
			DrawTree(node->children[i], error);
		}
	}
	return 0;
}

void FreeControl(control* control)
{
	SDL_FreeSurface(control->surface);
	SDL_FreeSurface(control->highlighted_surface);
	free(control->location_rect);
	free(control->name);
	control->Action = NULL;
	control->type = NULL;
	free(control);
}

void FreeTree(UINode* node)
{
	if (node == NULL)
	{
		free(node);
		return;
	}

	if (node->children != NULL){
		for (int i = 0; i < node->childrenCount; i++)
		{
			FreeTree(node->children[i]);
		}
	}
	FreeControl(node->control);
	node->control = NULL;

	free(node->children);
	node->children = NULL;

	node->childrenCount = 0;
	node->childrenSize = 0;
	node->father = NULL;
	node->root = NULL;
	
	free(node);
}

UINode* SearchTreeByName(UINode* node,char* name)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->control->name != NULL)
	if (strcmp(node->control->name, name) == 0)
	{
		return node;
	}

	if (node->children != NULL){
		for (int i = 0; i < node->childrenCount; i++)
		{
			UINode* ret = SearchTreeByName(node->children[i], name);
			if (ret != NULL)
			{
				return ret;
			}
		}
	}
	return NULL;
}
