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

	//copy constructor
	gameWindow(const gameWindow& tmp) = delete;
	//assignment operator
	gameWindow& operator = (const gameWindow& tmp) = delete;
	//destructor
	~gameWindow() = default;


	gameWindow* _Instance = nullptr;

	//singleton class
	static gameWindow& _get()
	{
		static gameWindow _Instance;
		return _Instance;
	}

	//initialze program window
	static bool initialize() { return _get()._initialize(); };

	//terminate window procedures
	static bool Terminate() { return _get()._Terminate(); };

	//????????allows the windo to work?
	static bool broadcast() { return _get()._broadcast(); };

	static bool isRun() { return _get()._isRun(); };


	/*
	//Window Events
	static void onCreate(){};
	static void onUpdate(){};
	static void onDestroy(){};
	*/

	// Draw content.
	static void OnRender() { _get()._onRender(); };

	// Resize the render target.
	static void OnResize(UINT width, UINT height) { _get()._OnResize(width, height); };
	static HWND getWindow() { return _get()._getWindow(); };

	static D2D1_SIZE_F getScreenSize() { _get()._getScreenSize(); };
	static void onDestroy() { _get()._onDestroy(); };

protected:

	//default constructor
	gameWindow() {};

	//initialze program window
	bool _initialize();
	//terminate window procedures
	bool _Terminate();
	//????????allows the windo to work?
	bool _broadcast();
	bool _isRun();

	/*
	//Window Events
	void _onCreate();
	void _onUpdate();
	*/

	void _onDestroy();
	

	// Draw content.
	void _onRender();

	// Resize the render target.
	void _OnResize(UINT width, UINT height);
	HWND _getWindow();

	D2D1_SIZE_F _getScreenSize();


	// Initialize device-independent resources.
	//HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	//HRESULT CreateDeviceResources();

	HWND m_hwnd = nullptr;
	bool m_is_run = false;

	

};


