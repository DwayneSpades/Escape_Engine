#include <Windows.h>
#include "gameWindow.h"

//console window execution
int main()
{
	
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	//main game loop
	if(gameWindow::initialize())
	{
		while(gameWindow::isRun())
		{
			gameWindow::broadcast();
		}
		CoUninitialize();
	}
	
	return 0;
}

/*
//console window DISABLED execution
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	applicationWindow mainWindow;
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	//main game loop
	if (mainWindow.initialize())
	{
		while (mainWindow.isRun())
		{
			mainWindow.broadcast();
		}
		CoUninitialize();
	}

	return 0;
}
*/