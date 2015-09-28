#ifndef CHESS_
#define CHESS_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "Defs.h"
#include "Data_Structures.h"
#include "Logic.h"

// TODO - comments:
void console_main(char board[BOARD_SIZE][BOARD_SIZE]);

// Set the settings of the game
struct game_settings set_settings(char board[BOARD_SIZE][BOARD_SIZE]);

// Start the game
void play(char board[BOARD_SIZE][BOARD_SIZE], struct game_settings* settings);

// Handle user turn
bool user_turn(char board[BOARD_SIZE][BOARD_SIZE], struct move_list* move_list, struct game_settings* settings, COLOR color);

// Handle computer turn
void computer_turn(char board[BOARD_SIZE][BOARD_SIZE], struct move_list* move_list, struct game_settings* settings);

#endif
