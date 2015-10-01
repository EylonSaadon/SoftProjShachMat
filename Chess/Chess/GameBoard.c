#include "GameBoard.h"


control* gameSelectedSquare_control;

void GameBoardMainMenu_ButtonClick(control* input)
{
	MainMenu();
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

int isPawnUpgradePossible(move move)
{
	if (curSettings->next_turn == WHITE)
	{
		return move.end_pos.row == BOARD_SIZE_FROM_ZERO;
	}
	else
	{
		return move.end_pos.row == 0;
	}
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

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
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
			chosenMove = malloc(sizeof(move));
			chosenMove->start_pos = *startPos;
			chosenMove->end_pos= *endPos;

			if (is_move_in_move_list(chosenMove, curMovesList) == true){
				if (isPawnUpgradePossible(*chosenMove) == true){
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

		DrawTree(tree);
		/* We finished drawing*/
		if (SDL_Flip(tree->control->surface) != 0) {
			printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
		}
	}
}

void ComputerTurn()
{
	if (gameOver == false){
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
	control* board_control = Create_panel_from_bmp(
		CHESSBOARDFILENAME,
		                  CHESSBOARDNAME,
		                  0,
		                  0,
		                  (Uint16)BOARD_W,
		                  (Uint16)BOARD_H);
	board_node = CreateAndAddNodeToTree(board_control, tree);

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
		gameOver = true;
	}
	else {
		if (is_check_on_color(board, curSettings->next_turn)) {
			// TODO: should turn to messagebox
			print_message(CHECK);
		}
	}
}

int Game()
{
	FreeTree(tree);
	if (NULL != buttonsBoard){
		FreeButtonsBoard();
	}
	EventHandler_init(&Quit);

	selectedSquare_Control = NULL;
	selectedPiece_Control = NULL;

	get_moves_for_color(board, curSettings->next_turn, &curMovesList);

	CheckGameOver();

	posMovesFromCurPos = NULL;

	control* window = Create_window(GAMEBOARDBACKGROUND_W, GAMEBOARDBACKGROUND_H);
	tree = CreateTree(window);


	control* gameBoarBackground_control = Create_panel_from_bmp(
		GAMEBOARDBACKGROUNDFILENAME,
		GAMEBOARDBACKGROUNDNAME,
		0,
		0,
		(Uint16)GAMEBOARDBACKGROUND_W,
		(Uint16)GAMEBOARDBACKGROUND_H);
	UINode* gameBoarBackground_node = CreateAndAddNodeToTree(gameBoarBackground_control, tree);

	buildBoardUITree();

	int quitButton_x_location = GAMEBOARDBACKGROUND_W - BUTTON_W - 0.5 * MARGIN;
	int quitButton_y_location = GAMEBOARDBACKGROUND_H - BUTTON_H - 1.5 * MARGIN;
	control* quitButton_control = Create_Button_from_bmp(
		BUTTONQUITFILENAME,
		BUTTONQUITFILENAME,
		BUTTONQUITNAME,
		quitButton_x_location,
		quitButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&Quit_ButtonClick);
	UINode* quitButton_node = CreateAndAddNodeToTree(quitButton_control, gameBoarBackground_node);
	AddToListeners(quitButton_control);

	int saveButton_x_location = quitButton_x_location;
	int saveButton_y_location = 2 * MARGIN;
	control* saveButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONSAVEFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONSAVENAME,
		saveButton_x_location,
		saveButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameBoardSave_ButtonClick);
	UINode* saveButton_node = CreateAndAddNodeToTree(saveButton_control, gameBoarBackground_node);
	AddToListeners(saveButton_control);

	int mainMenuButton_x_location = quitButton_x_location;
	int mainMenuButton_y_location = saveButton_y_location + BUTTON_H + 1.5 *MARGIN;
	control* mainMenuButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONMAINMENUFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONMAINMENUNAME,
		mainMenuButton_x_location,
		mainMenuButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&GameBoardMainMenu_ButtonClick);
	UINode* mainMenuButton_node = CreateAndAddNodeToTree(mainMenuButton_control, gameBoarBackground_node);
	AddToListeners(mainMenuButton_control);

	if (gameOver)
	{
		//TODO: addLabel
	}


	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}



	if (PLAYER_VS_AI_GAME_MODE == curSettings->game_mode && curSettings->next_turn != curSettings->user_color)
	{
		ComputerTurn();
	}
}
