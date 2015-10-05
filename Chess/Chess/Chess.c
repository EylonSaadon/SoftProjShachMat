#include "Chess.h"

#include "Minimax.h"
#include "GUI.h"

int main(int argc, char* argv[])
{
	char board[BOARD_SIZE][BOARD_SIZE];

	init_board(board);

	if (1 == argc || !strcmp(argv[1], "console")) {
		console_main(board);
	}
	else {
		start_gui();
	}

	return 0;
}

void console_main(char board[BOARD_SIZE][BOARD_SIZE]) {
	print_board(board);

	game_settings settings = set_settings(board);

	play(board, &settings);
}

game_settings set_settings(char board[BOARD_SIZE][BOARD_SIZE])
{
	struct game_settings settings = { .next_turn = WHITE, .game_mode = 1, .minimax_depth = 1, .user_color = WHITE };

	print_message(ENTER_SETTINGS);

	char input[MAX_USER_COMMAND];

	while (fgets(input, MAX_USER_COMMAND, stdin) != NULL) {
		// Set game_mode
		if (strstr(input, "game_mode ") == input) {
			int game_mode = atoi(input + 10);

			switch (game_mode) {
			case 1:
				print_message(RUNNING_IN_2_PLAYERS_MODE);
				settings.game_mode = game_mode;
				break;
			case 2:
				print_message(RUNNING_IN_PLAYER_VS_COMPUTER_MODE);
				settings.game_mode = game_mode;
				break;
			default:
				print_message(WRONG_GAME_MODE);
			}
		}
		// Set difficulty
		else if (strstr(input, "difficulty ") == input && PLAYER_VS_AI_GAME_MODE == settings.game_mode) {
			if (strstr(input, "best") == input) {
				settings.minimax_depth = get_best_depth(board);
			}
			else {
				input[12] = 0;
				int minimax_depth = atoi(input + 11);

				if (minimax_depth < 1 || minimax_depth > 4) {
					print_message(WRONG_MINIMAX_DEPTH);
				}
				else {
					settings.minimax_depth = minimax_depth;
				}
			}
		}
		// Set user_color
		else if (strstr(input, "user_color ") == input && PLAYER_VS_AI_GAME_MODE == settings.game_mode) {
			char* color = input + 11;
			if (0 == strcmp(color, "black\n")) {
				settings.user_color = BLACK;
			}
		}
		// Load settings
		else if (strstr(input, "load ") == input) {
			*strstr(input, "\n") = 0;
			char* file_path = input + 5;
			FILE* file = fopen(file_path, "r");

			if (NULL != file) {
				fclose(file);
				if (-1 == load_game_from_xml(file_path, &settings, board))
				{
					exit(EXIT_FAILURE);
				}
			}
			else {
				print_message(WRONG_FILE_NAME);
			}

			print_board(board);
		}
		// Clear board
		else if (strstr(input, "clear\n") == input) {
			for (int i = 0; i < BOARD_SIZE; i++){
				for (int j = 0; j < BOARD_SIZE; j++){
					board[i][j] = EMPTY;
				}
			}
		}
		// Set next_player
		else if (strstr(input, "next_player ") == input) {
			char* color = input + 12;
			if (0 == strcmp(color, "black\n")) {
				settings.next_turn = BLACK;
			}
		}
		// Remove disc
		else if (strstr(input, "rm ") == input) {
			struct position pos = { 0 };

			unsigned short row = -1;
			if (2 != sscanf(input, "rm <%c,%hu>\n", &pos.col, &row)) {
				perror_message("sscanf");
				exit(0);
			}

			pos.col -= 'a';
			pos.row = row - 1;

			if (is_valid_position(pos)) {
				set_piece(board, pos, EMPTY);
			}
			else {
				print_message(WRONG_POSITION);
			}
		}
		// Set disc
		else if (strstr(input, "set ") == input) {
			struct position pos = { 0 };
			char color_string[6] = { 0 };
			char piece_string[7] = { 0 };

			unsigned short row = -1;
			if (4 != sscanf(input, "set <%c,%hu> %s %s\n", &pos.col, &row, color_string, piece_string)) {
				perror_message("sscanf");
				exit(0);
			}

			pos.col -= 'a';
			pos.row = row - 1;

			COLOR color = BLACK;
			if ('w' == color_string[0]) {
				color = WHITE;
			}

			char piece = get_piece_from_string(piece_string, color);

			if (is_valid_position(pos)) {
				if (is_valid_set(board, piece, pos, color)) {
					set_piece(board, pos, piece);
				}
				else {
					print_message(INVALID_BOARD);
				}
			}
			else {
				print_message(WRONG_POSITION);
			}
		}
		// Print
		else if (strstr(input, "print\n") == input) {
			print_board(board);
		}
		// Quit
		else if (strstr(input, "quit\n") == input) {
			exit(EXIT_SUCCESS);
		}
		// Start
		else if (strstr(input, "start\n") == input) {
			if (is_valid_board_init(board)) {
				return settings;
			}
			else {
				print_message(WROND_BOARD_INITIALIZATION);
			}
		}
		// Illegal command
		else {
			print_message(ILLEGAL_COMMAND);
		}

		print_message(ENTER_SETTINGS);
	}

	// User finished to set the settings and never started the game
	exit(0);
}

