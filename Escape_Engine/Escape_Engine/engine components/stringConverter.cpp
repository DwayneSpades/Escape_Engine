#include "stringConverter.h"

std::wstring stringConverter::_convertString(std::string str) 
{
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}