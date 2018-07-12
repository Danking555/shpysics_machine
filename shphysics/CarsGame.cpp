#include "CarsGame.h"



CarsGame::CarsGame(Car car) :_car(car)
{
	_friction = 0.1;
}

CarsGame::CarsGame(int _width, int _height): _car("images/car.png", Vector2f(_width / 8, _height / 2), M_PI / 2, 5, 1)
{
	_friction = 0.1;
}



CarsGame::~CarsGame()
{
}


void CarsGame::mainGameLoop( RenderWindow& win, Sprite& background) {
	Clock clock;

	float last_time = 0;
	float meters_traveled = 0;

	while (win.isOpen())
	{
		last_time = clock.getElapsedTime().asSeconds();
		Event ev;
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed) win.close();
			if (ev.type == Event::KeyPressed)
				_car.changeCarsSpeed(ev.key.code);
		}
		
		float time_passed = clock.getElapsedTime().asSeconds() - last_time;
		Vector2f last_speed = _car.getCurrentSpeed();
		
		_car.makeFriction(_friction);
		_car.updateCurrentSpeed(); // Will be updated both from friction and keyboard if was pressed
		_car.moveBall(time_passed, last_speed); // Updates position by speed parameters; dx, dy

		if (_car.carStopped())
			_car.setRotation(-_car.getRotation() * 180 / M_PI);
		if (_car.boolReverse())
			_car.setRotation(-(M_PI + _car.getRotation()) * 180 / M_PI);


		meters_traveled += Helper::getMetersTraveledForTime(time_passed,last_speed,_car.getCurrentSpeed());

		cout << "Time passed: " << time_passed << "\t" << " Meters traveled: " << meters_traveled << endl;

		//win.clear(Color::White);
		win.draw(background);
		win.draw(_car.getSprite());
		win.display();

	}
}

