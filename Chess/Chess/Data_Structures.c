#include "Data_Structures.h"

bool is_equal_pos(struct position pos1, struct position pos2) {
	return pos1.col == pos2.col && pos1.row == pos2.row;
}

void free_move_list(struct move_list* move_node) {
	if (NULL == move_node) {
		return;
	}

	do {
		struct move_list* next_move_node = move_node->next;
		free(move_node);
		move_node = next_move_node;
	} while (NULL != move_node);
}

struct move_list* add_new_move_node(struct move_list* move_list,
                                    struct position start_pos,
									struct position end_pos, char new_disc) {
	struct move_list* move_node = (struct move_list*)calloc(1, sizeof(struct move_list));

	if (NULL == move_node) {
		perror_message("calloc");
		return NULL;
	}

	move_node->mov.start_pos = start_pos;
	move_node->mov.end_pos = end_pos;
	move_node->mov.new_disc = new_disc;

	if (NULL != move_list) {
		move_node->next = move_list;
	}

	return move_node;
}

bool is_equal_moves(struct move* move1, struct move* move2) {
	return is_equal_pos(move1->start_pos, move2->start_pos) && is_equal_pos(move1->end_pos, move2->end_pos);
}

bool add_new_move_node_helper(struct move_list** move_list, struct position pos, struct position new_pos, char new_disc) {
	struct move_list* temp_move_list = add_new_move_node(*move_list, pos, new_pos, new_disc);

	if (NULL == temp_move_list) {
		return false;
	}

	*move_list = temp_move_list;

	return true;
}

bool is_move_in_move_list(struct move* mov, struct move_list* move_list)
{
	struct move_list* current_move_node = move_list;
	do {
        if (is_equal_moves(&current_move_node->mov, mov)) {
            return true;
        }
	} while (NULL != (current_move_node = current_move_node->next));

	return false;
}

UINode* CreateTree(control* window)
{
	UINode* root = (UINode*)malloc(sizeof(UINode));
	root->control = window;
	root->childrenCount = 0;
	root->childrenSize = INITIALCHILDRENSIZE;
	root->children = (UINode**)malloc(sizeof(UINode*) * root->childrenSize);
	root->father = NULL;
	root->root = root;
	return root;
}

void addNodeAsChild(UINode* node, UINode* father)
{
	if (father->childrenCount == father->childrenSize)
	{
		father->childrenSize *= 2;
		father->children = realloc(father->children, sizeof(UINode*) * father->childrenSize);
	}
	father->childrenCount ++;
	father->children[father->childrenCount - 1] = node;

	node->father = father;
	node->root = father->root;
}

UINode* CreateAndAddNodeToTree(control* control, UINode* father){
	UINode* node = (UINode*)malloc(sizeof(UINode));
	node->control = control;
	node->childrenCount = 0;
	node->childrenSize = INITIALCHILDRENSIZE;
	node->children = (UINode**)malloc(sizeof(UINode*) * node->childrenSize);
	node->father = NULL;

	addNodeAsChild(node, father);

	return node;
}