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
			curSettings->user_color = BLACK;
			UINode* node = SearchTreeByName(tree, BUTTONWHITENAME);
			if (node != NULL){
				SwitchButtonHighlight(node->control);
			}
			SwitchButtonHighlight(input);
		}
	}

	// DrawTree
	if (-1 == FlipTree(&error_global))
	{
		guiQuit = -1;
		return;
	}
}

void AIMinimaxDepth_ButtonClick(control* input)
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
			curSettings->minimax_depth = get_best_depth(board);
			SwitchOffHighlightAllMinimaxDepths();
			SwitchOnHighlightbyName(BUTTONBESTNAME);
		}
	}

	// DrawTree
	if (-1 == FlipTree(&error_global))
	{
		guiQuit = -1;
		return;
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
		return;
	}
	else{
		Game();
		return;
	}
}

void AISetting()
{
	FreeTree(tree);

	if (-1 == EventHandler_init(&Quit, &error_global))
	{
		guiQuit = -1;
		return;
	}

	control* window;
	if (-1 == Create_window(AISETTING_W, AISETTING_H, &window, &error_global))
	{
		guiQuit = -1;
		return;
	}


	if (-1 == CreateTree(window, &tree, &error_global))
	{
		FreeControl(window);
		guiQuit = -1;
		return;
	}


	control* AISettingBackground_control;
	if (-1 == Create_panel_from_bmp(
		AISETTINGFILENAME,
		AISETTINGNAME,
		0,
		0,
		(Uint16)AISETTING_W,
		(Uint16)AISETTING_H,
		&AISettingBackground_control,
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* AISettingBackground_node;
	if (-1 == CreateAndAddNodeToTree(AISettingBackground_control, tree, &AISettingBackground_node, &error_global))
	{
		FreeControl(AISettingBackground_control);
		guiQuit = -1;
		return;
	}

	int oneButton_x_location = 330;
	int oneButton_y_location = 48;

	control* oneButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTON1FILENAME,
		NUMBUTTONHIGHLIGHTEDFILENAME,
		BUTTON1NAME,
		oneButton_x_location,
		oneButton_y_location,
		(Uint16)NUMBUTTON_W,
		(Uint16)NUMBUTTON_H,
		&AIMinimaxDepth_ButtonClick,
		&oneButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* oneButton_node;
	if (-1 == CreateAndAddNodeToTree(oneButton_control, AISettingBackground_node, &oneButton_node, &error_global))
	{
		FreeControl(oneButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(oneButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	int twoButton_x_location = oneButton_x_location + NUMBUTTON_W + 28;
	int twoButton_y_location = oneButton_y_location;
	control* twoButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTON2FILENAME,
		NUMBUTTONHIGHLIGHTEDFILENAME,
		BUTTON2NAME,
		twoButton_x_location,
		twoButton_y_location,
		(Uint16)NUMBUTTON_W,
		(Uint16)NUMBUTTON_H,
		&AIMinimaxDepth_ButtonClick,
		&twoButton_control,
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* twoButton_node;
	if (-1 == CreateAndAddNodeToTree(twoButton_control, AISettingBackground_node, &twoButton_node, &error_global))
	{
		FreeControl(twoButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(twoButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	int threeButton_x_location = twoButton_x_location + NUMBUTTON_W + 28;
	int threeButton_y_location = oneButton_y_location;
	control* threeButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTON3FILENAME,
		NUMBUTTONHIGHLIGHTEDFILENAME,
		BUTTON3NAME,
		threeButton_x_location,
		threeButton_y_location,
		(Uint16)NUMBUTTON_W,
		(Uint16)NUMBUTTON_H,
		&AIMinimaxDepth_ButtonClick,
		&threeButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* threeButton_node;
	if (-1 == CreateAndAddNodeToTree(threeButton_control, AISettingBackground_node, &threeButton_node, &error_global))
	{
		FreeControl(threeButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(threeButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	int fourButton_x_location = threeButton_x_location + NUMBUTTON_W + 28;
	int fourButton_y_location = threeButton_y_location;
	control* fourButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTON4FILENAME,
		NUMBUTTONHIGHLIGHTEDFILENAME,
		BUTTON4NAME,
		fourButton_x_location,
		fourButton_y_location,
		(Uint16)NUMBUTTON_W,
		(Uint16)NUMBUTTON_H,
		&AIMinimaxDepth_ButtonClick,
		&fourButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* fourButton_node;
	if (-1 == CreateAndAddNodeToTree(fourButton_control, AISettingBackground_node, &fourButton_node, &error_global))
	{
		FreeControl(fourButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(fourButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	int bestButton_x_location = fourButton_x_location + NUMBUTTON_W + 45;
	int bestButton_y_location = fourButton_y_location;
	control* bestButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONBESTFILENAME,
		BUTTONBESTHIGHLIGHTFILENAME,
		BUTTONBESTNAME,
		bestButton_x_location,
		bestButton_y_location,
		(Uint16)BESTBUTTON_W,
		(Uint16)BESTBUTTON_H,
		&AIMinimaxDepth_ButtonClick, &bestButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* bestButton_node;
	if (-1 == CreateAndAddNodeToTree(bestButton_control, AISettingBackground_node, &bestButton_node, &error_global))
	{
		FreeControl(bestButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(bestButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	int whiteButton_x_location = oneButton_x_location;
	int whiteButton_y_location = 156;
	control* whiteButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONWHITEFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONWHITENAME,
		whiteButton_x_location,
		whiteButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&UserColor_ButtonClick,
		&whiteButton_control,
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* whiteButton_node;
	if (-1 == CreateAndAddNodeToTree(whiteButton_control, AISettingBackground_node, &whiteButton_node, &error_global))
	{
		FreeControl(whiteButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(whiteButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	int blackButton_x_location = whiteButton_x_location + BUTTON_W + 28;
	int blackButton_y_location = whiteButton_y_location;
	control* blackButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONBLACKFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONBLACKNAME,
		blackButton_x_location,
		blackButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&UserColor_ButtonClick,
		&blackButton_control,
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* blackButton_node;
	if (-1 == CreateAndAddNodeToTree(blackButton_control, AISettingBackground_node, &blackButton_node, &error_global))
	{
		FreeControl(blackButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(blackButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}


	int cancelButton_x_location = 44;
	int cancelButton_y_location = 398;
	control* cancelButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONCANCELFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONCANCELNAME,
		cancelButton_x_location,
		cancelButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&AICancel_ButtonClick,
		&cancelButton_control,
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* cancelButton_node;
	if (-1 == CreateAndAddNodeToTree(cancelButton_control, AISettingBackground_node, &cancelButton_node, &error_global))
	{
		FreeControl(cancelButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(cancelButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	int nextButton_x_location = cancelButton_x_location;
	int nextButton_y_location = 474;
	control* nextButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONNEXTFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONNEXTNAME,
		nextButton_x_location,
		nextButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&AINext_ButtonClick,
		&nextButton_control,
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* nextButton_node;
	if (-1 == CreateAndAddNodeToTree(nextButton_control, AISettingBackground_node, &nextButton_node, &error_global))
	{
		FreeControl(nextButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(nextButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	if (curSettings->user_color == WHITE)
	{
		whiteButton_control->ishighlighted = 1;
	}
	else
	{
		blackButton_control->ishighlighted = 1;
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

	// DrawTree
	if (-1 == FlipTree(&error_global))
	{
		guiQuit = -1;
		return;
	}
}