void play(char board[BOARD_SIZE][BOARD_SIZE], struct game_settings* settings)
{
	bool should_continue = true;

	while (should_continue) {

		// Get the possible moves of the current player
		struct move_list* moves = NULL;
		if (-1 == get_moves_for_color(board, settings->next_turn, &moves)) {
			exit(0);
		}

		// Get the score of the board
		int score = get_board_score_for_color(board, get_opposite_color(settings->next_turn));

		// The game is over if the score is WIN_SCORE, LOSE_SCORE or TIE_SCORE
		if (WIN_SCORE == score) {
			print_win_message(get_opposite_color(settings->next_turn));
			break;
		}
		else if (TIE_SCORE == score && NULL == moves) {
			print_message(TIE);
			break;
		}
		else {
			if (is_check_on_color(board, settings->next_turn)) {
				print_message(CHECK);
			}
		}

		// Computer turn
		if (PLAYER_VS_AI_GAME_MODE == settings->game_mode && settings->next_turn != settings->user_color) {
			computer_turn(board, moves, settings);
		}
		// User turn
		else {
			should_continue = user_turn(board, moves, settings, settings->next_turn);
		}

		free_move_list(moves);

		if (should_continue) {
			print_board(board);
		}

		settings->next_turn = get_opposite_color(settings->next_turn);
	}
}

void computer_turn(char board[BOARD_SIZE][BOARD_SIZE], struct move_list* move_list, struct game_settings* settings)
{
	struct move_list* best_move_list = NULL;
	int number_of_boards_evaluated = 0;

	// Get the best next move
	int current_move_grade = get_best_moves(settings->minimax_depth, board, get_opposite_color(settings->user_color), move_list, &best_move_list, &number_of_boards_evaluated);

	// Check for errors
	if (FAILED_ERROR == current_move_grade) {
		free_move_list(move_list);
		free_move_list(best_move_list);
		exit(EXIT_FAILURE);
	}

	// Make the move
	make_move(board, &best_move_list->mov);

	// Prints move
	printf("Computer: move ");
	print_move(&best_move_list->mov);

	free_move_list(best_move_list);
}

