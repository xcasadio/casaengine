#include "Animation2DPlayerGame.h"
#include <windows.h>
#include <exception>

INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInst, LPSTR CmdLine, INT NbCmd)
{
	try
	{
		Animation2DPlayerGame game;
		game.Run();
	}
	catch (const std::exception& E)
	{
		MessageBox(nullptr, E.what(), "Error", MB_ICONWARNING);
	}

	return EXIT_SUCCESS;
}
