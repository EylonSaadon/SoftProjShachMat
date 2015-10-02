#include "SaveLoadWindow.h"


char* concat(char *s1, char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1);

	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

void SaveLoadCancel_ButtonClick(control* input)
{
	if (isSaveMode)
	{
		Game();
	}
	else{
		MainMenu();
	}
}

void SaveLoadSlot_ButtonClick(control* input)
{
	// TODO: take care of memory leak
	// TODO: handle File not found
	char* path = input->name;
	if (isSaveMode)
	{
		FILE* file = fopen(path, "w");
		if (NULL != file) {
			fclose(file);
			save_game_to_xml(path, curSettings, board);
		}
		Game();
	}
	else{
		FILE* file = fopen(path, "r");
		if (NULL != file) {
			fclose(file);
			load_game_from_xml(path, curSettings, board);
		}
		SettingMenu();
	}
		
}


int SaveLoadMenu()
{
	FreeTree(tree);
	EventHandler_init(&Quit);

	control* window = Create_window(SAVELOAD_W, SAVELOAD_H);
	tree = CreateTree(window);

	control* background_control = Create_panel_from_bmp(
		SAVELOADBACKGROUNDFILENAME,
		SAVELOADBACKGROUNDNAME,
		0,
		0,
		(Uint16)SAVELOAD_W,
		(Uint16)SAVELOAD_H);
	UINode* background_node = CreateAndAddNodeToTree(background_control, tree);


	int titleLabel_x_location = SAVELOAD_TITLE_LOCATION_X_CENTER-100;
	int titleLabel_y_location = MARGIN;

	char* filename = LABELLOADGAMEFILENAME;
	char* name = LABELLOADGAMENAME;

	if (isSaveMode)
	{
		filename = LABELSAVEGAMEFILENAME;
		name = LABELSAVEGAMENAME;
	}

	control* titleLabel_control = Create_panel_from_bmp(
		filename,
		name,
		titleLabel_x_location,
		titleLabel_y_location,
		0,
		0);
	UINode* titleLabel_node = CreateAndAddNodeToTree(titleLabel_control, background_node);



	for (int i = 0; i < NUMOFSLOTS; i++)
	{
		char c = i + 1 + '0';
		char* numberstr[2];
		numberstr[0] = c;
		numberstr[1] = NULL;

		char* saveFileName = concat(SAVEFILNAMEPREFIX, numberstr);

		char* fileNameNoSuffix = concat(BUTTONIMGFILENAMEPREFIX, numberstr);
		char* fileName = concat(fileNameNoSuffix, ".bmp");
		control* slotButton_control = Create_Button_from_bmp_transHighlight(
			fileName,
			BUTTONSAVESLOTHIGHLIGHTFILENAME,
			saveFileName,
			2 * MARGIN + (i % 3) * BUTTONSAVESLOT_W + MARGIN *2,
			0.20 * SAVELOAD_H + (i / 3) * BUTTONSAVESLOT_H + MARGIN,
			(Uint16)BUTTONSAVESLOT_H,
			(Uint16)BUTTONSAVESLOT_W,
			&SaveLoadSlot_ButtonClick);
		UINode* slotButton_node = CreateAndAddNodeToTree(slotButton_control, background_node);
		AddToListeners(slotButton_control);


		free(saveFileName);
		free(fileNameNoSuffix);
		free(fileName);
	}


	int cancelButton_x_location = MARGIN;
	int cancelButton_y_location = SAVELOAD_H - BUTTON_H - MARGIN * 2;
	control* cancelButton_control = Create_Button_from_bmp_transHighlight(
		BUTTONCANCELFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONCANCELNAME,
		cancelButton_x_location,
		cancelButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&SaveLoadCancel_ButtonClick);
	UINode* cancelButton_node = CreateAndAddNodeToTree(cancelButton_control, background_node);
	AddToListeners(cancelButton_control);

	DrawTree(tree);
	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}
}