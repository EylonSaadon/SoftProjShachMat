#include "AISettings.h"

void UserColor_ButtonClick(control* input)
{
	// white
	if (strcmp(input->name, BUTTONWHITENAME) == 0)
	{
		if (curSettings->user_color == BLACK)
		{
			curSettings->user_color = WHITE;
			UINode* node = SearchTreeByName(tree, BUTTONBLACKNAME);
			if (node != NULL){
				SwitchButtonHighlight(node->control);
			}
			SwitchButtonHighlight(input);
		}
	}
	// black
	else if (strcmp(input->name, BUTTONBLACKNAME) == 0)
	{
		if (curSettings->user_color == WHITE)
		{
			curSettings->user_color= BLACK;
			UINode* node = SearchTreeByName(tree, BUTTONWHITENAME);
			if (node != NULL){
				SwitchButtonHighlight(node->control);
			}
			SwitchButtonHighlight(input);
		}
	}

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}

void SwitchOffHighlightAllMinimaxDepths()
{
	SwitchOffHighlightbyName(BUTTON1NAME);
	SwitchOffHighlightbyName(BUTTON2NAME);
	SwitchOffHighlightbyName(BUTTON3NAME);
	SwitchOffHighlightbyName(BUTTON4NAME);
	SwitchOffHighlightbyName(BUTTONBESTNAME);
}

void MinimaxDepth_ButtonClick(control* input)
{
	// 1
	if (strcmp(input->name, BUTTON1NAME) == 0)
	{
		if (curSettings->minimax_depth != 1)
		{
			curSettings->minimax_depth = 1;
			SwitchOffHighlightAllMinimaxDepths();
			SwitchOnHighlightbyName(BUTTON1NAME);
		}
	}
	// 2
	else if (strcmp(input->name, BUTTON2NAME) == 0)
	{
		if (curSettings->minimax_depth != 2)
		{
			curSettings->minimax_depth = 2;
			SwitchOffHighlightAllMinimaxDepths();
			SwitchOnHighlightbyName(BUTTON2NAME);
		}
	}
	// 3
	else if (strcmp(input->name, BUTTON3NAME) == 0)
	{
		if (curSettings->minimax_depth != 3)
		{
			curSettings->minimax_depth = 3;
			SwitchOffHighlightAllMinimaxDepths();
			SwitchOnHighlightbyName(BUTTON3NAME);
		}
	}
	// 4 
	else if (strcmp(input->name, BUTTON4NAME) == 0)
	{
		if (curSettings->minimax_depth != 4)
		{
			curSettings->minimax_depth = 4;
			SwitchOffHighlightAllMinimaxDepths();
			SwitchOnHighlightbyName(BUTTON4NAME);
		}
	}
	// Best
	else if (strcmp(input->name, BUTTONBESTNAME) == 0)
	{
		if (curSettings->minimax_depth != MAX_MINIMAX_DEPTH_POSSIBLE)
		{
			curSettings->minimax_depth = MAX_MINIMAX_DEPTH_POSSIBLE;
			SwitchOffHighlightAllMinimaxDepths();
			SwitchOnHighlightbyName(BUTTONBESTNAME);
		}
	}

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}

}


void AICancel_ButtonClick(control* input)
{
	SettingMenu();
}

void AINext_ButtonClick(control* input)
{
	if (setPieces == 1){
		SetPiecesWindow();
	}
	else{
		Game();
	}
}

