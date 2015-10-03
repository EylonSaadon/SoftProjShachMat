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

int CreateTree(control* window, UINode** node_ret, char** error)
{
	UINode* root = (UINode*)malloc(sizeof(UINode));
	if (NULL == root)
	{
		*node_ret = NULL;
		*error = "ERROR: Failed allocatin memory for UINode.";
		return -1;
	}

	root->control = window;
	root->childrenCount = 0;
	root->childrenSize = INITIALCHILDRENSIZE;
	root->children = (UINode**)malloc(sizeof(UINode*) * root->childrenSize);
	if (NULL == root->children)
	{
		free(root);
		root = NULL;
		*node_ret = NULL;
		*error = "ERROR: Failed allocatin memory for UINode array (children of a node).";
		return -1;
	}
	root->father = NULL;
	root->root = root;

	*node_ret = root;

	return 0;
}

int addNodeAsChild(UINode* node, UINode* father, char** error)
{
	if (father->childrenCount == father->childrenSize)
	{
		father->childrenSize *= 2;

		UINode** tmp = (UINode**)malloc(sizeof(UINode*) * father->childrenSize);
		if (NULL == tmp)
		{
			// not freeing the children array because the father should still be part of a tree that will be freed in an orderly fashion.
			*error = "ERROR: Failed trying to allocate memory for UINode array (while enlarging the children array).";
			return -1;
		}

		for (int i = 0; i < father->childrenCount; i++)
		{
			tmp[i] = father->children[i];
		}

		father->children = tmp;
	}

	father->childrenCount ++;
	father->children[father->childrenCount - 1] = node;

	node->father = father;
	node->root = father->root;
}

int CreateAndAddNodeToTree(control* control, UINode* father, UINode** node, char** error){

	(*node) = (UINode*)malloc(sizeof(UINode));
	if (NULL == (*node))
	{
		*node = NULL;
		*error = "ERROR: Failed allocatin memory for UINode.";
		return -1;
	}

	(*node)->control = control;
	(*node)->childrenCount = 0;
	(*node)->childrenSize = INITIALCHILDRENSIZE;
	(*node)->father = NULL;

	(*node)->children = (UINode**)malloc(sizeof(UINode*) * (*node)->childrenSize);
	if (NULL == (*node)->children)
	{
		free(*node);
		*node = NULL;
		*error = "ERROR: Failed allocatin memory for UINode array (children of a node).";
		return -1;
	}

	if (-1 == addNodeAsChild((*node), father, error))
	{
		free((*node)->children);
		(*node)->children = NULL;
		free(*node);
		*node = NULL;
		return -1;
	}
}

char* concat(char *s1, char *s2)
{
	char* result= malloc(strlen(s1) + strlen(s2) + 1);
	if (NULL == result)
	{
		return NULL;
	}

	strcpy(result, s1);
	strcat(result, s2);
	return result;
}