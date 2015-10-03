#include "GameBoard.h"


control* gameSelectedSquare_control;

void GameBoardMainMenu_ButtonClick(control* input)
{
	MainMenu();
}

void HighlightBestMove(int blinknum)
{
	struct move_list* best_move_list = NULL;
	int number_of_boards_evaluated = 0;

	// Get the best next move
	int current_move_grade = get_best_moves_using_minimax(curSettings->minimax_depth, board, curSettings->next_turn, curSettings->next_turn, 0, curMovesList, &best_move_list, ALPHA_INIT, BETA_INIT, &number_of_boards_evaluated);

	// Check for errors
	if (FAILED_ERROR == current_move_grade) {
		free_move_list(best_move_list);
		guiQuit = 1;
		return;
	}

	move bestMove = best_move_list->mov;
	position startPos = bestMove.start_pos;
	position endPos = bestMove.end_pos;

	control* startSquare = buttonsBoard[startPos.col][7 - (int)startPos.row];
	control* endSquare = buttonsBoard[endPos.col][7 - (int)endPos.row];

	bool startHiglighted = startSquare->ishighlighted;
	bool endHiglighted = endSquare->ishighlighted;

	startSquare->ishighlighted = 1;
	endSquare->ishighlighted = 1;

	for (int i = 0; i < blinknum; i++){
		SwitchButtonHighlight(startSquare);
		SwitchButtonHighlight(endSquare);

		if (isPawnUpgradePossible(bestMove, board[startPos.col][startPos.row]))
		{
			char* fileName = ResolveFileNameFromLetter(bestMove.new_disc);
			char* name = ResolveNameFromLetter(bestMove.new_disc);

			if (fileName != NULL){
				control* chessPiece_control;
				if (-1 == Create_panel_from_bmp(
					fileName,
					SQUAREBUTTONHIGHLIGHTEDFILENAME,
					name,
					BOARD_W + MARGIN,
					BOARD_W - SQUARE_H - 0.5,
					(Uint16)SQUARE_W,
					(Uint16)SQUARE_H,
					&chessPiece_control, &error))
				{
					guiQuit = -1;
				}
				UINode* chessPiece_node;
				if (-1 == CreateAndAddNodeToTree(chessPiece_control, tree->children[0], &chessPiece_node, &error))
				{
					guiQuit = -1;
				}
			}
		}

		// DrawTree
		if (-1 == FlipTree(&error))
		{
			guiQuit = -1;
		}
		SDL_Delay(500);
	}



	startSquare->ishighlighted = startHiglighted;
	endSquare->ishighlighted = endHiglighted;

	free_move_list(best_move_list);
}

void GameMinimaxDepth_ButtonClick(control* input)
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

	HighlightBestMove(BLINKNUM);

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}

