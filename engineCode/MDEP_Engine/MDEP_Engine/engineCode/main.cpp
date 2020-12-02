#include <Windows.h>
#include "applicationWindow.h"

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
