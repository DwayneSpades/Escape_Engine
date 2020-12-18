#include "errorLogger.h"
#include <comdef.h>

void errorLogger::_log(std::string str) 
{
	std::string errorMessage = "Error: " + str;
	MessageBoxA(NULL,errorMessage.c_str(), "Error", MB_ICONERROR);


}

void errorLogger::_logToWindow(HRESULT hr, std::string str)
{
	_com_error error(hr);
	std::string errorMessage = "Error: " + str;
	MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_ICONERROR);
	
}