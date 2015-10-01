#include "Data_Structures.h"

struct position_list* add_new_pos_node(struct position_list* pos_list, struct position pos) {
	struct position_list* pos_node = (struct position_list*)calloc(1, sizeof(struct position_list));

	if (NULL == pos_node) {
		perror_message("calloc");
		return NULL;
	}

	pos_node->pos = pos;

	if (NULL != pos_list) {
		pos_node->next = pos_list;
	}

	return pos_node;
}

bool is_equal_pos(struct position pos1, struct position pos2) {
	return pos1.col == pos2.col && pos1.row == pos2.row;
}

void free_position_list(struct position_list* pos_list) {
	if (NULL == pos_list) {
		return;
	}

	free_position_list(pos_list->next);

	free(pos_list);
}

//void free_move_list(struct move_list* move_node) {
//	if (NULL == move_node) {
//		return;
//	}
//
//    free_move_list(move_node->next);
//
//	free(move_node);
//}

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

struct position_list* create_position_list_from_position_list(struct position_list* new_pos_list, struct position_list* old_pos_list) {
	struct position_list* current_pos = old_pos_list;
    do {
		if (NULL != current_pos->next) {
			struct position_list* new_pos_node = add_new_pos_node(new_pos_list, current_pos->pos);

			if (NULL == new_pos_node) {
				free_position_list(new_pos_list);
				return NULL;
			}

			new_pos_list = new_pos_node;
        }
	} while (NULL != (current_pos = current_pos->next));

	return new_pos_list;
}

bool is_equal_position_lists(struct position_list* pos_list1, struct position_list* pos_list2) {
	if (NULL == pos_list1 || NULL == pos_list2) {
		return false;
	}

	struct position_list* current_pos_node1 = pos_list1;
	struct position_list* current_pos_node2 = pos_list2;
	do {
		if (!is_equal_pos(current_pos_node1->pos, current_pos_node2->pos)) {
			return false;
		}

		current_pos_node1 = current_pos_node1->next;
		current_pos_node2 = current_pos_node2->next;
	} while (NULL != current_pos_node1 && NULL != current_pos_node2);

	return (NULL == current_pos_node1 && NULL == current_pos_node2);
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

bool is_pos_in_pos_list(struct position pos, struct position_list* pos_list) {
	if (NULL == pos_list) {
		return false;
	}

	struct position_list* current_pos = pos_list;
	do {
		if (is_equal_pos(pos, current_pos->pos)) {
			return true;
		}
	} while (NULL != (current_pos = current_pos->next));

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