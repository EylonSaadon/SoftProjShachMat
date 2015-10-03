#include "UIFrameWork.h"


SDL_Surface* LoadBMP(char* fileName)
{
	SDL_Surface* surface = SDL_LoadBMP(fileName);
	Uint32 green = SDL_MapRGB(surface->format, 0, 255, 0);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, green);
	return surface;
}

control* CreateControl(SDL_Surface* Button_Background, SDL_Surface* Button_Background_Highlighted, SDL_Rect* Button_Rect, char* name, ButtonAction action, char* type)
{
	control* ret = (control*)malloc(sizeof(control));
	ret->surface = Button_Background;
	ret->highlighted_surface = Button_Background_Highlighted;
	ret->location_rect = Button_Rect;
	ret->type = type;
	if (name != NULL){
		ret->name = malloc((strlen(name)+1) * sizeof(char));
		for (int i = 0; i < strlen(name); i++)
		{
			ret->name[i] = name[i];
		}
		ret->name[strlen(name)] = NULL;
	}
	else
	{
		ret->name = name;
	}
	ret->Action = action;
	ret->ishighlighted = 0;
	return ret;
}

control* Create_window(int window_w, int window_h)
{
	SDL_Surface *window = SDL_SetVideoMode(window_w, window_h, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	/* Create window surface*/
	if (window == NULL) {
		printf("ERROR: failed to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	return CreateControl(window, NULL, NULL, NULL, NULL,WINDOWTYPE);
}


control* Create_panel_from_bmp(char* background_filename, char* name, Sint16 x_location, Sint16 y_location, Uint16 picture_width, Uint16 picture_height)
{
	SDL_Surface* Panel_Background = LoadBMP(background_filename);

	SDL_Rect* Panel_Rect = malloc(sizeof(SDL_Rect));
	Panel_Rect->x = x_location;
	Panel_Rect->y = y_location;
	Panel_Rect->h = picture_height;
	Panel_Rect->w = picture_width;

	return CreateControl(Panel_Background, NULL, Panel_Rect, name, NULL, PANELTYPE);
}



control* Create_Button_from_bmp(char* background_filename, char* background_filename_highlighted, char* name, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr)
{
	SDL_Surface* Button_Background = LoadBMP(background_filename);
	SDL_Surface* Button_Background_Highlighted = LoadBMP(background_filename_highlighted);

	SDL_Rect* Button_Rect = malloc(sizeof(SDL_Rect));
	Button_Rect->x = x_location;
	Button_Rect->y = y_location;
	Button_Rect->h = button_height;
	Button_Rect->w = button_width;

	return CreateControl(Button_Background, Button_Background_Highlighted, Button_Rect, name, buttonFunctionPtr, BUTTONTYPE);
}

void HighlightButtonSurface(SDL_Surface* button_surface, SDL_Surface* button_highlighted_transparent)
{
	SDL_BlitSurface(button_highlighted_transparent, NULL, button_surface, NULL);
}

control* Create_Button_from_bmp_transHighlight(char* background_filename, char* highligted_transparent_button_filename, char* name, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr)
{
	SDL_Surface* Button_Background = LoadBMP(background_filename);

	SDL_Surface* Button_Highlighted = LoadBMP(background_filename);
	SDL_Surface* TranparentHighlightedButton = LoadBMP(highligted_transparent_button_filename);

	HighlightButtonSurface(Button_Highlighted, TranparentHighlightedButton);

	SDL_Rect* Button_Rect = malloc(sizeof(SDL_Rect));
	Button_Rect->x = x_location;
	Button_Rect->y = y_location;
	Button_Rect->h = button_height;
	Button_Rect->w = button_width;

	return CreateControl(Button_Background, Button_Highlighted, Button_Rect, name, buttonFunctionPtr, BUTTONTYPE);
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

void DrawTree(UINode* node)
{
	if (node == NULL)
	{
		return;
	}
	if (node->father != NULL)
	{
		if (node->control->ishighlighted == 0){
			SDL_BlitSurface(node->control->surface, NULL, node->root->control->surface, node->control->location_rect);
		}
		else
		{
			SDL_BlitSurface(node->control->highlighted_surface, NULL, node->root->control->surface, node->control->location_rect);
		}
	}
	if (node->children != NULL){
		for (int i = 0; i < node->childrenCount; i++)
		{
			DrawTree(node->children[i]);
		}
	}

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