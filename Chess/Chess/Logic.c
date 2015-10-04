#include "Logic.h"

#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlwriter.h>

void print_line(){
	int i;
	printf(" |");
	for (i = 1; i < BOARD_SIZE * 4; i++){
		printf("-");
	}
	printf("|\n");
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
	int i, j;
	print_line();
	for (j = BOARD_SIZE_FROM_ZERO; j >= 0; j--)
	{
		printf("%d", j + 1);
		for (i = 0; i < BOARD_SIZE; i++){
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		print_line();
	}
	printf("  ");
	for (j = 0; j < BOARD_SIZE; j++){
		printf(" %c  ", (char)('a' + j));
	}
	printf("\n");
}

void init_board(char board[BOARD_SIZE][BOARD_SIZE]){
	set_line_in_board(board, 0, "rnbqkbnr");
	set_line_in_board(board, 1, "mmmmmmmm");
	set_line_in_board(board, 6, "MMMMMMMM");
	set_line_in_board(board, 7, "RNBQKBNR");

	for (int i = 2; i <= 5; i++) {
		set_line_in_board(board, i, "________");
	}
}

bool is_valid_position(struct position pos) {
	return (pos.col >= 0 && pos.col <= BOARD_SIZE_FROM_ZERO && pos.row >= 0 && pos.row <= BOARD_SIZE_FROM_ZERO);
}


void set_line_in_board(char board[BOARD_SIZE][BOARD_SIZE], int line_number, const char line[BOARD_SIZE]) {
	for (int j = 0; j < BOARD_SIZE; j++) {
		if (line[j] == '_') {
			board[j][line_number] = EMPTY;
		}
		else {
			board[j][line_number] = line[j];
		}
	}
}

void load_game_from_xml_rec(xmlNode * a_node, struct game_settings* settings, char board[BOARD_SIZE][BOARD_SIZE])
{
	for (xmlNode *cur_node = a_node; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE) {
			if (!strcmp((const char*)cur_node->name, "next_turn")) {
				if (!strcmp((const char*)cur_node->children->content, "White")) {
					settings->next_turn = WHITE;
				}
				else {
					settings->next_turn = BLACK;
				}
			}

			if (!strcmp((const char*)cur_node->name, "game_mode")) {
				settings->game_mode = atoi((const char*)cur_node->children->content);
			}

			if (!strcmp((const char*)cur_node->name, "difficulty") && cur_node->children != NULL) {
				if (!strcmp((const char*)cur_node->children->content, "best")) {
					settings->minimax_depth = MAX_MINIMAX_DEPTH_POSSIBLE;
				}
				else {
					settings->minimax_depth = atoi((const char*)cur_node->children->content);
				}
			}

			if (!strcmp((const char*)cur_node->name, "user_color") && cur_node->children != NULL) {
				if (!strcmp((const char*)cur_node->children->content, "White")) {
					settings->user_color = WHITE;
				}
				else {
					settings->user_color = BLACK;
				}
			}

			if (!strcmp((const char*)cur_node->name, "board")) {
				int i = BOARD_SIZE - 1;
				for (xmlNode *cur_child = cur_node->children; cur_child; cur_child = cur_child->next) {
					if (cur_child->type == XML_ELEMENT_NODE) {
						set_line_in_board(board, i, (const char*)cur_child->children->content);
						i--;
					}
				}
			}
		}

		load_game_from_xml_rec(cur_node->children, settings, board);
	}
}

int load_game_from_xml(char* file_path, struct game_settings* settings, char board[BOARD_SIZE][BOARD_SIZE]) {
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;

	// Parse the file and get the DOM
	if ((doc = xmlReadFile(file_path, NULL, 0)) == NULL) {
		printf("ERROR: Failed to parse file %s\n", file_path);
		return -1;
	}
	else {
		root_element = xmlDocGetRootElement(doc);

		load_game_from_xml_rec(root_element, settings, board);

		// Clean
		xmlFreeDoc(doc);       // free document
		xmlCleanupParser();    // Free globals
	}
	return 0;
}

