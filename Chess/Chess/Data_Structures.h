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
}; typedef struct position position;

// Move - represent a move - contains a start position, end position and new_disc if needed
struct move {
	struct position start_pos;
	struct position end_pos;
	char new_disc;
}; typedef struct move move;

// Move list - each item contains a move and a pointer to the next item.
struct move_list {
	struct move mov;
	struct move_list* next;
}; typedef struct move_list move_list;

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

// initial number of children for a node
#define INITIALCHILDRENSIZE 100


// All Panels, buttons, and windows will be controls with different types.
struct control
{
	SDL_Surface* surface;
	SDL_Surface* highlighted_surface;
	SDL_Rect* location_rect;
	char* type;
	char* name;
	bool ishighlighted;
	void (*Action)(struct control*);
}; typedef struct control control;

// A pointer for a function. each control of type button will hold one that points to the function that need to be called when it is pressed.
typedef void(*ButtonAction)(struct control*);

// a Node in the UI tree. holds the dontrol to draw
struct UINode
{
	control* control;
	int childrenCount;
	int childrenSize;
	struct UINode** children;
	struct UINode* father;
	struct UINode* root;
};  typedef struct UINode UINode;

// Creates a UINode that will be the rot of our new tree
int CreateTree(control* window, UINode** node_ret, char** error);

// adds a given node as the child of the given father.
int addNodeAsChild(UINode* node, UINode* father, char** error);

// takes a given control and creates a control out of it and adds it as a one of the children of the given father
int CreateAndAddNodeToTree(control* control, UINode* father, UINode** node, char** error);

// Given two strings the Function concats both of them, in failure returns NULL. if succesful the ret value should be freed.
char* concat(char *s1, char *s2);
#endif

