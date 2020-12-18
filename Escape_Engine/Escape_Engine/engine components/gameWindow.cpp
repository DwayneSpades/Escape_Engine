#include "gameWindow.h"
#include "EE2DTools.h"
#include "dx11Base.h"

 //close directx and clean memeory

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_CREATE:
	{
		
		break;
	}
		
	case WM_CLOSE:
	{
		//what to do when closing the program
		printf("Beginning to exit application\n");

		//shutdown confirmation: enable for release build
		//-----------------------------------------------

		/*
		if (MessageBox(hwnd, "Really quit?", "My Application", MB_OKCANCEL) == IDOK)
		{
			instance->onDestroy();
			return 0;
		}
		*/
		gameWindow::onDestroy();
		break;
	}
	case WM_KEYDOWN:
	{
		
		if (wParam == VK_ESCAPE)
		{
			//DestroyWindow(instance->getWindow());

			//When the user presses escape it cloases the program
			PostMessageA(gameWindow::getWindow(), WM_CLOSE, NULL, NULL);
			printf("ATTEMPT TO SHUT DOWN\n");
			
		}
		break;
	}
	case WM_CHAR:
	{
		printf("WM_CHAR: %c, Keycode: %x\n", (char)wParam,wParam);
		break;
	}
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		gameWindow::OnResize(width, height);
		gameWindow::OnRender();
		ValidateRect(hwnd, NULL);
	}
	break;
	case WM_DISPLAYCHANGE:
	{
		InvalidateRect(hwnd, NULL, FALSE);
	}
	break;
	case WM_PAINT:
	{

		gameWindow::OnRender();
		ValidateRect(hwnd, NULL);
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

HWND gameWindow::_getWindow()
{
	return m_hwnd;
}



void gameWindow::_onRender()
{
	EE2DTools::onRender();
}


void gameWindow::_OnResize(UINT width, UINT height)
{
	EE2DTools::onResize(width,height);
}


bool gameWindow::_initialize()
{

	HRESULT hr;

	hr = EE2DTools::CreateDeviceIndependentResources();//CreateDeviceIndependentResources();

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

	if (!RegisterClassEx(&wc))
		return false;

	//FLOAT dpiX, dpiY;
	//m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);


	//create window display object
	m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "Game Window", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL, NULL, NULL, NULL);

	if (!m_hwnd)
		return false;

	ShowWindow(m_hwnd,SW_SHOWNORMAL);
	UpdateWindow(m_hwnd);

	//initialize Direct3D
	dx11Base::InitD3D(m_hwnd);

	//set flag to true 
	m_is_run = true;

	return true;
}

bool gameWindow::_broadcast()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//instance->onUpdate();

	Sleep(0);
	return true;
}

D2D1_SIZE_F gameWindow::_getScreenSize()
{
	return EE2DTools::getScreenSize();
}

bool gameWindow::_Terminate()
{
	if (!DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool gameWindow::_isRun()
{
	return m_is_run;
}

void gameWindow::_onDestroy()
{
	//release rendering resources
	EE2DTools::Terminate();
	//cleanup DirectX and COM
	dx11Base::CleanD3D();

	//application window is nolonger running
	m_is_run = false;
}