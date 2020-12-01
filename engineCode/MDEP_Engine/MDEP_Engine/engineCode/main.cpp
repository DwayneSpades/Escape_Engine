#include <Windows.h>
#include "applicationWindow.h"

int main()
{
	
	applicationWindow mainWindow;
	if(mainWindow.initialize())
	{

		while(mainWindow.isRun())
		{
			mainWindow.broadcast();
		}
	}

	return 0;
}
