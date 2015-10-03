#include "SaveLoadWindow.h"


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


void SaveLoadMenu()
{
	FreeTree(tree);
	if (-1 == EventHandler_init(&Quit, &error))
	{
		guiQuit = -1;
	}

	control* window;
	if (-1 == Create_window(SAVELOAD_W, SAVELOAD_H, &window, &error))
	{
		guiQuit = -1;
	}


	if (-1 == CreateTree(window, &tree, &error))
	{
		guiQuit = -1;
	}


	char* filename = LOADMENUBACKGROUNDFILENAME;
	char* name = LOADMENUBACKGROUNDNAME;

	if (isSaveMode)
	{
		filename = SAVEMENUBACKGROUNDFILENAME;
		name = SAVEMENUBACKGROUNDFILENAME;
	}



	control* background_control;
	Create_panel_from_bmp(
		filename,
		name,
		0,
		0,
		(Uint16)SAVELOAD_W,
		(Uint16)SAVELOAD_H,
		&background_control,
		&error);
	UINode* background_node;
	if (-1 == CreateAndAddNodeToTree(background_control, tree, &background_node, &error))
	{
		guiQuit = -1;
	}


	/*int titleLabel_x_location = SAVELOAD_TITLE_LOCATION_X_CENTER-100;
	int titleLabel_y_location = MARGIN;


	

	control* titleLabel_control;
	if(-1 == Create_panel_from_bmp(
		filename,
		name,
		titleLabel_x_location,
		titleLabel_y_location,
		0,
		0,
		&titleLabel_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* titleLabel_node;
	if (-1 == CreateAndAddNodeToTree(titleLabel_control, background_node, &titleLabel_node, &error))
	{
		guiQuit = -1;
	}
*/


	for (int i = 0; i < NUMOFSLOTS; i++)
	{
		char numberstr[3];
		_itoa_s(i+1,numberstr,3,10);
		

		char* saveFileName = concat(SAVEFILNAMEPREFIX, numberstr);

		char* fileNameNoSuffix = concat(BUTTONIMGFILENAMEPREFIX, numberstr);
		char* fileName = concat(fileNameNoSuffix, ".bmp");
		control* slotButton_control;
		if( -1 == Create_Button_from_bmp_transHighlight(
			fileName,
			BUTTONSAVESLOTHIGHLIGHTFILENAME,
			saveFileName,
			2 * MARGIN + (i / 7) * BUTTON_W + MARGIN * 2,
			(Sint16)(0.15 * SAVELOAD_H + (i & 7) * (BUTTON_H + MARGIN)),
			(Uint16)BUTTON_H,
			(Uint16)BUTTON_W,
			&SaveLoadSlot_ButtonClick,
			&slotButton_control,
			&error))
		{
			guiQuit = -1;
		}
		UINode* slotButton_node;
		if (-1 == CreateAndAddNodeToTree(slotButton_control, background_node, &slotButton_node, &error))
		{
			guiQuit = -1;
		}
		if (-1 == AddToListeners(slotButton_control, &error))
		{
			guiQuit = -1;
		}


		free(saveFileName);
		free(fileNameNoSuffix);
		free(fileName);
	}


	Sint16 cancelButton_x_location = (Sint16)(SAVELOAD_W - BUTTON_W - 0.5 * MARGIN);
	Sint16 cancelButton_y_location = (Sint16)(SAVELOAD_H - BUTTON_H - 1.5 * MARGIN);
	control* cancelButton_control;
	if(-1 ==Create_Button_from_bmp_transHighlight(
		BUTTONCANCELFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONCANCELNAME,
		cancelButton_x_location,
		cancelButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&SaveLoadCancel_ButtonClick,
		&cancelButton_control,
		&error))
	{
		guiQuit = -1;
	}
	UINode* cancelButton_node;
	if (-1 == CreateAndAddNodeToTree(cancelButton_control, background_node, &cancelButton_node, &error))
	{
		guiQuit = -1;
	}
	if(-1 ==AddToListeners(cancelButton_control, &error))
		{
			guiQuit = -1;
		}

	// DrawTree
	if (-1 == FlipTree(&error))
	{
		guiQuit = -1;
	}
}