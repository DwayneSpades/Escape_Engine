#pragma once

#include <Windows.h>
// C RunTime Header Files:
#include <stdio.h>
#include <iostream>

//required to use the Diret 2D API
#include <d2d1.h>
#pragma comment(lib, "d2d1")
//TASK: convert into a singleton

class gameWindow
{

public:

	//big four
	//default constructor
	gameWindow();
	//copy constructor
	gameWindow(const gameWindow& tmp) = default;
	//assignment operator
	gameWindow& operator = (const gameWindow& tmp) = default;
	//destructor
	~gameWindow() = default;

	//initialze program window
	bool initialize();
	//terminate window procedures
	bool Terminate();
	//????????allows the windo to work?
	bool broadcast();
	bool isRun();

	//Window Events
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy() = 0;
	// Draw content.
	HRESULT OnRender();

	// Resize the render target.
	void OnResize(UINT width,UINT height);
	HWND getWindow();
protected:
// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	HWND m_hwnd;
	bool m_is_run=false;

	//direct 2D entrypoint
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;

};


