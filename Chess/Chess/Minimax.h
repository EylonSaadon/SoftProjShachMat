#ifndef MINIMAX_
#define MINIMAX_

#include "Defs.h"
#include "Data_Structures.h"

// Copies board A to board B
void copy_boards(char from_board[BOARD_SIZE][BOARD_SIZE], char to_board[BOARD_SIZE][BOARD_SIZE]);

// Get the next best moves
int get_best_moves(	int max_depth,
					char board[BOARD_SIZE][BOARD_SIZE],
					COLOR run_for_color,
					struct move_list* move_list,
					struct move_list** best_move_list,
					int* number_of_boards_evaluated);

// Get move score using minimax
int get_move_score_using_minimax(	int max_depth,
									char board[BOARD_SIZE][BOARD_SIZE],
									COLOR current_color,
									COLOR run_for_color,
									int current_depth,
									struct move_list* move_list,
									int alpha,
									int beta,
									int* number_of_boards_evaluated);

#endif
