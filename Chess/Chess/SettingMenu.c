#include "SettingMenu.h"


void ChooseMode_ButtonClick(control* input)
{
	// PVP
	if (strcmp(input->name, BUTTONPVPNAME) == 0)
	{
		if (curSettings->game_mode == PLAYER_VS_AI_GAME_MODE)
		{
			curSettings->game_mode = TWO_PLAYERS_GAME_MODE;
			UINode* node = SearchTreeByName(tree, BUTTONPVCNAME);
			if (node != NULL){
				SwitchButtonHighlight(node->control);
			}
			SwitchButtonHighlight(input);
		}
	}
	// PVC
	else if (strcmp(input->name, BUTTONPVCNAME) == 0)
	{
		if (curSettings->game_mode == TWO_PLAYERS_GAME_MODE)
		{
			curSettings->game_mode = PLAYER_VS_AI_GAME_MODE;
			UINode* node = SearchTreeByName(tree, BUTTONPVPNAME);
			if (node != NULL){
				SwitchButtonHighlight(node->control);
			}
			SwitchButtonHighlight(input);
		}
	}

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}

void SetPiece_ButtonClick(control* input)
{
	SwitchButtonHighlight(input);
	if (setPieces == 0)
	{
		setPieces = 1;
	}
	else
	{
		setPieces = 0;
	}

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}