bool is_valid_set(char board[BOARD_SIZE][BOARD_SIZE], char disc, struct position pos, COLOR color) {
	if ((WHITE_P == disc && 7 == pos.row) || (BLACK_P == disc && 0 == pos.row)) {
		return false;
	}

	int queen_count = 0;
	int bishop_count = 0;
	int knight_count = 0;
	int king_count = 0;
	int pawn_count = 0;
	int rook_count = 0;

	switch (disc) {
	case WHITE_P:
	case BLACK_P:
		pawn_count++;
		break;

	case WHITE_B:
	case BLACK_B:
		bishop_count++;
		break;

	case WHITE_N:
	case BLACK_N:
		knight_count++;
		break;

	case WHITE_R:
	case BLACK_R:
		rook_count++;
		break;

	case WHITE_Q:
	case BLACK_Q:
		queen_count++;
		break;

	case WHITE_K:
	case BLACK_K:
		king_count++;
		break;
	}

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (!is_piece_of_color(board[i][j], color)) {
				continue;
			}

			switch (board[i][j]) {
			case WHITE_P:
			case BLACK_P:
				pawn_count++;
				break;

			case WHITE_B:
			case BLACK_B:
				bishop_count++;
				break;

			case WHITE_N:
			case BLACK_N:
				knight_count++;
				break;

			case WHITE_R:
			case BLACK_R:
				rook_count++;
				break;

			case WHITE_Q:
			case BLACK_Q:
				queen_count++;
				break;

			case WHITE_K:
			case BLACK_K:
				king_count++;
				break;
			}
		}
	}

	return (2 >= rook_count && 1 >= king_count && 2 >= bishop_count && 2 >= knight_count && 8 >= pawn_count && 1 >= queen_count);
}

bool is_valid_board_init(char board[BOARD_SIZE][BOARD_SIZE])
{
	bool is_white_king_exist = false;
	bool is_black_king_exist = false;

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (WHITE_K == board[i][j]) {
				is_white_king_exist = true;
			}
			else if (BLACK_K == board[i][j]) {
				is_black_king_exist = true;
			}
		}
	}

	return (is_black_king_exist && is_white_king_exist);
}

void print_move(struct move* mov) {
	printf("<%c,%hu> to <%c,%hu>", mov->start_pos.col + 'a', mov->start_pos.row + 1, mov->end_pos.col + 'a', mov->end_pos.row + 1);

	if (EMPTY != mov->new_disc) {
		char* new_disc = NULL;

		switch (mov->new_disc) {
		case WHITE_P:
		case BLACK_P:
			new_disc = "pawn";
			break;

		case WHITE_B:
		case BLACK_B:
			new_disc = "bishop";
			break;

		case WHITE_N:
		case BLACK_N:
			new_disc = "knight";
			break;

		case WHITE_R:
		case BLACK_R:
			new_disc = "rook";
			break;

		case WHITE_Q:
		case BLACK_Q:
			new_disc = "queen";
			break;
		}

		printf(" %s", new_disc);
	}

	printf("\n");
}

void print_moves_from_pos(struct move_list* moves, struct position pos) {
	if (NULL == moves) {
		return;
	}

	struct move_list* current_move = moves;
	do {
		if (is_equal_pos(pos, current_move->mov.start_pos)) {
			print_move(&current_move->mov);
		}
	} while (NULL != (current_move = current_move->next));
}

int get_moves_from_pos(move_list* moves, struct position pos, move_list** possible_moves) {
	if (NULL == moves) {
		return 0;
	}

	move_list* current_move = moves;
	do {
		if (is_equal_pos(pos, current_move->mov.start_pos)) {
			if (!add_new_move_node_helper(possible_moves, pos, current_move->mov.end_pos, EMPTY)) return -1;
		}
		current_move = current_move->next;
	} while (NULL != current_move);

	return 0;
}

void print_win_message(COLOR winner_color) {
	if (WHITE == winner_color) {
		printf(WHITE_PLAYER_WINS);
	}
	else {
		printf(BLACK_PLAYER_WINS);
	}
}

COLOR get_opposite_color(COLOR color) {
	if (WHITE == color) {
		return BLACK;
	}

	return WHITE;
}

