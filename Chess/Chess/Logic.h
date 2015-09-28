#ifndef LOGIC_
#define LOGIC_

#include <stdio.h>
#include <stdbool.h>
#include "Defs.h"
#include "Data_Structures.h"

// Validates the board initialization
bool is_valid_board_init(char board[BOARD_SIZE][BOARD_SIZE]);

// Checks if board is empty
bool is_empty_board(char board[BOARD_SIZE][BOARD_SIZE]);

// Prints the board
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);

// Prints a line
void print_line();

// Checks if a position is valid
bool is_valid_position(struct position pos);

// Initialize the board to the start position
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);

// Get possible moves for a color, returns 0 on success or -1 on failure
int get_moves_for_color(char board[BOARD_SIZE][BOARD_SIZE], COLOR color, struct move_list** move_list);

// Parses move string (from user), returns 0 on success or -1 on failure
int parse_move_string(char* move_string, struct move* mov, COLOR color);

// Checks the validation of the positions of a move
bool is_valid_move_positions(struct move* mov);

// Checks if piece is of a specific color
bool is_piece_of_color(char disc, COLOR color);

// Prints a move
void print_move(struct move* mov);

// Prints move list
void print_moves_from_pos(struct move_list* moves, struct position pos);

// Get opposite color (if white returns black, and vice versa)
COLOR get_opposite_color(COLOR color);

// Prints win message
void print_win_message(COLOR winner_color);

// Set a piece by a position
void set_piece(char board[BOARD_SIZE][BOARD_SIZE], struct position pos, char piece);

// Returns a piece by a position
char get_piece(char board[BOARD_SIZE][BOARD_SIZE], struct position pos);

// Make a move
void make_move(char board[BOARD_SIZE][BOARD_SIZE], struct move* mov);

// Gets board score for color
int get_board_score_for_color(char board[BOARD_SIZE][BOARD_SIZE], COLOR color);

// TODO: add comments
void set_line_in_board(char board[BOARD_SIZE][BOARD_SIZE], int line_number, const char line[BOARD_SIZE]);
bool is_check_on_color(char board[BOARD_SIZE][BOARD_SIZE], COLOR color);
char get_piece_from_string(char* piece_string, COLOR color);
void load_game_from_xml(char* file_path, struct game_settings* settings, char board[BOARD_SIZE][BOARD_SIZE]);
bool is_valid_set(char board[BOARD_SIZE][BOARD_SIZE], char disc, struct position pos, COLOR color);
int save_game_to_xml(char* file_path, struct game_settings* settings, char board[BOARD_SIZE][BOARD_SIZE]);

#endif
