#include "Minimax.h"

#include "Logic.h"

void copy_boards(char from_board[BOARD_SIZE][BOARD_SIZE], char to_board[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			to_board[i][j] = from_board[i][j];
		}
	}
}

int get_best_moves(	int max_depth,
					char board[BOARD_SIZE][BOARD_SIZE],
					COLOR run_for_color,
					struct move_list* move_list,
					struct move_list** best_move_list,
					int* number_of_boards_evaluated) {
	int grade = -4000;
	int current_depth = 0;

	struct move_list* current_move_node = move_list;
	do {
		// Temp board for current move
		char minimax_board[BOARD_SIZE][BOARD_SIZE];

		(*number_of_boards_evaluated)++;

		// Copies the board to a temp board
		copy_boards(board, minimax_board);

		// Make the move we want to check
		make_move(minimax_board, &current_move_node->mov);

		int score = get_board_score_for_color(minimax_board, run_for_color);

		int current_move_grade = FAILED_ERROR;

		// Stop condition - if we got to the max depth or there is a winner
		if (max_depth == current_depth + 1 || WIN_SCORE == score || LOSE_SCORE == score) {
			current_move_grade = score;
		}
		else {
			// Get the color of the next turn
			COLOR next_color = get_opposite_color(run_for_color);

			// Get the move list for the next turn
			struct move_list* minimax_move_list = NULL;

			if (-1 == get_moves_for_color(minimax_board, next_color, &minimax_move_list)) {
				// get_moves_for_color failed
				return FAILED_ERROR;
			}

			// Checks if there is no moves for the next turn
			if (NULL == minimax_move_list) {
				current_move_grade = score;
			}
			else {
				// Run minimax again with the new board and position
				current_move_grade = get_move_score_using_minimax(max_depth, minimax_board, next_color, run_for_color, current_depth + 1, minimax_move_list, ALPHA_INIT, BETA_INIT, number_of_boards_evaluated);
				free_move_list(minimax_move_list);

				// If return value is FAILED_ERROR there was an error with a standard function
				if (FAILED_ERROR == current_move_grade) {
					return FAILED_ERROR;
				}
			}
		}

		// Update the grade if it the first move or take the max grade or the min grade according to the depth
		if (current_move_grade >= grade) {
			if (current_move_grade > grade) {
				free_move_list(*best_move_list);
				*best_move_list = NULL;
			}

			struct move_list* temp = add_new_move_node(*best_move_list, current_move_node->mov.start_pos, current_move_node->mov.end_pos, current_move_node->mov.new_disc);
			if (NULL == temp) {
				return FAILED_ERROR;
			}
			*best_move_list = temp;

			grade = current_move_grade;
		}
	} while (NULL != (current_move_node = current_move_node->next));

	return grade;
}

int get_move_score_using_minimax(	int max_depth,
									char board[BOARD_SIZE][BOARD_SIZE],
									COLOR current_color,
									COLOR run_for_color,
									int current_depth,
									struct move_list* move_list,
									int alpha, int
									beta,
									int* number_of_boards_evaluated) {
	
	bool maximizingPlayer = current_depth % 2 == 0 ? true : false;

	int grade = 4000;
	if (maximizingPlayer) {
		grade *= -1;
	}

	struct move_list* current_move_node = move_list;
	do {
		// Temp board for current move
		char minimax_board[BOARD_SIZE][BOARD_SIZE];

		(*number_of_boards_evaluated)++;

		// Copies the board to a temp board
		copy_boards(board, minimax_board);

		// Make the move we want to check
		make_move(minimax_board, &current_move_node->mov);

		int score = get_board_score_for_color(minimax_board, run_for_color);

		int current_move_grade = FAILED_ERROR;

		// Stop condition - if we got to the max depth or there is a winner
		if (max_depth == current_depth + 1 || WIN_SCORE == score || LOSE_SCORE == score) {
			current_move_grade = score;
		}
		else {
			// Get the color of the next turn
			COLOR next_color = get_opposite_color(current_color);

			// Get the move list for the next turn
			struct move_list* minimax_move_list = NULL;

			if (-1 == get_moves_for_color(minimax_board, next_color, &minimax_move_list)) {
				// get_moves_for_color failed
				return FAILED_ERROR;
			}

			// Checks if there is no moves for the next turn
			if (NULL == minimax_move_list) {
				current_move_grade = score;
			}
			else {
				// Run minimax again with the new board and position
				current_move_grade = get_move_score_using_minimax(max_depth, minimax_board, next_color, run_for_color, current_depth + 1, minimax_move_list, alpha, beta, number_of_boards_evaluated);
				free_move_list(minimax_move_list);

				// If return value is FAILED_ERROR there was an error with a standard function
				if (FAILED_ERROR == current_move_grade) {
					return FAILED_ERROR;
				}
			}
		}

		if (maximizingPlayer) {
			grade = grade > current_move_grade ? grade : current_move_grade;
			alpha = alpha > grade ? alpha : grade;
		}
		else {
			grade = grade < current_move_grade ? grade : current_move_grade;
			beta = beta < grade ? beta : grade;
		}

		if (beta <= alpha) {
			break;
		}

	} while (NULL != (current_move_node = current_move_node->next));

	return grade;
}