int save_game_to_xml(char* file_path, struct game_settings* settings, char board[BOARD_SIZE][BOARD_SIZE]) {
	int rc;
	xmlTextWriterPtr writer;

	// Create a new XmlWriter for uri, with no compression.
	writer = xmlNewTextWriterFilename(file_path, 0);
	if (writer == NULL) {
		printf("testXmlwriterFilename: Error creating the xml writer\n");
		return -1;
	}

	// Start the document with the xml default for the version
	rc = xmlTextWriterStartDocument(writer, NULL, "UTF-8", NULL);
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterStartDocument\n");
		return -1;
	}

	rc = xmlTextWriterStartElement(writer, BAD_CAST "game");
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
		return -1;
	}

	rc = xmlTextWriterWriteElement(writer, BAD_CAST "next_turn", settings->next_turn ? BAD_CAST "Black" : BAD_CAST "White");
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
		return -1;
	}

	rc = xmlTextWriterWriteElement(writer, BAD_CAST "game_mode", settings->game_mode == 1 ? BAD_CAST "1" : BAD_CAST "2");
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
		return -1;
	}

	if (settings->game_mode == 2) {
		if (settings->minimax_depth == 0) {
			rc = xmlTextWriterWriteElement(writer, BAD_CAST "difficulty", BAD_CAST "best");
		}
		else {
			char snum[2];
			sprintf(snum, "%d", settings->minimax_depth);
			rc = xmlTextWriterWriteElement(writer, BAD_CAST "difficulty", BAD_CAST snum);
		}

	}
	else {
		rc = xmlTextWriterWriteElement(writer, BAD_CAST "difficulty", BAD_CAST "");
	}

	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
		return -1;
	}

	if (settings->game_mode == 2) {
		rc = xmlTextWriterWriteElement(writer, BAD_CAST "user_color", settings->user_color ? BAD_CAST "Black" : BAD_CAST "White");
	}
	else {
		rc = xmlTextWriterWriteElement(writer, BAD_CAST "user_color", BAD_CAST "");
	}

	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
		return -1;
	}

	rc = xmlTextWriterStartElement(writer, BAD_CAST "board");
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
		return -1;
	}

	for (int i = BOARD_SIZE_FROM_ZERO; i >= 0; i--) {
		char row_string[9] = { 0 };
		for (int j = 0; j <= BOARD_SIZE_FROM_ZERO; j++) {
			row_string[j] = board[j][i] == EMPTY ? '_' : board[j][i];
		}

		char row_title_string[6];
		sprintf(row_title_string, "row_%d", i + 1);

		rc = xmlTextWriterWriteElement(writer, BAD_CAST row_title_string, BAD_CAST row_string);
		if (rc < 0) {
			printf("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
			return -1;
		}
	}

	rc = xmlTextWriterEndDocument(writer);
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterEndDocument\n");
		return -1;
	}

	xmlFreeTextWriter(writer);

	// Cleaning
	xmlCleanupCharEncodingHandlers();
	xmlCleanupParser();

	return 0;
}

struct position find_king_pos(char board[BOARD_SIZE][BOARD_SIZE], COLOR color) {
	struct position pos = { 0 };

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if ((board[i][j] == WHITE_K || board[i][j] == BLACK_K) && is_piece_of_color(board[i][j], color)) {
				pos.col = i;
				pos.row = j;
				return pos;
			}
		}
	}

	return pos;
}

