#include <Windows.h>
#include "applicationWindow.h"

//console window execution
int main()
{
	applicationWindow mainWindow;
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	//main game loop
	if(mainWindow.initialize())
	{
		while(mainWindow.isRun())
		{
			mainWindow.broadcast();
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