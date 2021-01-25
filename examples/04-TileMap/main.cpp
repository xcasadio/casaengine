#include <windows.h>
#include <stdlib.h>
#include <exception>

#include "TileMapGame.h"

/**
 *
 */
INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInst, LPSTR CmdLine, INT NbCmd)
{
	TileMapGame game;
	game.Run();

	return EXIT_SUCCESS;
}