bool is_check_on_color(char board[BOARD_SIZE][BOARD_SIZE], COLOR color) {
	struct position pos = find_king_pos(board, color);

	// Check chess from queen, bishop, rook or king
	for (int i = 0; i <= 7; i++) {
		// Choose direction
		int diff_col = 0;
		int diff_row = 0;

		switch (i) {
		case 0:
			diff_col = 1;
			diff_row = 1;
			break;
		case 1:
			diff_col = -1;
			diff_row = 1;
			break;
		case 2:
			diff_col = 1;
			diff_row = -1;
			break;
		case 3:
			diff_col = -1;
			diff_row = -1;
			break;
		case 4:
			diff_col = 1;
			diff_row = 0;
			break;
		case 5:
			diff_col = -1;
			diff_row = 0;
			break;
		case 6:
			diff_col = 0;
			diff_row = 1;
			break;
		case 7:
			diff_col = 0;
			diff_row = -1;
			break;
		}

		struct position new_pos = pos;
		new_pos.col += diff_col;
		new_pos.row += diff_row;

		bool first_iter = true;
		while (is_valid_position(new_pos)) {
			char piece = get_piece(board, new_pos);

			if (piece == EMPTY) {
				new_pos.col += diff_col;
				new_pos.row += diff_row;
			}
			else {
				if (!is_piece_of_color(piece, color)) {
					if ((WHITE_Q == piece || BLACK_Q == piece) ||
						(i <= 3 && (WHITE_B == piece || BLACK_B == piece)) ||
						(i >= 4 && (WHITE_R == piece || BLACK_R == piece)) ||
						((WHITE_K == piece || BLACK_K == piece) && first_iter)) {
						return true;
					}
				}

				break;
			
			}
			first_iter = false;
		}
	}

	// Check chess from pawn
	if ((WHITE == color && pos.row != 7 && ((pos.col != 7 && BLACK_P == board[pos.col + 1][pos.row + 1]) || (pos.col != 0 && BLACK_P == board[pos.col - 1][pos.row + 1]))) ||
		(BLACK == color && pos.row != 0 && ((pos.col != 7 && WHITE_P == board[pos.col + 1][pos.row - 1]) || (pos.col != 0 && WHITE_P == board[pos.col - 1][pos.row - 1])))) {
		return true;
	}

	// Check chess from knight
	for (int i = 0; i <= 7; i++) {
		// Choose direction
		int diff_col = 0;
		int diff_row = 0;

		switch (i) {
		case 0:
			diff_col = -1;
			diff_row = 2;
			break;
		case 1:
			diff_col = -2;
			diff_row = 1;
			break;
		case 2:
			diff_col = -2;
			diff_row = -1;
			break;
		case 3:
			diff_col = -1;
			diff_row = -2;
			break;
		case 4:
			diff_col = 1;
			diff_row = -2;
			break;
		case 5:
			diff_col = 2;
			diff_row = -1;
			break;
		case 6:
			diff_col = 2;
			diff_row = 1;
			break;
		case 7:
			diff_col = 1;
			diff_row = 2;
			break;
		}

		struct position knight_pos = pos;
		knight_pos.col += diff_col;
		knight_pos.row += diff_row;

		char possible_knight = get_piece(board, knight_pos);

		if (is_valid_position(knight_pos) && !is_piece_of_color(possible_knight, color) && (possible_knight == WHITE_N || possible_knight == BLACK_N)) {
			return true;
		}
	}

	return false;
}

bool is_check_move(char board[BOARD_SIZE][BOARD_SIZE], struct position start_pos, struct position end_pos, char new_disc, COLOR color) {
	struct move mov;
	mov.start_pos = start_pos;
	mov.end_pos = end_pos;
	mov.new_disc = new_disc;

	char start_pos_disc = get_piece(board, start_pos);
	char end_pos_disc = get_piece(board, end_pos);

	// Make the move we want to check
	make_move(board, &mov);

	int ret = is_check_on_color(board, color);

	set_piece(board, start_pos, start_pos_disc);
	set_piece(board, end_pos, end_pos_disc);

	return ret;
}

int get_moves_pawn_last_row(char board[BOARD_SIZE][BOARD_SIZE], struct position pos, struct position new_pos, COLOR color, struct move_list** move_list) {
	char rook = (color == WHITE ? WHITE_R : BLACK_R);
	char queen = (color == WHITE ? WHITE_Q : BLACK_Q);
	char bishop = (color == WHITE ? WHITE_B : BLACK_B);
	char knight = (color == WHITE ? WHITE_N : BLACK_N);

	if (!is_check_move(board, pos, new_pos, rook, color)) {
		if (!add_new_move_node_helper(move_list, pos, new_pos, rook)) return -1;
	}

	if (!is_check_move(board, pos, new_pos, queen, color)) {
		if (!add_new_move_node_helper(move_list, pos, new_pos, queen)) return -1;
	}

	if (!is_check_move(board, pos, new_pos, bishop, color)) {
		if (!add_new_move_node_helper(move_list, pos, new_pos, bishop)) return -1;
	}

	if (!is_check_move(board, pos, new_pos, knight, color)) {
		if (!add_new_move_node_helper(move_list, pos, new_pos, knight)) return -1;
	}

	return 0;
}

