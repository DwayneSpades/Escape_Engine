#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dX11.h>
#include <d3dX10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")



//function prototypes


class dx11Base 
{
public:
	//copy constructor
	dx11Base(const dx11Base& tmp) = delete;
	//assignment operator
	dx11Base& operator = (const dx11Base& tmp) = delete;
	//destructor
	~dx11Base() = default;


	dx11Base* _Instance = nullptr;

	//singleton class
	static dx11Base& _get()
	{
		static dx11Base _Instance;
		return _Instance;
	}


	static void InitD3D(HWND hwnd) { _get()._InitD3D(hwnd); };  //set up and initialize DirectX
	static void CleanD3D() { _get()._CleanD3D(); };  //close directx and clean memeory

private:
	dx11Base(){}
	
	void _InitD3D(HWND hwnd);
	static void _CleanD3D();

};