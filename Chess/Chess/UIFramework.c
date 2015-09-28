#include "UIFrameWork.h"


SDL_Surface* LoadBMP(char* fileName)
{
	SDL_Surface* surface = SDL_LoadBMP(fileName);
	Uint32 green = SDL_MapRGB(surface->format, 0, 255, 0);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, green);
	return surface;
}

control* Create_window(int window_w, int window_h)
{
	SDL_Surface *window = SDL_SetVideoMode(window_w, window_h, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	/* Create window surface*/
	if (window == NULL) {
		printf("ERROR: failed to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	control* ret = (control*)malloc(sizeof(control));
	ret->surface = window;
	ret->type = WINDOWTYPE;
	ret->Action = NULL;
	ret->highlighted_surface = NULL;
	ret->location_rect = NULL;
	return ret;
}


control* Create_panel_from_bmp(char* background_filename, Sint16 x_location, Sint16 y_location, Uint16 picture_width, Uint16 picture_height)
{
	SDL_Surface* Panel_Background = LoadBMP(background_filename);

	SDL_Rect* Panel_Rect = malloc(sizeof(SDL_Rect));
	Panel_Rect->x = x_location;
	Panel_Rect->y = x_location;
	Panel_Rect->h = picture_height;
	Panel_Rect->w = picture_width;

	control* ret = (control*)malloc(sizeof(control));
	ret->surface = Panel_Background;
	ret->type = PANELTYPE;
	ret->Action = NULL;
	ret->highlighted_surface = NULL;
	ret->location_rect = Panel_Rect;
	return ret;
}

control* Create_Button_from_bmp(char* background_filename, char* background_filename_highlighted, Sint16 x_location, Sint16 y_location, Uint16 button_width, Uint16 button_height, ButtonAction buttonFunctionPtr)
{
	SDL_Surface* Button_Background = LoadBMP(background_filename);
	SDL_Surface* Button_Background_Highlighted = LoadBMP(background_filename_highlighted);

	SDL_Rect* Button_Rect = malloc(sizeof(SDL_Rect));
	Button_Rect->x = x_location;
	Button_Rect->y = y_location;
	Button_Rect->h = button_height;
	Button_Rect->w = button_width;

	control* ret = (control*)malloc(sizeof(control));
	ret->surface = Button_Background;
	ret->highlighted_surface = Button_Background_Highlighted;
	ret->location_rect = Button_Rect;
	ret->type = BUTTONTYPE;
	ret->Action = buttonFunctionPtr;
	return ret;
}

void DrawTree(UINode* node)
{
	if (node == NULL)
	{
		return;
	}
	if (node->children != NULL){
		for (int i = 0; i < node->childrenCount; i++)
		{
			DrawTree(node->children[i]);
		}
	}
	if (node->father != NULL)
	{
		SDL_BlitSurface(node->control->surface, NULL, node->father->control->surface, node->control->location_rect);
	}
}

void FreeControl(control* control)
{
	SDL_FreeSurface(control->surface);
	SDL_FreeSurface(control->highlighted_surface);
	free(control->type);
	free(control->location_rect);
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
	free(node->children);
	free(node);
}