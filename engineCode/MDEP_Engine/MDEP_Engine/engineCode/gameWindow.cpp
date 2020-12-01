#include "gameWindow.h"
#include <stdio.h>
#include <iostream>

gameWindow* instance = nullptr;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	//char msg[32];

	switch (uMsg)
	{
	case WM_CREATE:
	{
		instance->onCreate();
		break;
	}
		
	case WM_CLOSE:
	{
		printf("Begginning to exit application\n");
		if (MessageBox(hwnd, "Really quit?", "My Application", MB_OKCANCEL) == IDOK)
		{
			
			instance->onDestroy();
		}
			return 0;	
		//break;
	}
	case WM_KEYDOWN:
	{
		printf("Pushed Button: %c\n",lParam);
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

bool gameWindow::initialize()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "Game Window";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WindowProcedure;

	if (!::RegisterClassEx(&wc))
		return false;

	if (!instance)
		instance = this;

	//create window display object
	m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "Game Window", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL, NULL, NULL, NULL);

	if (!m_hwnd)
		return false;

	ShowWindow(m_hwnd,SW_SHOW);
	UpdateWindow(m_hwnd);

	

	//set flag to true 
	m_is_run = true;

	return true;
}

bool gameWindow::broadcast()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	instance->onUpdate();

	Sleep(0);
	return true;
}

bool gameWindow::Terminate()
{
	if (!DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool gameWindow::isRun()
{
	return m_is_run;
}

void gameWindow::onDestroy()
{
	m_is_run = false;
}