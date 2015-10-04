#include "SaveLoadWindow.h"

#include <stdio.h>

void SaveLoadCancel_ButtonClick(control* input)
{
	if (isSaveMode)
	{
		Game();
		return;
	}
	else{
		MainMenu();
		return;
	}
}

void SaveLoadSlot_ButtonClick(control* input)
{
	char* path = input->name;
	if (isSaveMode)
	{
		FILE* file = fopen(path, "w");
		if (NULL != file) {
			fclose(file);
			if(-1 == save_game_to_xml(path, curSettings, board))
			{
				guiQuit = -1;
				return;
			}
			Game();
			return;
		}
	}
	else{
		FILE* file = fopen(path, "r");
		if (NULL != file) {
			fclose(file);
			if (-1 == load_game_from_xml(path, curSettings, board))
			{
				guiQuit = -1;
				return;
			}
			SettingMenu();
			return;
		}
	}

}


void SaveLoadMenu()
{
	FreeTree(tree);
	if (-1 == EventHandler_init(&Quit, &error_global))
	{
		guiQuit = -1;
		return;
	}

	control* window;
	if (-1 == Create_window(SAVELOAD_W, SAVELOAD_H, &window, &error_global))
	{
		guiQuit = -1;
		return;
	}


	if (-1 == CreateTree(window, &tree, &error_global))
	{
		FreeControl(window);
		guiQuit = -1;
		return;
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
		&error_global);
	UINode* background_node;
	if (-1 == CreateAndAddNodeToTree(background_control, tree, &background_node, &error_global))
	{
		FreeControl(background_control);
		guiQuit = -1;
		return;
	}

	for (int i = 0; i < NUMOFSLOTS; i++)
	{
		char numberstr[3];
		_itoa_s(i + 1, numberstr, 3, 10);


		char* saveFileName = concat(SAVEFILNAMEPREFIX, numberstr);

		char* fileNameNoSuffix = concat(BUTTONIMGFILENAMEPREFIX, numberstr);
		char* fileName = concat(fileNameNoSuffix, ".bmp");
		control* slotButton_control;
		if (-1 == Create_Button_from_bmp_transHighlight(
			fileName,
			BUTTONSAVESLOTHIGHLIGHTFILENAME,
			saveFileName,
			2 * MARGIN + (i / 6) * BUTTON_W + MARGIN * 2,
			(Sint16)(0.15 * SAVELOAD_H + (i % 6) * (BUTTON_H + MARGIN)),
			(Uint16)BUTTON_H,
			(Uint16)BUTTON_W,
			&SaveLoadSlot_ButtonClick,
			&slotButton_control,
			&error_global))
		{
			guiQuit = -1;
			return;
		}
		UINode* slotButton_node;
		if (-1 == CreateAndAddNodeToTree(slotButton_control, background_node, &slotButton_node, &error_global))
		{
			FreeControl(slotButton_control);
			guiQuit = -1;
			return;
		}
		if (-1 == AddToListeners(slotButton_control, &error_global))
		{
			guiQuit = -1;
			return;
		}


		free(saveFileName);
		free(fileNameNoSuffix);
		free(fileName);
	}


	Sint16 cancelButton_x_location = (Sint16)(SAVELOAD_W - BUTTON_W - 0.5 * MARGIN);
	Sint16 cancelButton_y_location = (Sint16)(SAVELOAD_H - BUTTON_H - 1.5 * MARGIN);
	control* cancelButton_control;
	if (-1 == Create_Button_from_bmp_transHighlight(
		BUTTONCANCELFILENAME,
		BUTTONTRANSPARENTHIGHLIGHTEDFILENAME,
		BUTTONCANCELNAME,
		cancelButton_x_location,
		cancelButton_y_location,
		(Uint16)BUTTON_W,
		(Uint16)BUTTON_H,
		&SaveLoadCancel_ButtonClick,
		&cancelButton_control,
		&error_global))
	{
		guiQuit = -1;
		return;
	}
	UINode* cancelButton_node;
	if (-1 == CreateAndAddNodeToTree(cancelButton_control, background_node, &cancelButton_node, &error_global))
	{
		FreeControl(cancelButton_control);
		guiQuit = -1;
		return;
	}
	if (-1 == AddToListeners(cancelButton_control, &error_global))
	{
		guiQuit = -1;
		return;
	}

	// DrawTree
	if (-1 == FlipTree(&error_global))
	{
		guiQuit = -1;
		return;
	}
}