void GameBoardBest_ButtonClick(control * input)
{
	if (showDepthOptions == false){
		showDepthOptions = true;
		input->ishighlighted = 1;
	}
	else
	{
		showDepthOptions = false;
		input->ishighlighted = 0;
	}
	if (showDepthOptions){
		if (curSettings->game_mode == TWO_PLAYERS_GAME_MODE){


			UINode* gameBoarBackground_node = tree->children[0];
			int oneButton_x_location = BOARD_W + 0.5 * MARGIN;
			int oneButton_y_location = BOARD_H *0.5 + 0.5 * NUMBUTTON_H;

			control* oneButton_control;
			if (-1 == Create_Button_from_bmp_transHighlight(
				BUTTON1FILENAME,
				NUMBUTTONHIGHLIGHTEDFILENAME,
				BUTTON1NAME,
				oneButton_x_location,
				oneButton_y_location,
				(Uint16)NUMBUTTON_W,
				(Uint16)NUMBUTTON_H,
				&GameMinimaxDepth_ButtonClick,
				&oneButton_control,
				&error))
			{
				guiQuit = -1;
			}
			UINode* oneButton_node;
			if (-1 == CreateAndAddNodeToTree(oneButton_control, gameBoarBackground_node, &oneButton_node, &error))
			{
				guiQuit = -1;
			}
			if (-1 == AddToListeners(oneButton_control, &error))
			{
				guiQuit = -1;
			}


			int twoButton_x_location = oneButton_x_location + NUMBUTTON_W + 0.5 * MARGIN;
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
				&GameMinimaxDepth_ButtonClick,
				&twoButton_control,
				&error))
			{
				guiQuit = -1;
			}
			UINode* twoButton_node;
			if (-1 == CreateAndAddNodeToTree(twoButton_control, gameBoarBackground_node, &twoButton_node, &error))
			{
				guiQuit = -1;
			}
			if (-1 == AddToListeners(twoButton_control, &error))
			{
				guiQuit = -1;
			}


			int threeButton_x_location = twoButton_x_location + NUMBUTTON_W + 0.5 * MARGIN;
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
				&GameMinimaxDepth_ButtonClick,
				&threeButton_control, &error))
			{
				guiQuit = -1;
			}
			UINode* threeButton_node;
			if (-1 == CreateAndAddNodeToTree(threeButton_control, gameBoarBackground_node, &threeButton_node, &error))
			{
				guiQuit = -1;
			}
			if (-1 == AddToListeners(threeButton_control, &error))
			{
				guiQuit = -1;
			}

			int fourButton_x_location = threeButton_x_location + NUMBUTTON_W + 0.5 * MARGIN;
			int fourButton_y_location = oneButton_y_location;
			control* fourButton_control;
			if (-1 == Create_Button_from_bmp_transHighlight(
				BUTTON4FILENAME,
				NUMBUTTONHIGHLIGHTEDFILENAME,
				BUTTON4NAME,
				fourButton_x_location,
				fourButton_y_location,
				(Uint16)NUMBUTTON_W,
				(Uint16)NUMBUTTON_H,
				&GameMinimaxDepth_ButtonClick,
				&fourButton_control, &error))
			{
				guiQuit = -1;
			}
			UINode* fourButton_node;
			if (-1 == CreateAndAddNodeToTree(fourButton_control, gameBoarBackground_node, &fourButton_node, &error))
			{
				guiQuit = -1;
			}
			if (-1 == AddToListeners(fourButton_control, &error))
			{
				guiQuit = -1;
			}

			int bestButton_x_location = fourButton_x_location + NUMBUTTON_W + 0.5 *MARGIN;
			int bestButton_y_location = oneButton_y_location;
			control* bestButton_control;
			if (-1 == Create_Button_from_bmp_transHighlight(
				BUTTONBESTFILENAME,
				NUMBUTTONHIGHLIGHTEDFILENAME,
				BUTTONBESTNAME,
				bestButton_x_location,
				bestButton_y_location,
				(Uint16)NUMBUTTON_W,
				(Uint16)NUMBUTTON_H,
				&GameMinimaxDepth_ButtonClick, &bestButton_control, &error))
			{
				guiQuit = -1;
			}
			UINode* bestButton_node;
			if (-1 == CreateAndAddNodeToTree(bestButton_control, gameBoarBackground_node, &bestButton_node, &error))
			{
				guiQuit = -1;
			}
			if (-1 == AddToListeners(bestButton_control, &error))
			{
				guiQuit = -1;
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
		}

		HighlightBestMove(BLINKNUM);

		// DrawTree
		if (-1 == FlipTree(&error))
		{
			guiQuit = -1;
		}
	}
	else
	{
		Game();
	}
}



void GameBoardSave_ButtonClick(control* input)
{
	isSaveMode = true;

	free_move_list(curMovesList);
	curMovesList = NULL;
	free_move_list(posMovesFromCurPos);
	posMovesFromCurPos = NULL;
	free(chosenMove);
	chosenMove = NULL;

	SaveLoadMenu();
}

void HightlightPosMoves(move_list* movesToHighlight)
{
	move_list * curMove = movesToHighlight;

	if (curMove == NULL)
	{
		return;
	}
	else
	{
		move mov = curMove->mov;
		buttonsBoard[mov.end_pos.col][7 - (int)mov.end_pos.row]->ishighlighted = 1;
		curMove = curMove->next;
		HightlightPosMoves(curMove);
	}
}

bool isPawnUpgradePossible(move move, char piece)
{
	if (piece == WHITE_P || piece == BLACK_P){
		if (curSettings->next_turn == WHITE)
		{
			return move.end_pos.row == BOARD_SIZE_FROM_ZERO;
		}
		else
		{
			return move.end_pos.row == 0;
		}
	}
	return false;
}

void switchOffAllButtons()
{
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			buttonsBoard[i][j]->ishighlighted = 0;
		}
	}
}

void upgradePieces_ButtonClick(control* input)
{
	char piece = ResolveLetterFromButtonName(input->name);

	chosenMove->new_disc = piece;
	if (is_move_in_move_list(chosenMove, curMovesList) == true){
		make_move(board, chosenMove);
		SwitchButtonHighlight(gameSelectedSquare_control);
		gameSelectedSquare_control = NULL;
		curSettings->next_turn = get_opposite_color(curSettings->next_turn);
		free_move_list(curMovesList);
		curMovesList = NULL;
		free_move_list(posMovesFromCurPos);
		posMovesFromCurPos = NULL;
		free(chosenMove);
		chosenMove = NULL;
		Game();
	}

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}