int get_moves_pawn(char board[BOARD_SIZE][BOARD_SIZE], struct position pos, COLOR color, struct move_list** move_list) {
	int direction = (color == WHITE ? 1 : -1);

	struct position new_pos;
	new_pos = pos;
	new_pos.row += direction;

	if (is_valid_position(new_pos) && get_piece(board, new_pos) == EMPTY) {
		if (BOARD_SIZE_FROM_ZERO == new_pos.row || 0 == new_pos.row) {
			if (-1 == get_moves_pawn_last_row(board, pos, new_pos, color, move_list)) return -1;
		}
		else {
			if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
				if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
			}
		}
	}

	new_pos = pos;
	new_pos.row += direction;
	new_pos.col += direction;

	if (is_valid_position(new_pos) && is_piece_of_color(board[pos.col + direction][pos.row + direction], get_opposite_color(color))) {
		if (BOARD_SIZE_FROM_ZERO == new_pos.row || 0 == new_pos.row) {
			if (-1 == get_moves_pawn_last_row(board, pos, new_pos, color, move_list)) return -1;
		}
		else {
			if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
				if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
			}
		}
	}

	new_pos = pos;
	new_pos.row += direction;
	new_pos.col -= direction;
	if (is_valid_position(new_pos) && is_piece_of_color(board[pos.col - direction][pos.row + direction], get_opposite_color(color))) {
		if (BOARD_SIZE_FROM_ZERO == new_pos.row || 0 == new_pos.row) {
			if (-1 == get_moves_pawn_last_row(board, pos, new_pos, color, move_list)) return -1;
		}
		else {
			if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
				if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
			}
		}
	}

	return 0;
}

int get_moves_bishop(char board[BOARD_SIZE][BOARD_SIZE], struct position pos, COLOR color, struct move_list** move_list) {
	for (int i = 0; i < 4; i++) {
		// Choose direction
		int diff_col = 0;
		int diff_row = 0;

		switch (i) {
		case 0:
			diff_col = 1;
			diff_row = 1;
			break;
		case 1:
			diff_col = -1;
			diff_row = 1;
			break;
		case 2:
			diff_col = 1;
			diff_row = -1;
			break;
		case 3:
			diff_col = -1;
			diff_row = -1;
			break;
		}

		struct position new_pos = pos;
		new_pos.col += diff_col;
		new_pos.row += diff_row;

		while (is_valid_position(new_pos)) {
			char piece = get_piece(board, new_pos);

			if (piece == EMPTY) {
				if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
					if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
				}
			}
			else if (is_piece_of_color(piece, color)) {
				break;
			}
			else {
				if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
					if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
				}

				break;
			}

			new_pos.col += diff_col;
			new_pos.row += diff_row;
		}
	}

	return 0;
}

int get_moves_rook(char board[BOARD_SIZE][BOARD_SIZE], struct position pos, COLOR color, struct move_list** move_list) {
	for (int i = 0; i < 4; i++) {
		// Choose direction
		int diff_col = 0;
		int diff_row = 0;

		switch (i) {
		case 0:
			diff_col = 1;
			diff_row = 0;
			break;
		case 1:
			diff_col = -1;
			diff_row = 0;
			break;
		case 2:
			diff_col = 0;
			diff_row = 1;
			break;
		case 3:
			diff_col = 0;
			diff_row = -1;
			break;
		}

		struct position new_pos = pos;
		new_pos.col += diff_col;
		new_pos.row += diff_row;

		while (is_valid_position(new_pos)) {
			char piece = get_piece(board, new_pos);

			if (piece == EMPTY) {
				if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
					if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
				}
			}
			else if (is_piece_of_color(piece, color)) {
				break;
			}
			else {
				if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
					if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
				}

				break;
			}

			new_pos.col += diff_col;
			new_pos.row += diff_row;
		}
	}

	return 0;
}

