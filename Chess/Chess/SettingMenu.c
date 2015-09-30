#include "SettingMenu.h"
#include "AISettings.h"

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

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
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
		setPieces == 0;
	}
	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
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

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}
void GameSettingsCancel_ButtonClick(control* input)
{
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
		StartGame();
		return;
	}
}


int SettingMenu()
{
	print_board(board);
	FreeTree(tree);
	EventHandler_init(&Quit);

	setPieces = 0;

	control* window = Create_window(GAMESETTING_W, GAMESETTING_H);
	tree = CreateTree(window);

	control* gameSettingBackground_control = Create_panel_from_bmp(
		GAMESETTINGFILENAME,
		GAMESETTINGNAME,
		0,
		0,
		(Uint16)GAMESETTING_W,
		(Uint16)GAMESETTING_H);
	UINode* gameSettingBackground_node = CreateAndAddNodeToTree(gameSettingBackground_control, tree);


	int chooseModeLabel_x_location = MARGIN;
	int chooseModeLabel_y_location = 0.25 * GAMESETTING_H - 20;
	control* chooseModeLabel_control = Create_panel_from_bmp(
		LABELCHOOSEMODEFILENAME,
		LABELCHOOSEMODENAME,
		chooseModeLabel_x_location,
		chooseModeLabel_y_location,
		0,
		0);
	UINode* chooseModeLabel_node = CreateAndAddNodeToTree(chooseModeLabel_control, gameSettingBackground_node);

	int pvpButtonn_x_location = chooseModeLabel_x_location + 200;
	int pvpButton_y_location = chooseModeLabel_y_location;
	control* pvpButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONPVPFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONPVPNAME,
		pvpButtonn_x_location,
		pvpButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&ChooseMode_ButtonClick);
	UINode* pvpButton_node = CreateAndAddNodeToTree(pvpButton_control, gameSettingBackground_node);
	AddToListeners(pvpButton_control);

	int pvcButtonn_x_location = pvpButtonn_x_location + BUTTON_W + MARGIN;
	int pvcButton_y_location = pvpButton_y_location;
	control* pvcButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONPVCFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONPVCNAME,
		pvcButtonn_x_location,
		pvcButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&ChooseMode_ButtonClick);
	UINode* pvcButton_node = CreateAndAddNodeToTree(pvcButton_control, gameSettingBackground_node);
	AddToListeners(pvcButton_control);

	int setPiecesLabel_x_location = MARGIN;
	int setPiecesLabel_y_location = 0.50 * GAMESETTING_H - 20;
	control* setPiecesLabel_control = Create_panel_from_bmp(
		LABELSETPIECESFILENAME,
		LABELSETPIECESNAME,
		setPiecesLabel_x_location,
		setPiecesLabel_y_location,
		0,
		0);
	UINode* setPiecesLabel_node = CreateAndAddNodeToTree(setPiecesLabel_control, gameSettingBackground_node);

	int setPiecesButton_x_location = pvpButtonn_x_location;
	int setPiecesButton_y_location = setPiecesLabel_y_location;
	control* setPiecesButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONSETPIECESFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONSETPIECESNAME,
		setPiecesButton_x_location,
		setPiecesButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&SetPiece_ButtonClick);
	UINode* setPiecesButton_node = CreateAndAddNodeToTree(setPiecesButton_control, gameSettingBackground_node);
	AddToListeners(setPiecesButton_control);

	int nextPlayerLabel_x_location = MARGIN;
	int nextPlayerLabel_y_location = 0.75 * GAMESETTING_H - 20;
	control* nextPlayerLabel_control = Create_panel_from_bmp(
		LABELNEXTPLAYERFILENAME,
		LABELNEXTPLAYERNAME,
		nextPlayerLabel_x_location,
		nextPlayerLabel_y_location,
		0,
		0);
	UINode* nextPlayerLabel_node = CreateAndAddNodeToTree(nextPlayerLabel_control, gameSettingBackground_node);

	int whiteButton_x_location = pvpButtonn_x_location;
	int whiteButton_y_location = nextPlayerLabel_y_location;
	control* whiteButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONWHITEFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONWHITENAME,
		whiteButton_x_location,
		whiteButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&NextPlayer_ButtonClick);
	UINode* whiteButton_node = CreateAndAddNodeToTree(whiteButton_control, gameSettingBackground_node);
	AddToListeners(whiteButton_control);

	int blackButton_x_location = pvcButtonn_x_location;
	int blackButton_y_location = nextPlayerLabel_y_location;
	control* blackButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONBLACKFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONBLACKNAME,
		blackButton_x_location,
		blackButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&NextPlayer_ButtonClick);
	UINode* blackButton_node = CreateAndAddNodeToTree(blackButton_control, gameSettingBackground_node);
	AddToListeners(blackButton_control);


	int cancelButton_x_location = MARGIN ;
	int cancelButton_y_location = GAMESETTING_H - BUTTON_H - MARGIN * 2;
	control* cancelButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONCANCELFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONCANCELNAME,
		cancelButton_x_location,
		cancelButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameSettingsCancel_ButtonClick);
	UINode* cancelButton_node = CreateAndAddNodeToTree(cancelButton_control, gameSettingBackground_node);
	AddToListeners(cancelButton_control);

	int nextButton_x_location = GAMESETTING_W - BUTTON_W - MARGIN;
	int nextButton_y_location = GAMESETTING_H - BUTTON_H - MARGIN * 2;
	control* nextButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONNEXTFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONNEXTNAME,
		nextButton_x_location,
		nextButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameSettingsNext_ButtonClick);
	UINode* nextButton_node = CreateAndAddNodeToTree(nextButton_control, gameSettingBackground_node);
	AddToListeners(nextButton_control);

	if (curSettings->game_mode == TWO_PLAYERS_GAME_MODE)
	{
		pvpButton_control->ishighlighted = 1;
	}
	else
	{
		pvcButton_control->ishighlighted = 0;
	}

	if (curSettings->next_turn == WHITE)
	{
		whiteButton_control->ishighlighted = 1;
	}
	else
	{
		blackButton_control->ishighlighted = 0;
	}

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}