all: Chess

clean:
	-rm Data_Structures.o Chess.o Logic.o Minimax.o chessprog 

Chess: Data_Structures.o Logic.o Minimax.o UIFrameWork.o GUI.o Chess.o
	gcc -o chessprog Data_Structures.o Logic.o Minimax.o UIFrameWork.o GUI.o Chess.o -lm -std=c99 -pedantic-errors -g -lxml2 `sdl-config --libs`

Data_Structures.o: Data_Structures.h Data_Structures.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm Data_Structures.c `sdl-config --cflags`

Logic.o: Logic.h Logic.c
	gcc -I/usr/include/libxml2 -std=c99 -pedantic-errors -c -Wall -g -lm Logic.c `sdl-config --cflags`

Minimax.o: Minimax.h Minimax.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm Minimax.c `sdl-config --cflags`

UIFrameWork.o: UIFrameWork.h UIFramework.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm UIFramework.c `sdl-config --cflags`

AISetting.o: AISetting.h AISetting.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm AISetting.c `sdl-config --cflags`

CommonGameboard.o: CommonGameboard.h CommonGameboard.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm CommonGameboard.c `sdl-config --cflags`

EventHandler.o: EventHandler.h EventHandler.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm EventHandler.c `sdl-config --cflags`

GameBoard.o: GameBoard.h GameBoard.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm GameBoard.c `sdl-config --cflags`

GUI.o: GUI.h GUI.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm GUI.c `sdl-config --cflags`

MainMenu.o: MainMenu.h MainMenu.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm MainMenu.c `sdl-config --cflags`

SaveLoadWindow.o: SaveLoadWindow.h SaveLoadWindow.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm SaveLoadWindow.c `sdl-config --cflags`

SetPieces.o: SetPieces.h SetPieces.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm SetPieces.c `sdl-config --cflags`

SettingMenu.o: SettingMenu.h SettingMenu.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm SettingMenu.c `sdl-config --cflags`

Chess.o: Chess.h Chess.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Chess.c `sdl-config --cflags`