void AISetting()
{
	FreeTree(tree);
	EventHandler_init(&Quit);

	control* window = Create_window(AISETTING_W, AISETTING_H);
	tree = CreateTree(window);

	control* AISettingBackground_control = Create_panel_from_bmp(
		AISETTINGFILENAME,
		AISETTINGNAME,
		0,
		0,
		(Uint16)AISETTING_W,
		(Uint16)AISETTING_H);
	UINode* AISettingBackground_node = CreateAndAddNodeToTree(AISettingBackground_control, tree);

	int minimaxDepthLabel_x_location = MARGIN;
	int minimaxDepthLabel_y_location = 0.30 * AISETTING_H - 20;
	control* minimaxDepthLabel_control = Create_panel_from_bmp(
		LABELMINIMAXFILENAME,
		LABELMINIMAXNAME,
		minimaxDepthLabel_x_location,
		minimaxDepthLabel_y_location,
		0,
		0);
	UINode* minimaxDepthLabel_node = CreateAndAddNodeToTree(minimaxDepthLabel_control, AISettingBackground_node);

	int oneButton_x_location = minimaxDepthLabel_x_location + 250;
	int oneButton_y_location = minimaxDepthLabel_y_location - 0.7 * BUTTON_H;
	control* oneButton_control = Create_Button_from_bmp_transHighlight(
		BUTTON1FILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTON1NAME,
		oneButton_x_location,
		oneButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&MinimaxDepth_ButtonClick);
	UINode* oneButton_node = CreateAndAddNodeToTree(oneButton_control, AISettingBackground_node);
	AddToListeners(oneButton_control);

	int twoButton_x_location = oneButton_x_location + BUTTON_W + MARGIN;
	int twoButton_y_location = oneButton_y_location;
	control* twoButton_control = Create_Button_from_bmp_transHighlight(
		BUTTON2FILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTON2NAME,
		twoButton_x_location,
		twoButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&MinimaxDepth_ButtonClick);
	UINode* twoButton_node = CreateAndAddNodeToTree(twoButton_control, AISettingBackground_node);
	AddToListeners(twoButton_control);

	int threeButton_x_location = oneButton_x_location;
	int threeButton_y_location = oneButton_y_location + BUTTON_H + 2* MARGIN;
	control* threeButton_control = Create_Button_from_bmp_transHighlight(
		BUTTON3FILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTON3NAME,
		threeButton_x_location,
		threeButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&MinimaxDepth_ButtonClick);
	UINode* threeButton_node = CreateAndAddNodeToTree(threeButton_control, AISettingBackground_node);
	AddToListeners(threeButton_control);

	int fourButton_x_location = twoButton_x_location;
	int fourButton_y_location = threeButton_y_location;
	control* fourButton_control = Create_Button_from_bmp_transHighlight(
		BUTTON4FILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTON4NAME,
		fourButton_x_location,
		fourButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&MinimaxDepth_ButtonClick);
	UINode* fourButton_node = CreateAndAddNodeToTree(fourButton_control, AISettingBackground_node);
	AddToListeners(fourButton_control);

	int bestButton_x_location = threeButton_x_location;
	int bestButton_y_location = threeButton_y_location + BUTTON_H + 2* MARGIN;
	control* bestButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONBESTFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONBESTNAME,
		bestButton_x_location,
		bestButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&MinimaxDepth_ButtonClick);
	UINode* bestButton_node = CreateAndAddNodeToTree(bestButton_control, AISettingBackground_node);
	AddToListeners(bestButton_control);

	int UserColorLabel_x_location = MARGIN;
	int UserColorLabel_y_location = 0.75 * AISETTING_H - BUTTON_H;
	control* UserColorLabel_control = Create_panel_from_bmp(
		LABELUSERCOLORFILENAME,
		LABELUSERCOLORNAME,
		UserColorLabel_x_location,
		UserColorLabel_y_location,
		0,
		0);
	UINode* UserColorLabel_node = CreateAndAddNodeToTree(UserColorLabel_control, AISettingBackground_node);

	int whiteButton_x_location = oneButton_x_location;
	int whiteButton_y_location = UserColorLabel_y_location;
	control* whiteButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONWHITEFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONWHITENAME,
		whiteButton_x_location,
		whiteButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&UserColor_ButtonClick);
	UINode* whiteButton_node = CreateAndAddNodeToTree(whiteButton_control, AISettingBackground_node);
	AddToListeners(whiteButton_control);

	int blackButton_x_location = whiteButton_x_location + BUTTON_W + MARGIN;
	int blackButton_y_location = whiteButton_y_location;
	control* blackButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONBLACKFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONBLACKNAME,
		blackButton_x_location,
		blackButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&UserColor_ButtonClick);
	UINode* blackButton_node = CreateAndAddNodeToTree(blackButton_control, AISettingBackground_node);
	AddToListeners(blackButton_control);


	int cancelButton_x_location = MARGIN;
	int cancelButton_y_location = AISETTING_H - BUTTON_H - MARGIN * 2;
	control* cancelButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONCANCELFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONCANCELNAME,
		cancelButton_x_location,
		cancelButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&AICancel_ButtonClick);
	UINode* cancelButton_node = CreateAndAddNodeToTree(cancelButton_control, AISettingBackground_node);
	AddToListeners(cancelButton_control);

	int nextButton_x_location = AISETTING_W - BUTTON_W - MARGIN;
	int nextButton_y_location = AISETTING_H - BUTTON_H - MARGIN * 2;
	control* nextButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONNEXTFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONNEXTNAME,
		nextButton_x_location,
		nextButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&AINext_ButtonClick);
	UINode* nextButton_node = CreateAndAddNodeToTree(nextButton_control, AISettingBackground_node);
	AddToListeners(nextButton_control);

	if (curSettings->user_color == WHITE)
	{
		whiteButton_control->ishighlighted = 1;
	}
	else
	{
		blackButton_control->ishighlighted = 0;
	}

	switch (curSettings->minimax_depth){
	case 1:
		oneButton_control->ishighlighted = 1;
		break;
	case 2:
		twoButton_control->ishighlighted = 1;
		break;
	case 3:
		threeButton_control->ishighlighted = 1;
		break;
	case 4:
		fourButton_control->ishighlighted = 1;
		break;
	case MAX_MINIMAX_DEPTH_POSSIBLE:
		bestButton_control->ishighlighted = 1;
		break;
	}

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}