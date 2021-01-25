/**
 *
 */
#include "FSMGame.h"
#include <windows.h>
#include <exception>

 /**
  *
  */
INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInst, LPSTR CmdLine, INT NbCmd)
{
	try
	{
		FSMGame game;
		game.Run();
	}
	catch (const std::exception& E)
	{
		MessageBox(NULL, E.what(), "Error", MB_ICONWARNING);
	}

	return EXIT_SUCCESS;
}