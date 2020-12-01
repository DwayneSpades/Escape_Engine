#pragma once

#include <Windows.h>



class gameWindow
{

public:

	//big four
	//default constructor
	gameWindow() = default;
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
protected:
	HWND m_hwnd;
	bool m_is_run=false;
};


