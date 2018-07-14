#include "CarsGame.h"



CarsGame::CarsGame(Car car) :_car(car)
{
	_friction = 0.1;
}

CarsGame::CarsGame(int _width, int _height): _car("images/car.png", Vector2f(_width / 8, _height / 2), 0, 4.5, 1,0.1)
{
	_friction = 0.01;
}



CarsGame::~CarsGame()
{
}


void CarsGame::mainGameLoop( RenderWindow& win, Sprite& background) {
	Clock clock;

	while (win.isOpen())
	{
		//last_time = clock.getElapsedTime().asSeconds();
		Event ev;
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed) win.close();
			if (ev.type == Event::KeyPressed)
				_car.changeCarsSpeed(ev.key.code);
		}
		
		Vector2f last_speed = _car.getCurrentVelocity();
		
		_car.makeFriction();
		_car.moveBall(last_speed); // Updates position by speed parameters; dx, dy

		//cout << "current speed " << _car.getCurrentSpeedAproximately() << endl;
		//meters_traveled += Helper::getMetersTraveledForLoopCycle(last_speed,_car.getCurrentVelocity());

		//cout << "Time passed: " << time_passed << "\t" << " Meters traveled: " << meters_traveled << endl;
		
		win.clear();
		win.draw(background);
		win.draw(_car.getSprite());
		win.display();

	}
}