bool user_turn(char board[BOARD_SIZE][BOARD_SIZE], struct move_list* move_list, struct game_settings* settings, COLOR color)
{
	if (WHITE == color) {
		printf("White");
	}
	else {
		printf("Black");
	}

	print_message(ENTER_USER_MOVE);

	char input[MAX_USER_COMMAND];

	while (fgets(input, MAX_USER_COMMAND, stdin) != NULL) {
		
		bool should_print_enter_user_move = true;

		// Move
		if (strstr(input, "move ") == input) {
			struct move mov = { .start_pos = { 0 }, .end_pos = { 0 }, .new_disc = EMPTY };

			if (-1 == parse_move_string(input, &mov, color)) {
				free_move_list(move_list);
				exit(EXIT_FAILURE);
			}

			if (!is_valid_move_positions(&mov)) {
				print_message(WRONG_POSITION);
			}
			else if (!is_piece_of_color(get_piece(board, mov.start_pos), color)) {
				print_message(NO_DICS);
			}
			else if (!is_move_in_move_list(&mov, move_list)) {
				print_message(ILLEGAL_MOVE)
			}
			// The move is ok
			else {
				make_move(board, &mov);

				return true;
			}
		}
		// Get moves
		else if (strstr(input, "get_moves ") == input) {

			char col;
			unsigned short row;

			if (2 != sscanf(input, "get_moves <%c,%hu>", &col, &row)) {
				perror_message("sscanf");
				return -1;
			}

			struct position pos;
			pos.col = col - 'a';
			pos.row = row - 1;

			if (!is_valid_position(pos)) {
				print_message(WRONG_POSITION);
			}
			else if (!is_piece_of_color(get_piece(board, pos), color)) {
				print_message(NO_DICS);
			}
			// The pos is ok
			else {
				print_moves_from_pos(move_list, pos);
			}
		}
		// Get best moves
		else if (strstr(input, "get_best_moves ") == input) {
			int minimax_depth = 0;

			if (strstr(input, "get_best_moves best") == input) {
				minimax_depth = get_best_depth(board);
			}
			else {
				minimax_depth = atoi(input + 15);

				if (minimax_depth < 1 || minimax_depth > 4) {
					print_message(WRONG_MINIMAX_DEPTH);
					continue;
				}
			}

			struct move_list* best_move_list = NULL;
			int number_of_boards_evaluated = 0;

			// Get the best next move
			int current_move_grade = get_best_moves(minimax_depth, board, color, move_list, &best_move_list, &number_of_boards_evaluated);

			// Check for errors
			if (FAILED_ERROR == current_move_grade) {
				free_move_list(move_list);
				free_move_list(best_move_list);
				exit(EXIT_FAILURE);
			}

			struct move_list* current_move_node = best_move_list;
			do {
				print_move(&current_move_node->mov);
			} while (NULL != (current_move_node = current_move_node->next));

			free_move_list(best_move_list);
		}
		// Get Score
		else if (strstr(input, "get_score ") == input) {
			int minimax_depth = 0;
			char* move_string;

			if (strstr(input, "best ") == input) {
				minimax_depth = get_best_depth(board);
				move_string = input + 15;
			}
			else {
				minimax_depth = atoi(input + 10);

				if (minimax_depth < 1 || minimax_depth > 4) {
					print_message(WRONG_MINIMAX_DEPTH);
					continue;
				}

				move_string = input + 12;
			}

			struct move mov = { .start_pos = { 0 }, .end_pos = { 0 }, .new_disc = EMPTY };

			if (-1 == parse_move_string(move_string, &mov, color)) {
				exit(EXIT_FAILURE);
			}

			struct move_list one_move_list;
			one_move_list.mov = mov;
			one_move_list.next = NULL;

			struct move_list* best_move_list = NULL;
			int number_of_boards_evaluated = 0;

			// Get the best next move
			int current_move_grade = get_best_moves(minimax_depth, board, color, &one_move_list, &best_move_list, &number_of_boards_evaluated);

			// Check for errors
			if (FAILED_ERROR == current_move_grade) {
				free_move_list(move_list);
				free_move_list(best_move_list);
				exit(EXIT_FAILURE);
			}

			printf("%d\n", current_move_grade);

			free_move_list(best_move_list);
		}
		// Save
		else if (strstr(input, "save ") == input) {
			*strstr(input, "\n") = 0;
			char* file_path = input + 5;
			FILE* file = fopen(file_path, "w");

			if (NULL != file) {
				fclose(file);
				if (-1 == save_game_to_xml(file_path, settings, board)) {
					return false;
				}
			}
			else {
				print_message(WRONG_FILE_NAME);
			}
		}
		// Quit
		else if (strstr(input, "quit\n") == input) {
			return false;
		}
		// Illegal command
		else {
			print_message(ILLEGAL_COMMAND);
		}

		if (should_print_enter_user_move) {
			if (WHITE == color) {
				printf("White");
			}
			else {
				printf("Black");
			}

			print_message(ENTER_USER_MOVE);
		}
	}

	return false;
}