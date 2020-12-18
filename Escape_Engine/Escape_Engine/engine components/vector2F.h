#pragma once
//required to use the Diret 2D API
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class vector2f
{
public:
	//big four
	vector2f() = default;
	//copy constructor
	vector2f(const vector2f& tmp) = default;
	//assignment operator
	vector2f& operator = (const vector2f& tmp) = default;
	//destructor
	~vector2f() = default;

	vector2f(FLOAT x,FLOAT y);

	FLOAT getX();
	FLOAT getY();


private:
	float x = 0;
	float y = 0;

};