void GameBoardSquare_ButtonClick(control* input)
{
	if ((curSettings->next_turn == curSettings->user_color || curSettings->game_mode == TWO_PLAYERS_GAME_MODE || isUpgrade) && gameOver == false){
		if (input == gameSelectedSquare_control)
		{
			switchOffAllButtons();
			gameSelectedSquare_control = NULL;
			free_move_list(posMovesFromCurPos);
			posMovesFromCurPos = NULL;
		}
		else if (gameSelectedSquare_control == NULL)
		{
			position* chosenPos = GetPosOfSquare(input);
			if (is_piece_of_color(board[chosenPos->col][chosenPos->row], curSettings->next_turn) == true){
				SwitchButtonHighlight(input);
				gameSelectedSquare_control = input;
				get_moves_from_pos(curMovesList, *chosenPos, &posMovesFromCurPos);
				HightlightPosMoves(posMovesFromCurPos);
			}
			free(chosenPos);
		}
		else if (gameSelectedSquare_control != NULL)
		{
			position* startPos = GetPosOfSquare(gameSelectedSquare_control);
			position* endPos = GetPosOfSquare(input);
			chosenMove = malloc(sizeof(move));//TODO checkFailure
			chosenMove->start_pos = *startPos;
			chosenMove->end_pos = *endPos;

			if (is_move_in_move_list(chosenMove, curMovesList) == true){
				if (isPawnUpgradePossible(*chosenMove, board[startPos->col][startPos->row]) == true){
					DrawPiecesOnSidePanelFilterColor(tree->children[0], &upgradePieces_ButtonClick, curSettings->next_turn);
					isUpgrade = true;
				}
				else
				{
					make_move(board, chosenMove);
					SwitchButtonHighlight(gameSelectedSquare_control);
					gameSelectedSquare_control = NULL;
					curSettings->next_turn = get_opposite_color(curSettings->next_turn);
					free_move_list(curMovesList);
					curMovesList = NULL;
					free_move_list(posMovesFromCurPos);
					posMovesFromCurPos = NULL;
					free(chosenMove);
					chosenMove = NULL;
					free(startPos);
					free(endPos);
					Game();
					return;
				}
			}
			free(startPos);
			free(endPos);
		}

		// DrawTree
		if (-1 == FlipTree(&error))
		{
			guiQuit = -1;
		}
	}
}

void ComputerTurn()
{
	if (gameOver == false && tie == false){
		struct move_list* best_move_list = NULL;
		int number_of_boards_evaluated = 0;

		int current_move_grade = get_best_moves_using_minimax(curSettings->minimax_depth, board, get_opposite_color(curSettings->user_color), get_opposite_color(curSettings->user_color), 0, curMovesList, &best_move_list, ALPHA_INIT, BETA_INIT, &number_of_boards_evaluated);

		// Check for errors
		if (FAILED_ERROR == current_move_grade) {
			free_move_list(curMovesList);
			curMovesList = NULL;
			free_move_list(best_move_list);
			// TODO: check 
			exit(EXIT_FAILURE);
		}

		// Make the move
		make_move(board, &best_move_list->mov);

		curSettings->next_turn = get_opposite_color(curSettings->next_turn);
		free_move_list(curMovesList);
		curMovesList = NULL;
		free_move_list(posMovesFromCurPos);
		posMovesFromCurPos = NULL;
		free(chosenMove);
		chosenMove = NULL;
		free_move_list(best_move_list);
		Game();
	}
}

void buildBoardUITree()
{
	control* board_control;
	if (-1 == Create_panel_from_bmp(
		CHESSBOARDFILENAME,
		CHESSBOARDNAME,
		0,
		0,
		(Uint16)BOARD_W,
		(Uint16)BOARD_H,
		&board_control,
		&error))
	{
		guiQuit = -1;
	}
	if (-1 == CreateAndAddNodeToTree(board_control, tree, &board_node, &error))
	{
		guiQuit = -1;
	}

	DrawSquareButtons(board_node, &GameBoardSquare_ButtonClick);

	DrawBoardGui(board_node);
}

