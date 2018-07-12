#include "Car.h"



Car::Car(String path, Vector2f position, float dir_alpha, float max_speed, float acceleration = 1)
{

	_sprite.setTexture(Helper::loadTextureFromFile(path));
	_position = position;
	_dir_alpha = dir_alpha;
	_max_speed = max_speed;
	_current_speed = 0;
	_meters_traveled = 0;
	_acceleration = acceleration;
	rev = false;
}

Car::Car()
{

}


Car::~Car()
{
}



void Car::changeDirectionOrDecreaseSpeed()
{
	if (!_current_speed) // Change from R to D 
	{
		_dir_alpha += M_PI; // Change direction to be forward
		_current_speed += _acceleration; // accelerate as expected
		rev = !rev;
		cout << rev << endl;
	}
	else if ((_current_speed - _acceleration) <= 0) _current_speed = 0;
	else  _current_speed -= _acceleration; // Try to stop from reverse

}

void Car::increaseSpeed()
{

	if (_current_speed + _acceleration > _max_speed)
		cout << "Can't move faster than speed limit" << endl;
	else _current_speed += _acceleration;
}


void Car::SpeedUp()
{
	if (rev) changeDirectionOrDecreaseSpeed();
	else increaseSpeed();
}

void Car::SpeedDown()
{
	if (rev) increaseSpeed();
	else changeDirectionOrDecreaseSpeed();
}



void Car::changeCarsSpeed(int keyboard_result_code)
{
	if (keyboard_result_code == Keyboard::Up)
		SpeedUp();
	if (keyboard_result_code == Keyboard::Down)
		SpeedDown();
	if (keyboard_result_code == Keyboard::Left)
		if (_current_speed != 0)  _dir_alpha += 0.1;
	if (keyboard_result_code == Keyboard::Right)
		if (_current_speed != 0)  _dir_alpha -= 0.1;


}

void Car::makeFriction(float friction)
{
	if (_current_speed > friction) _current_speed -= friction;
}

void Car::updateCurrentSpeed()
{
	_velocity.x = cos(_dir_alpha) * _current_speed;
	_velocity.y = -sin(_dir_alpha) * _current_speed;

	_current_speed = sqrt(pow(_velocity.x, 2) + pow(_velocity.y, 2));
	if (_current_speed < 0.1) _current_speed = 0;
}

void Car::moveBall(float time_passed, Vector2f v0)
{
	_position.x += Helper::getMetersTraveledForTime(time_passed, v0.x, _velocity.x);
	_position.y += Helper::getMetersTraveledForTime(time_passed, v0.y, _velocity.y);
}

Vector2f Car::getCurrentSpeed()
{
	return _velocity;
}

bool Car::carStopped()
{
	return _velocity.x == 0 && _velocity.y == 0;
}

void Car::setRotation(float alpha)
{
	_dir_alpha = alpha;
}

float Car::getRotation()
{
	return _dir_alpha;
}

bool Car::boolReverse()
{
	return rev;
}

Sprite Car::getSprite()
{
	return _sprite;
}


