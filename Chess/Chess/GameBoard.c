#include "GameBoard.h"

void Square_ButtonClick(control* input)
{
	SwitchButtonHighlight(input);

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}

int StartGame()
{
	FreeTree(tree);
	EventHandler_init(&Quit);

	control* window = Create_window(BOARD_W, BOARD_H);
	tree = CreateTree(window);

	control* board_control = Create_panel_from_bmp(
		CHESSBOARDFILENAME,
		CHESSBOARDNAME,
		0,
		0,
		(Uint16)BOARD_W,
		(Uint16)BOARD_H);

	UINode* board_node = CreateAndAddNodeToTree(board_control, tree);

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			control* square = Create_Button_from_bmp(
				SQUAREBUTTONFILENAME,
				SQUAREBUTTONHIGHLIGHTEDFILENAME,
				SQUAREBUTTONNAME,
				MARGIN + (i*SQUARE_W),
				MARGIN + (j*SQUARE_H),
				(Uint16)SQUARE_W,
				(Uint16)SQUARE_H,
				&Square_ButtonClick);
			UINode* newGameButton_node = CreateAndAddNodeToTree(square, board_node);
			AddToListeners(square);
		}
	}

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}
