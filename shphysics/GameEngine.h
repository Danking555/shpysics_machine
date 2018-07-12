#pragma once
#include <thread>
using namespace std;

#include "CarsGame.h"

class GameEngine
{
	
private:
	int _choice;
	int _width;
	int _height;
public:
	GameEngine();
	~GameEngine();

	void openRelevantGame();
};

