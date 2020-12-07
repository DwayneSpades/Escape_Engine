#pragma once

#include <stdio.h>
#include <iostream>

//required to use the Diret 2D API
#include <d2d1.h>
#pragma comment(lib, "d2d1")
//TASK: convert into a singleton

class EE2DTools
{

public:

	//big four

	//copy constructor
	EE2DTools(const EE2DTools& tmp) = delete;
	//assignment operator
	EE2DTools& operator = (const EE2DTools& tmp) = delete;
	//destructor
	~EE2DTools() = default;


	EE2DTools* _Instance = nullptr;

	//singleton class
	static EE2DTools& _get()
	{
		static EE2DTools _Instance;
		return _Instance;
	}

	static HRESULT CreateDeviceIndependentResources() { return _get()._CreateDeviceIndependentResources(); };
	static HRESULT CreateDeviceResources() { return _get()._CreateDeviceResources(); };

	static void Terminate() { _get()._Terminate(); };
	static void onResize(UINT width, UINT height) { _get()._onResize(width,height); };
	static void onRender() { _get()._onRender(); };
	static D2D1_SIZE_F getScreenSize() { return _get()._getScreenSize(); };

protected:

	//default constructor
	EE2DTools() {};


	// Initialize device-independent resources.
	HRESULT _CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT _CreateDeviceResources();
	
	//get screensize
	D2D1_SIZE_F _getScreenSize();

	//render to window target
	HRESULT _onRender();

	//resize render window
	void _onResize(UINT width, UINT height);

	void _Terminate();
	//HWND m_hwnd = nullptr;

	//direct 2D entrypoint
	ID2D1Factory* m_pDirect2dFactory = nullptr;
	ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush = nullptr;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush = nullptr;


};