void CheckGameOver()
{
	// Get the score of the board
	int score = get_board_score_for_color(board, get_opposite_color(curSettings->next_turn));

	// The game is over if the score is WIN_SCORE, LOSE_SCORE or TIE_SCORE
	if (WIN_SCORE == score) {
		print_win_message(get_opposite_color(get_opposite_color(curSettings->next_turn)));
		gameOver = true;
	}
	else if (TIE_SCORE == score && NULL == curMovesList) {
		tie = true;
	}
	else {
		if (is_check_on_color(board, curSettings->next_turn)) {
			check = true;
			print_message(CHECK);
		}
	}
}

void Game()
{
	check = false;

	FreeTree(tree);
	if (NULL != buttonsBoard){
		FreeButtonsBoard();
	}
	if (-1 == EventHandler_init(&Quit, &error))
	{
		guiQuit = -1;
	}


	gameSelectedSquare_control = NULL;

	showDepthOptions = false;

	get_moves_for_color(board, curSettings->next_turn, &curMovesList);

	CheckGameOver();

	control* window;
	if (-1 == Create_window(GAMEBOARDBACKGROUND_W, GAMEBOARDBACKGROUND_H, &window, &error))
	{
		guiQuit = -1;
	}


	if (-1 == CreateTree(window, &tree, &error))
	{
		guiQuit = -1;
	}


	control* gameBoarBackground_control;
	if (-1 == Create_panel_from_bmp(
		GAMEBOARDBACKGROUNDFILENAME,
		GAMEBOARDBACKGROUNDNAME,
		0,
		0,
		(Uint16)GAMEBOARDBACKGROUND_W,
		(Uint16)GAMEBOARDBACKGROUND_H,
		&gameBoarBackground_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* gameBoarBackground_node;
	if (-1 == CreateAndAddNodeToTree(gameBoarBackground_control, tree, &gameBoarBackground_node, &error))
	{
		guiQuit = -1;
	}

	buildBoardUITree();

	int quitButton_x_location = GAMEBOARDBACKGROUND_W - BUTTON_W - 0.5 * MARGIN;
	int quitButton_y_location = GAMEBOARDBACKGROUND_H - BUTTON_H - 1.5 * MARGIN;
	control* quitButton_control;
	if (-1 == Create_Button_from_bmp(
		BUTTONQUITFILENAME,
		BUTTONQUITFILENAME,
		BUTTONQUITNAME,
		quitButton_x_location,
		quitButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&Quit_ButtonClick,
		&quitButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* quitButton_node;
	if (-1 == CreateAndAddNodeToTree(quitButton_control, gameBoarBackground_node, &quitButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(quitButton_control, &error))
	{
		guiQuit = -1;
	}


	int bestButton_x_location = quitButton_x_location;
	int bestButton_y_location = quitButton_y_location - BUTTON_H - 1.5 * MARGIN;
	control* bestButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONBESTMOVEFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONBESTMOVENAME,
		bestButton_x_location,
		bestButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameBoardBest_ButtonClick,
		&bestButton_control, &error))
	{
		guiQuit = -1;
	}
	UINode* bestButton_node;
	if (-1 == CreateAndAddNodeToTree(bestButton_control, gameBoarBackground_node, &bestButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(bestButton_control, &error))
	{
		guiQuit = -1;
	}


	if (showDepthOptions)
	{

	}

	int saveButton_x_location = quitButton_x_location;
	int saveButton_y_location = 2 * MARGIN;
	control* saveButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONSAVEFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONSAVENAME,
		saveButton_x_location,
		saveButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameBoardSave_ButtonClick,
		&saveButton_control,
		&error))
	{
		guiQuit = -1;
	}

	UINode* saveButton_node;
	if (-1 == CreateAndAddNodeToTree(saveButton_control, gameBoarBackground_node, &saveButton_node, &error))
	{
		guiQuit = -1;
	}
	if (-1 == AddToListeners(saveButton_control, &error))
	{
		guiQuit = -1;
	}


	int mainMenuButton_x_location = quitButton_x_location;
	int mainMenuButton_y_location = saveButton_y_location + BUTTON_H + 1.5 *MARGIN;
	control* mainMenuButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONMAINMENUFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONMAINMENUNAME,
		mainMenuButton_x_location,
		mainMenuButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameBoardMainMenu_ButtonClick,
		&mainMenuButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* mainMenuButton_node;
	if (-1 == CreateAndAddNodeToTree(mainMenuButton_control, gameBoarBackground_node, &mainMenuButton_node, &error))
	{
		guiQuit;
	}
	if (-1 == AddToListeners(mainMenuButton_control, &error))
	{
		guiQuit = -1;
	}


	if (check)
	{

		char* filename = NULL;
		char* name = NULL;

		if (curSettings->next_turn == WHITE)
		{
			filename = LABELBLACKCHECKFILENAME;
			name = LABELBLACKCHECKNAME;
		}
		else
		{
			filename = LABELWHITECHECKFILENAME;
			name = LABELWHITECHECKNAME;
		}

		int checkLabel_x_location = mainMenuButton_x_location;
		int checkabel_y_location = mainMenuButton_y_location + BUTTON_H + MARGIN;

		control* checkLabel_control;
		if (-1 == Create_panel_from_bmp(
			filename,
			name,
			checkLabel_x_location,
			checkabel_y_location,
			GAMEBOARDBACKGROUND_W,
			GAMEBOARDBACKGROUND_H, &checkLabel_control, &error))
		{
			guiQuit = -1;
		}
		UINode* checkLabel_node;
		if (-1 == CreateAndAddNodeToTree(checkLabel_control, gameBoarBackground_node, &checkLabel_node, &error))
		{
			guiQuit = -1;
		}
	}

	if (gameOver)
	{
		int checkMateLabel_x_location = 0.5 * BOARD_H;
		int checkMateLabel_y_location = 0.25 * BOARD_H - 20;
		control* checkMateLabel_control;
		if (-1 == Create_panel_from_bmp(
			LABELCHECKMATEFILENAME,
			LABELCHECKMATENAME,
			checkMateLabel_x_location,
			checkMateLabel_y_location,
			GAMEBOARDBACKGROUND_W,
			GAMEBOARDBACKGROUND_H,
			&checkMateLabel_control,
			&error))
		{
			guiQuit = -1;
		}

		UINode* checkMateLabel_node;
		if (-1 == CreateAndAddNodeToTree(checkMateLabel_control, gameBoarBackground_node, &checkMateLabel_node, &error))
		{
			guiQuit = -1;
		}

		char* filename = NULL;
		char* name = NULL;

		if (curSettings->next_turn == WHITE)
		{
			filename = LABELBLACKWINSFILENAME;
			name = LABELBLACKWINSNAME;
		}
		else
		{
			filename = LABELWHITEWINSFILENAME;
			name = LABELWHITEWINSNAME;
		}

		int winsLabel_x_location = checkMateLabel_x_location;
		int winsLabel_y_location = 0.50 * BOARD_H - 20;
		control* winsLabel_control;
		if (-1 == Create_panel_from_bmp(
			filename,
			name,
			winsLabel_x_location,
			winsLabel_x_location,
			GAMEBOARDBACKGROUND_W,
			GAMEBOARDBACKGROUND_H,
			&winsLabel_control,
			&error))
		{
			guiQuit = -1;
		}
		UINode* winsLabel_node;
		if (-1 == CreateAndAddNodeToTree(winsLabel_control, gameBoarBackground_node, &winsLabel_node, &error))
		{
			guiQuit = -1;
		}
	}
	else if (tie)
	{
		int tieLabel_x_location = 0.5 * BOARD_H;
		int tieLabel_y_location = 0.25 * BOARD_H - 20;
		control* tieLabel_control;
		if (-1 == Create_panel_from_bmp(
			LABELTIEFILENAME,
			LABELTIENAME,
			tieLabel_x_location,
			tieLabel_y_location,
			GAMEBOARDBACKGROUND_W,
			GAMEBOARDBACKGROUND_H,
			&tieLabel_control,
			&error))
		{
			guiQuit = -1;
		}
		UINode* tieLabel_node;
		if (-1 == CreateAndAddNodeToTree(tieLabel_control, gameBoarBackground_node, &tieLabel_node, &error))
		{
			guiQuit = -1;
		}

		int gameOverLabel_x_location = tieLabel_x_location;
		int gameOver_y_location = 0.50 * BOARD_H - 20;
		control* gameOverLabel_control;
		if (-1 == Create_panel_from_bmp(
			LABELGAMEOVERFILENAME,
			LABELGAMEOVERNAME,
			gameOverLabel_x_location,
			gameOverLabel_x_location,
			GAMEBOARDBACKGROUND_W,
			GAMEBOARDBACKGROUND_H, 
			&gameOverLabel_control,
			&error))
		{
			guiQuit = -1;
		}
		UINode* gameOverLabel_node;
		if (-1 == CreateAndAddNodeToTree(gameOverLabel_control, gameBoarBackground_node, &gameOverLabel_control, &error))
		{
			guiQuit = -1;
		}
	}



	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}



	if (PLAYER_VS_AI_GAME_MODE == curSettings->game_mode && curSettings->next_turn != curSettings->user_color)
	{
		ComputerTurn();
	}
}