int get_moves_knight(char board[BOARD_SIZE][BOARD_SIZE], struct position pos, COLOR color, struct move_list** move_list) {
	for (int i = 0; i <= 7; i++) {
		// Choose direction
		int diff_col = 0;
		int diff_row = 0;

		switch (i) {
		case 0:
			diff_col = -1;
			diff_row = 2;
			break;
		case 1:
			diff_col = -2;
			diff_row = 1;
			break;
		case 2:
			diff_col = -2;
			diff_row = -1;
			break;
		case 3:
			diff_col = -1;
			diff_row = -2;
			break;
		case 4:
			diff_col = 1;
			diff_row = -2;
			break;
		case 5:
			diff_col = 2;
			diff_row = -1;
			break;
		case 6:
			diff_col = 2;
			diff_row = 1;
			break;
		case 7:
			diff_col = 1;
			diff_row = 2;
			break;
		}

		struct position new_pos = pos;
		new_pos.col += diff_col;
		new_pos.row += diff_row;

		if (is_valid_position(new_pos)) {
			char piece = get_piece(board, new_pos);

			if (piece == EMPTY) {
				if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
					if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
				}
			}
			else if (is_piece_of_color(piece, color)) {
				continue;
			}
			else {
				if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
					if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
				}

				continue;
			}
		}
	}

	return 0;
}

int get_moves_king(char board[BOARD_SIZE][BOARD_SIZE], struct position pos, COLOR color, struct move_list** move_list) {
	for (int i = 0; i <= 7; i++) {
		// Choose direction
		int diff_col = 0;
		int diff_row = 0;

		switch (i) {
		case 0:
			diff_col = 1;
			diff_row = 1;
			break;
		case 1:
			diff_col = -1;
			diff_row = 1;
			break;
		case 2:
			diff_col = 1;
			diff_row = -1;
			break;
		case 3:
			diff_col = -1;
			diff_row = -1;
			break;
		case 4:
			diff_col = 1;
			diff_row = 0;
			break;
		case 5:
			diff_col = -1;
			diff_row = 0;
			break;
		case 6:
			diff_col = 0;
			diff_row = 1;
			break;
		case 7:
			diff_col = 0;
			diff_row = -1;
			break;
		}

		struct position new_pos = pos;
		new_pos.col += diff_col;
		new_pos.row += diff_row;

		if (is_valid_position(new_pos)) {
			char piece = get_piece(board, new_pos);

			if (piece == EMPTY) {
				if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
					if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
				}
			}
			else if (is_piece_of_color(piece, color)) {
				continue;
			}
			else {
				if (!is_check_move(board, pos, new_pos, EMPTY, color)) {
					if (!add_new_move_node_helper(move_list, pos, new_pos, EMPTY)) return -1;
				}

				continue;
			}
		}
	}

	return 0;
}

int get_moves_queen(char board[BOARD_SIZE][BOARD_SIZE], struct position pos, COLOR color, struct move_list** move_list) {
	if (-1 == get_moves_bishop(board, pos, color, move_list)) {
		return -1;
	}

	if (-1 == get_moves_rook(board, pos, color, move_list)) {
		return -1;
	}

	return 0;
}

int get_moves_for_color(char board[BOARD_SIZE][BOARD_SIZE], COLOR color, struct move_list** move_list) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (!is_piece_of_color(board[i][j], color)) {
				continue;
			}

			struct position current_pos = { 0 };
			current_pos.col = i;
			current_pos.row = j;

			switch (board[i][j]) {
			case WHITE_P:
			case BLACK_P:
				if (-1 == get_moves_pawn(board, current_pos, color, move_list)) return -1;
				break;

			case WHITE_B:
			case BLACK_B:
				if (-1 == get_moves_bishop(board, current_pos, color, move_list)) return -1;
				break;

			case WHITE_N:
			case BLACK_N:
				if (-1 == get_moves_knight(board, current_pos, color, move_list)) return -1;
				break;

			case WHITE_R:
			case BLACK_R:
				if (-1 == get_moves_rook(board, current_pos, color, move_list)) return -1;
				break;

			case WHITE_Q:
			case BLACK_Q:
				if (-1 == get_moves_queen(board, current_pos, color, move_list)) return -1;
				break;

			case WHITE_K:
			case BLACK_K:
				if (-1 == get_moves_king(board, current_pos, color, move_list)) return -1;
				break;
			}
		}
	}

	return 0;
}

char get_piece_from_string(char* piece_string, COLOR color) {
	char piece;

	if (0 == strcmp(piece_string, "queen")) {
		piece = BLACK_Q;
	}
	else if (0 == strcmp(piece_string, "rook")) {
		piece = BLACK_R;
	}
	else if (0 == strcmp(piece_string, "bishop")) {
		piece = BLACK_B;
	}
	else if (0 == strcmp(piece_string, "knight")) {
		piece = BLACK_N;
	}
	else if (0 == strcmp(piece_string, "pawn")) {
		piece = BLACK_P;
	}
	else if (0 == strcmp(piece_string, "king")) {
		piece = BLACK_K;
	}

	if (WHITE == color) {
		piece += 'a' - 'A';
	}

	return piece;
}

