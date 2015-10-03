#ifndef DEFINES_
#define DEFINES_

#define WHITE_P 'm'
#define WHITE_B 'b'
#define WHITE_N 'n'
#define WHITE_R 'r'
#define WHITE_Q 'q'
#define WHITE_K 'k'

#define BLACK_P 'M'
#define BLACK_B 'B'
#define BLACK_N 'N'
#define BLACK_R 'R'
#define BLACK_Q 'Q'
#define BLACK_K 'K'

#define EMPTY ' '

#define BOARD_SIZE 8
#define BOARD_SIZE_FROM_ZERO BOARD_SIZE - 1
#define MAX_USER_COMMAND 51
// TODO: decide what to do with this minimax best depth
#define MAX_MINIMAX_DEPTH_POSSIBLE 10 //5949

#define WIN_SCORE 1000
#define LOSE_SCORE -WIN_SCORE
#define TIE_SCORE 0
#define FAILED_ERROR 3000
#define BETA_INIT 4000
#define ALPHA_INIT -BETA_INIT

typedef char** board_t;

#define ENTER_SETTINGS "Enter game settings:\n"
#define ENTER_USER_MOVE " player - enter your move:\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 4\n"
#define WRONG_FILE_NAME "Wrong file name\n"
#define WRONG_POSITION "Invalid position on the board\n"
#define NO_DICS "The specified position does not contain your piece\n"
#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE "Illegal move\n"
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"
#define WHITE_PLAYER_WINS "Mate! White player wins the game\n"
#define BLACK_PLAYER_WINS "Mate! Black player wins the game\n"
#define TIE "The game ends in a tie\n"
#define WRONG_GAME_MODE "Wrong game mode\n"
#define RUNNING_IN_2_PLAYERS_MODE "Running game in 2 players mode\n"
#define RUNNING_IN_PLAYER_VS_COMPUTER_MODE "Running game in player vs. AI mode\n"
#define CHECK "Check!\n"
#define INVALID_BOARD "Setting this piece creates an invalid board\n"

#define perror_message(func_name) perror("Error: standard function " #func_name " has failed")
#define print_message(message) (printf("%s", message));

// Enum for representing the color options (black and white)
typedef enum { WHITE = 0, BLACK = 1 } COLOR;

// Enum for representing the turn options (computer and user)
typedef enum { COMP = 0, USER = 1 } TURN;

// Enum for representing the game mode
typedef enum { TWO_PLAYERS_GAME_MODE = 1, PLAYER_VS_AI_GAME_MODE = 2 } GAME_MODE;

// Game Settings - minimax depth and user color
struct game_settings {
	COLOR next_turn;
	GAME_MODE game_mode;
	int minimax_depth;
	COLOR user_color;
}; typedef struct game_settings game_settings;

#endif
