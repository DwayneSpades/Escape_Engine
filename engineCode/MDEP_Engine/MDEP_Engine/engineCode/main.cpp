#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM Lparams);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	
	//const wchar_t CLASS_NAME[] = L"Game Window";


	LPCTSTR CLASS_NAME = "Game Window";


	WNDCLASS windowclass = { };

	windowclass.lpfnWndProc = WindowProc;
	windowclass.hInstance = hInstance;
	windowclass.lpszClassName = CLASS_NAME;

	RegisterClass(&windowclass);

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		"Game Window 1",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == nullptr)
	{
		return 0;
	}


	HWND hwnd2 = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		"Game Window 2",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		0, 0, 600, 600,
		hwnd,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd2 == nullptr)
	{
		return 0;
	}
	//display window 1:
	//where the game graphics will be displayed
	ShowWindow(hwnd, nCmdShow);

	//display window 2:
	//this will be my console window for displaying game messages
	ShowWindow(hwnd2, nCmdShow);
	
	MSG msg = {};
	while(GetMessage(&msg,NULL,0 ,0))
	{
		//GetMessage(&msg, hwnd2, 0, 0);

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{

			if (MessageBox(hwnd, "Really quit?", "My Application", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hwnd);
			}
			//if user has cancled do nothing
			return 0;
		}
		case WM_KEYDOWN:
		{
			
			
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			
			HDC hdc = BeginPaint(hwnd, &ps);



			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 0));

			EndPaint(hwnd, &ps);
			break;
		}

	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}