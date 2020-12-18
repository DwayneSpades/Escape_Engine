#pragma once
#pragma once

#include <Windows.h>
#include <string>

class stringConverter
{
public:
	//big four

	//copy constructor
	stringConverter(const stringConverter& tmp) = delete;
	//assignment operator
	stringConverter& operator = (const stringConverter& tmp) = delete;
	//destructor
	~stringConverter() = default;


	stringConverter* _Instance = nullptr;

	//singleton class
	static stringConverter& _get()
	{
		static stringConverter _Instance;
		return _Instance;
	}

	static std::wstring convertString(std::string str) { return _get()._convertString(str); };

private:
	stringConverter() {}

	std::wstring _convertString(std::string str);

};