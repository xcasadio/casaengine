#include <windows.h>
#include <stdlib.h>
#include <exception>

#include "CubeGame.h"

/**
 *
 */
INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInst, LPSTR CmdLine, INT NbCmd)
{
	CubeGame game;
	game.Run();

	return EXIT_SUCCESS;
}