void NextPlayer_ButtonClick(control* input)
{
	// white
	if (strcmp(input->name, BUTTONWHITENAME) == 0)
	{
		if (curSettings->next_turn == BLACK)
		{
			curSettings->next_turn = WHITE;
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
		if (curSettings->next_turn == WHITE)
		{
			curSettings->next_turn = BLACK;
			UINode* node = SearchTreeByName(tree, BUTTONWHITENAME);
			if (node != NULL){
				SwitchButtonHighlight(node->control);
			}
			SwitchButtonHighlight(input);
		}
	}

	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}
void GameSettingsCancel_ButtonClick(control* input)
{
	releaseResouces();
	MainMenu();
}

void GameSettingsNext_ButtonClick(control* input)
{
	if (curSettings->game_mode == PLAYER_VS_AI_GAME_MODE){
		AISetting();
		return;
	}
	if(setPieces == 1){
		SetPiecesWindow();
		return;
	}
	else{
		Game();
		return;
	}
}


void SettingMenu()
{
	FreeTree(tree);
	if (-1 == EventHandler_init(&Quit, &error))
	{
		guiQuit = -1;
	}

	control* window;
	if (-1 == Create_window(GAMESETTING_W, GAMESETTING_H, &window, &error))
	{
		guiQuit = -1;
	}
	if (-1 == CreateTree(window, &tree, &error))
	{
		guiQuit = -1;
	}

	// Drawing all controls
	#pragma region Drawing
	control* gameSettingBackground_control;
	Create_panel_from_bmp(
		GAMESETTINGFILENAME,
		GAMESETTINGNAME,
		0,
		0,
		(Uint16)GAMESETTING_W,
		(Uint16)GAMESETTING_H,
		&gameSettingBackground_control,
		&error);
	UINode* gameSettingBackground_node;
	if (-1 == CreateAndAddNodeToTree(gameSettingBackground_control, tree, &gameSettingBackground_node, &error))
	{
		guiQuit = -1;
	}


	//int chooseModeLabel_x_location = MARGIN;
	//int chooseModeLabel_y_location = 0.25 * GAMESETTING_H - 20;

	//control* chooseModeLabel_control;
	//if (-1 == Create_panel_from_bmp(
	//	LABELCHOOSEMODEFILENAME,
	//	LABELCHOOSEMODENAME,
	//	chooseModeLabel_x_location,
	//	chooseModeLabel_y_location,
	//	0,
	//	0,
	//	&chooseModeLabel_control,
	//	&error))
	//{
	//	guiQuit = -1;
	//}
	//UINode* chooseModeLabel_node;
	//if (-1 == CreateAndAddNodeToTree(chooseModeLabel_control, gameSettingBackground_node, &chooseModeLabel_node, &error))
	//{
	//	guiQuit = -1;
	//}

	int pvpButtonn_x_location = 285;
	int pvpButton_y_location = 45;
	control* pvpButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONPVPFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONPVPNAME,
		pvpButtonn_x_location,
		pvpButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&ChooseMode_ButtonClick,
		&pvpButton_control,
		&error))
	{
		guiQuit = -1;
	}

	UINode* pvpButton_node;
	if (-1 == CreateAndAddNodeToTree(pvpButton_control, gameSettingBackground_node, &pvpButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(pvpButton_control, &error))
	{
		guiQuit = -1;
	}

	int pvcButtonn_x_location = pvpButtonn_x_location + BUTTON_W + MARGIN;//227
	int pvcButton_y_location = pvpButton_y_location;
	control* pvcButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONPVCFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONPVCNAME,
		pvcButtonn_x_location,
		pvcButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&ChooseMode_ButtonClick,
		&pvcButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* pvcButton_node;
	if (-1 == CreateAndAddNodeToTree(pvcButton_control, gameSettingBackground_node, &pvcButton_node, &error))
	{		
		guiQuit = -1;
	}

	if (-1 == AddToListeners(pvcButton_control, &error))
	{
		guiQuit = -1;
	}

	//int setPiecesLabel_x_location = MARGIN;
	//int setPiecesLabel_y_location = 0.50 * GAMESETTING_H - 20;
	//control* setPiecesLabel_control;
	//if( -1 == Create_panel_from_bmp(
	//	LABELSETPIECESFILENAME,
	//	LABELSETPIECESNAME,
	//	setPiecesLabel_x_location,
	//	setPiecesLabel_y_location,
	//	0,
	//	0,
	//	&setPiecesLabel_control, 
	//	&error))
	//{
	//	guiQuit	= -1;
	//}
	//UINode* setPiecesLabel_node;
	//if (-1 == CreateAndAddNodeToTree(setPiecesLabel_control, gameSettingBackground_node, &setPiecesLabel_node, &error))
	//{
	//	guiQuit = -1;
	//}

	int setPiecesButton_x_location = pvpButtonn_x_location;
	int setPiecesButton_y_location = 133;

	control* setPiecesButton_control;
	if( -1 == Create_Button_from_bmp_transHighlight(
		BUTTONSETPIECESFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONSETPIECESNAME,
		setPiecesButton_x_location,
		setPiecesButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&SetPiece_ButtonClick, 
		&setPiecesButton_control, 
		&error))
	{
		guiQuit = -1;
	}
	UINode* setPiecesButton_node;
	if (-1 == CreateAndAddNodeToTree(setPiecesButton_control, gameSettingBackground_node, &setPiecesButton_node, &error))
	{
		guiQuit = -1;
	}

	if (-1 == AddToListeners(setPiecesButton_control, &error))
	{
		guiQuit = -1;
	}

	//int nextPlayerLabel_x_location = MARGIN;
	//int nextPlayerLabel_y_location = 0.75 * GAMESETTING_H - 20;
	//control* nextPlayerLabel_control;
	//if(-1 == Create_panel_from_bmp(
	//	LABELNEXTPLAYERFILENAME,
	//	LABELNEXTPLAYERNAME,
	//	nextPlayerLabel_x_location,
	//	nextPlayerLabel_y_location,
	//	0,
	//	0, 
	//	&nextPlayerLabel_control,
	//	&error))
	//{
	//	guiQuit = -1;
	//}
	//UINode* nextPlayerLabel_node;
	//if (-1 == CreateAndAddNodeToTree(nextPlayerLabel_control, gameSettingBackground_node, &nextPlayerLabel_node, &error))
	//{
	//	guiQuit = -1;
	//}

	int whiteButton_x_location = pvpButtonn_x_location;
	int whiteButton_y_location = 222;
	control* whiteButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONWHITEFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONWHITENAME,
		whiteButton_x_location,
		whiteButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&NextPlayer_ButtonClick,
		&whiteButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* whiteButton_node;
	if (-1 == CreateAndAddNodeToTree(whiteButton_control, gameSettingBackground_node, &whiteButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(whiteButton_control, &error))
	{
		guiQuit = -1;
	}

	int blackButton_x_location = pvcButtonn_x_location;
	int blackButton_y_location = 222;
	control* blackButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONBLACKFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONBLACKNAME,
		blackButton_x_location,
		blackButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&NextPlayer_ButtonClick,
		&blackButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* blackButton_node;
	if (-1 == CreateAndAddNodeToTree(blackButton_control, gameSettingBackground_node, &blackButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(blackButton_control, &error))
	{
		guiQuit = -1;
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
		&GameSettingsCancel_ButtonClick,
		&cancelButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* cancelButton_node;
	if (-1 == CreateAndAddNodeToTree(cancelButton_control, gameSettingBackground_node, &cancelButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(cancelButton_control, &error))
	{
		guiQuit = -1;
	}

	int nextButton_x_location = cancelButton_x_location;
	int nextButton_y_location = 474;
	control* nextButton_control;
	if(-1 ==Create_Button_from_bmp_transHighlight(
		BUTTONNEXTFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONNEXTNAME,
		nextButton_x_location,
		nextButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameSettingsNext_ButtonClick,
		&nextButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* nextButton_node;
	if(-1 == CreateAndAddNodeToTree(nextButton_control, gameSettingBackground_node, &nextButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(nextButton_control, &error))
	{
		guiQuit = -1;
	}
	#pragma endregion

	if (curSettings->game_mode == TWO_PLAYERS_GAME_MODE)
	{
		pvpButton_control->ishighlighted = 1;
	}
	else
	{
		pvcButton_control->ishighlighted = 1;
	}

	if (curSettings->next_turn == WHITE)
	{
		whiteButton_control->ishighlighted = 1;
	}
	else
	{
		blackButton_control->ishighlighted = 1;
	}

	if (1 == setPieces)
	{
		setPiecesButton_control->ishighlighted = 1;
	}

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}