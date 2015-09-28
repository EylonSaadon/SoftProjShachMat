#ifndef DATA_STRUCTURES_
#define DATA_STRUCTURES_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL/SDL.h>

#define perror_message(func_name) perror("Error: standard function " #func_name " has failed")

// Position - represents a column and a row in a 2 dimensional board.
struct position {
	char col;
	char row;
};

// Position list - each item contains a struct position and a pointer to the next item.
struct position_list {
	struct position pos;
	struct position_list* next;
};

// Move - represent a move - contains a start position and a list of positions to move to (in the order of the move).
struct move {
	struct position start_pos;
	struct position end_pos;
	char new_disc;
};

// Move list - each item contains a move and a pointer to the next item.
struct move_list {
	struct move mov;
	struct move_list* next;
};

// Creates position list from leaf - the leaf is the last position in the list
// Returns NULL on failure and frees pos_list
struct position_list* create_position_list_from_position_list(struct position_list* new_pos_list, struct position_list* old_pos_list);

// Add a node to a position list, returns NULL on failure
struct position_list* add_new_pos_node(struct position_list* pos_list, struct position pos);

// Free position list
void free_position_list(struct position_list* pos_list);

// Checks if 2 position lists are equal
bool is_equal_position_lists(struct position_list* pos_list1, struct position_list* pos_list2);

// Checks if a position is part of a position list
bool is_pos_in_pos_list(struct position pos, struct position_list* pos_list);

// Add a node to a move list, returns NULL on failure
struct move_list* add_new_move_node(struct move_list* move_list,
struct position start_pos,
struct position end_pos,
char new_disc);

// Add new move node helper
bool add_new_move_node_helper(struct move_list** move_list, struct position pos, struct position new_pos, char new_disc);

// Free move list
void free_move_list(struct move_list* move_node);

// Checks if 2 moves are equal
bool is_equal_moves(struct move* move1, struct move* move2);

// Checks if a move is a part of a move list
bool is_move_in_move_list(struct move* mov, struct move_list* move_list);

// Checks is 2 positions are equal
bool is_equal_pos(struct position pos1, struct position pos2);



struct control
{
	SDL_Surface* surface;
	SDL_Surface* highlighted_surface;
	SDL_Rect* location_rect;
	char* type;
	void (*Action)(struct control*);
}; typedef struct control control;

typedef void(*ButtonAction)(struct control*);

struct UINode
{
	control* control;
	int childrenCount;
	struct UINode** children;
	struct UINode* father;
};  typedef struct UINode UINode;


UINode* CreateTree(control* window);
UINode* CreateAndAddNodeToTree(control* control, UINode* father);
#endif
