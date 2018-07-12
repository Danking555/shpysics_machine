#pragma once
#include "Car.h"
#include "GameEngine.h"

class CarsGame
{
private:
	Car _car;
	float _friction;
public:
	CarsGame(Car car);
	CarsGame(int _width, int _height);
	~CarsGame();

	void mainGameLoop( RenderWindow& win, Sprite& background);
};

