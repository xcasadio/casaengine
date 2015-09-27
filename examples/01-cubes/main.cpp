#include <windows.h>
#include <stdlib.h>
#include <exception>

#include "CubesGame.h"

/**
 * 
 */
INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInst, LPSTR CmdLine, INT NbCmd)
{
	CubesGame game;
	game.Run();

	return EXIT_SUCCESS;
}