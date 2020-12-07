#pragma once
class windowManager
{

public:

	//big four

	//copy constructor
	windowManager(const windowManager& tmp) = delete;
	//assignment operator
	windowManager& operator = (const windowManager& tmp) = delete;
	//destructor
	~windowManager() = default;


	windowManager* _Instance = nullptr;

	//singleton class
	static windowManager& _get()
	{
		static windowManager _Instance;
		return _Instance;
	}

	//initialze program window
	static bool initialize() { _get()._initialize(); };

	//terminate window procedures
	static bool Terminate() { _get()._Terminate(); };

	//????????allows the windo to work?
	static bool broadcast() { _get()._broadcast(); };

	static bool isRun() { _get()._isRun(); };

	/*
	//Window Events
	static void onCreate(){};
	static void onUpdate(){};
	static void onDestroy(){};
	*/

	// Draw content.
	static HRESULT OnRender() { _get()._OnRender(); };

	// Resize the render target.
	static void OnResize(UINT width, UINT height) { _get()._OnResize(width, height); };
	static HWND getWindow() { return _get()._getWindow(); };

	static D2D1_SIZE_F getScreenSize() { _get().getScreenSize(); };

protected:

	//default constructor
	windowManager() {};

	//initialze program window
	bool _initialize();
	//terminate window procedures
	bool _Terminate();
	//????????allows the windo to work?
	bool _broadcast();
	bool _isRun();

	//Window Events
	void _onCreate();
	void _onUpdate();
	void _onDestroy();


	// Draw content.
	HRESULT _OnRender();

	// Resize the render target.
	void _OnResize(UINT width, UINT height);
	HWND _getWindow();

	D2D1_SIZE_F _getScreenSize();


	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	HWND m_hwnd;
	bool m_is_run = false;

	//direct 2D entrypoint
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;

};

