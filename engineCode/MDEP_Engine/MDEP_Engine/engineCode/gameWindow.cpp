#include "gameWindow.h"

gameWindow* instance = nullptr;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_CREATE:
	{
		instance->onCreate();
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
		instance->onDestroy();
		break;
	}
	case WM_KEYDOWN:
	{
		
		if (wParam == VK_ESCAPE)
		{
			//DestroyWindow(instance->getWindow());

			//When the user presses escape it cloases the program
			PostMessageA(instance->getWindow(), WM_CLOSE, NULL, NULL);
			printf("ATTEMPT TO SHUT DOWN\n");
			
		}
		printf("Pushed Button Code: %x\n", wParam);
		break;
	}
	case WM_CHAR:
	{
		printf("WM_CHAR: %c\n", (char)wParam);
		break;
	}
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		instance->OnResize(width, height);
		instance->OnRender();
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

		instance->OnRender();
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

gameWindow::gameWindow()
{
	m_hwnd = nullptr;
	m_pDirect2dFactory = nullptr;
	m_pRenderTarget = nullptr;
	m_pLightSlateGrayBrush = nullptr;
	m_pCornflowerBlueBrush = nullptr;
}

HWND gameWindow::getWindow()
{
	return m_hwnd;
}

HRESULT gameWindow::OnRender()
{
	HRESULT hr = S_OK;
	hr = CreateDeviceResources();

	if (SUCCEEDED(hr))
	{

		m_pRenderTarget->BeginDraw();

		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		

		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

		// Draw a grid background.
		int width = static_cast<int>(rtSize.width);
		int height = static_cast<int>(rtSize.height);

		

		//Horizontal Lines
		for (int x = 0; x < width; x += 10)
		{
			m_pRenderTarget->DrawLine(
				D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
				D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
				m_pCornflowerBlueBrush,
				1.5f
			);
		}

		//Vertical Lines
		
		for (int y = 0; y < height; y += 10)
		{
			m_pRenderTarget->DrawLine(
				D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
				m_pLightSlateGrayBrush,
				0.5f
			);
		}
		
		//draw the rectangles

		//draw a circle in the middle of the screen
		m_pRenderTarget->FillEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(rtSize.width / 2, rtSize.height / 2),
				rtSize.width / 2, rtSize.height / 2),
			m_pCornflowerBlueBrush);

		hr = m_pRenderTarget->EndDraw();

	}

	if(hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		onDestroy();
	}

	return hr;
}


void gameWindow::OnResize(UINT width, UINT height)
{
	if(m_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
			// error here, because the error will be returned again
			// the next time EndDraw is called.
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
		//printf("scaling\n");
	}
	
}

HRESULT gameWindow::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	return hr;
}

HRESULT gameWindow::CreateDeviceResources()
{
	HRESULT hr = S_OK;
	
	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		//get size of screen
		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		// Create a Direct2D render target.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
		);


		if (SUCCEEDED(hr))
		{
			// Create a gray brush.
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
				&m_pLightSlateGrayBrush
			);
		}
		if (SUCCEEDED(hr))
		{
			// Create a blue brush.
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
				&m_pCornflowerBlueBrush
			);
		}
	}

	return hr;
}


bool gameWindow::initialize()
{

	HRESULT hr;

	hr = CreateDeviceIndependentResources();

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

	if (!instance)
		instance = this;

	//FLOAT dpiX, dpiY;
	//m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);


	//create window display object
	m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "Game Window", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL, NULL, NULL, NULL);

	if (!m_hwnd)
		return false;

	ShowWindow(m_hwnd,SW_SHOWNORMAL);
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
	
	m_pDirect2dFactory->Release();
	m_pRenderTarget->Release();
	m_pLightSlateGrayBrush->Release();
	m_pCornflowerBlueBrush->Release();
	
	m_is_run = false;
}