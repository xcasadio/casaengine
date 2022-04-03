#include <exception>
#include <Windows.h>
#include "CubeGame.h"

INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInst, LPSTR CmdLine, INT NbCmd)
{
	try
	{
		CubeGame game;
		game.Run();
	}
		catch (const std::exception& E)
	{
		MessageBox(nullptr, E.what(), "Error", MB_ICONWARNING);
	}

	return EXIT_SUCCESS;
}