int parse_move_string(char* move_string, struct move* mov, COLOR color)
{
	char piece[7] = { 0 };
	unsigned short start_row = -1;
	unsigned short end_row = -1;
	if (4 != sscanf(move_string, "move <%c,%hu> to <%c,%hu>", &mov->start_pos.col, &start_row, &mov->end_pos.col, &end_row)) {
		perror_message("sscanf");
		return -1;
	}

	mov->start_pos.col -= 'a';
	mov->start_pos.row = start_row - 1;
	mov->end_pos.col -= 'a';
	mov->end_pos.row = end_row - 1;

	if ('\n' != (move_string + 19)[0] && '\0' != (move_string + 19)[0]) {
		if (1 == sscanf(move_string + 19, " %s", piece)) {
			mov->new_disc = get_piece_from_string(piece, color);
		}
		else {
			perror_message("sscanf");
			return -1;
		}
	}

	return 0;
}

bool is_valid_move_positions(struct move* mov)
{
	return is_valid_position(mov->start_pos) && is_valid_position(mov->end_pos);
}

bool is_piece_of_color(char disc, COLOR color)
{
	return ((WHITE == color && disc >= 'a' && disc <= 'z') || (BLACK == color && disc >= 'A' && disc <= 'Z'));
}

void set_piece(char board[BOARD_SIZE][BOARD_SIZE], struct position pos, char piece) {
	board[(int)pos.col][(int)pos.row] = piece;
}

char get_piece(char board[BOARD_SIZE][BOARD_SIZE], struct position pos) {
	return board[(int)pos.col][(int)pos.row];
}

void make_move(char board[BOARD_SIZE][BOARD_SIZE], struct move* mov)
{
	// Move the disc
	char disc = get_piece(board, mov->start_pos);

	set_piece(board, mov->start_pos, EMPTY);

	// Check if the disc is pawn and if it in the last row
	if ((WHITE_P == disc && BOARD_SIZE_FROM_ZERO == mov->end_pos.row) || (BLACK_P == disc && 0 == mov->end_pos.row)) {
		set_piece(board, mov->end_pos, mov->new_disc);
	}
	else {
		set_piece(board, mov->end_pos, disc);
	}
}

int get_board_score_for_color(char board[BOARD_SIZE][BOARD_SIZE], COLOR color) {
	unsigned int white = 0;
	unsigned int black = 0;

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			switch (board[i][j])
			{
			case WHITE_R:
				white += 5;
				break;
			case WHITE_P:
				white++;
				break;
			case WHITE_Q:
				white += 9;
				break;
			case WHITE_N:
			case WHITE_B:
				white += 3;
				break;
			case WHITE_K:
				white += 400;
				break;

			case BLACK_R:
				black += 5;
				break;
			case BLACK_P:
				black++;
				break;
			case BLACK_Q:
				black += 9;
				break;
			case BLACK_N:
			case BLACK_B:
				black += 3;
				break;
			case BLACK_K:
				black += 400;
				break;

			case EMPTY:
				break;
			}
		}
	}

	struct move_list* moves = NULL;
	if (WHITE == color) {
		if (-1 == get_moves_for_color(board, BLACK, &moves)) return FAILED_ERROR;

		if (NULL == moves) {
			// Check for mate
			if (is_check_on_color(board, BLACK)) {
				return WIN_SCORE;
			}
			else {
				return TIE_SCORE;
			}
		}
		else {
			free_move_list(moves);
			return white - black;
		}
	}
	else {
		if (-1 == get_moves_for_color(board, WHITE, &moves)) return FAILED_ERROR;

		if (NULL == moves) {
			// Check for mate
			if (is_check_on_color(board, WHITE)) {
				return LOSE_SCORE;
			}
			else {
				return TIE_SCORE;
			}
		}
		else {
			free_move_list(moves);
			return black - white;
		}
	}

	return FAILED_ERROR;
}