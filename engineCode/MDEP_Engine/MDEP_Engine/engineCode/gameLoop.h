#pragma once


class gameLoop
{
	//big four
	//default constructor
	gameLoop() = default;
	//copy constructor
	gameLoop(const gameLoop& tmp) = default;
	//assignment operator
	gameLoop& operator = (const gameLoop& tmp) = default;
	//destructor
	~gameLoop()=default;


	void runGameLoop();
};