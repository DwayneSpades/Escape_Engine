#pragma once

#include <Windows.h>
#include <string>

class errorLogger 
{
public:
	//big four

	//copy constructor
	errorLogger(const errorLogger& tmp) = delete;
	//assignment operator
	errorLogger& operator = (const errorLogger& tmp) = delete;
	//destructor
	~errorLogger() = default;


	errorLogger* _Instance = nullptr;

	//singleton class
	static errorLogger& _get()
	{
		static errorLogger _Instance;
		return _Instance;
	}

	static void log(std::string str) { _get()._log(str); };
	static void logToWindow(HRESULT hr, std::string str) { _get()._logToWindow(hr,str); };

private:
	errorLogger() {}

	void _log(std::string message);
	void _logToWindow(HRESULT hr ,std::string str);
};