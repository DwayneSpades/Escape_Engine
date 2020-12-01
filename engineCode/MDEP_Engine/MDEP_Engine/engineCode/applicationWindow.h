#pragma once

#include "gameWindow.h"

class applicationWindow : public gameWindow
{

public:

	//big four
	//default constructor
	applicationWindow() = default;
	//copy consapplicationtor
	applicationWindow(const applicationWindow& tmp) = default;
	//assignment operator
	applicationWindow& operator = (const applicationWindow& tmp) = default;
	//destructor
	~applicationWindow() = default;

private:

	// Inherited via gameWindow
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
};