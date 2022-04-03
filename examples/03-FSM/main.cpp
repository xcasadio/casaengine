#include "FSMGame.h"
#include <Windows.h>
#include <exception>

INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInst, LPSTR CmdLine, INT NbCmd)
{
	try
	{
		FSMGame game;
		game.Run();
	}
	catch (const std::exception& E)
	{
		MessageBox(nullptr, E.what(), "Error", MB_ICONWARNING);
	}

	return EXIT_SUCCESS;
}