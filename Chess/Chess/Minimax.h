#ifndef MINIMAX_
#define MINIMAX_

#include "Defs.h"
#include "Data_Structures.h"

// Copies board A to board B
void copy_boards(char from_board[BOARD_SIZE][BOARD_SIZE], char to_board[BOARD_SIZE][BOARD_SIZE]);

// Get the next best move using minimax algorithm
int get_best_moves_using_minimax(	int max_depth,
									char board[BOARD_SIZE][BOARD_SIZE],
									COLOR current_color,
									COLOR run_for_color,
									int current_depth,
									struct move_list* move_list,
									struct move_list** best_move_list,
									int alpha,
									int beta,
									int* number_of_boards_evaluated);

#endif
