#include "Car.h"



Car::Car(String path, Vector2f position, float dir_alpha, float max_speed, float acceleration, float friction)
{
	_texture = Helper::loadTextureFromFile(path);
	_sprite.setTexture(_texture);	
	_position = position;
	updateSpriteByPosition();
	_dir_alpha = dir_alpha;
	_max_speed = max_speed;
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
	if (!getCurrentSpeedAproximately()) // Change from R to D 
	{
		_dir_alpha += M_PI; // Change direction to be forward
		updateVelocityUp(); // accelerate as expected
		rev = !rev;
		cout << rev << endl;
	}
	else if (!zeroVelocity())
		updateVelocityDown(); // Try to stop from reverse

}


void Car::increaseSpeed()
{

	if (!shouldAccelerate())
		cout << "Can't move faster than speed limit" << endl;
	else updateVelocityUp();
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

void Car::updateVelocityUp()
{
	_velocity.x += cos(_dir_alpha)*_acceleration;
	_velocity.y += sin(_dir_alpha)*_acceleration;
}


void Car::updateVelocityDown()
{
	if (_velocity.x) // This velocity could be zerod before
		_velocity.x -= cos(_dir_alpha)*_acceleration;
	if (_velocity.y) // This velocity could be zerod before
		_velocity.y -= sin(_dir_alpha)*_acceleration;
}

bool Car::zeroVelocity()
{

	if(!carStopped() && getCurrentSpeedAproximately() < _friction)
	//if (_velocity.x < _friction && _velocity.y < _friction)
	{
		_velocity.x = 0;
		_velocity.y = 0;
		cout << "zeroed" << endl;
		return true;
	}
	return false;
}

bool Car::shouldAccelerate()
{
	return ((getCurrentSpeedAproximately() + _acceleration) < _max_speed);
}

void Car::changeCarsSpeed(int keyboard_result_code)
{

	if (keyboard_result_code == Keyboard::Up)
	{
		cout << "keyboard up" << endl;
		SpeedUp();
	}
	if (keyboard_result_code == Keyboard::Down)
	{
		cout << "keyboard down" << endl;
		SpeedDown();
	}
	if (keyboard_result_code == Keyboard::Left)
		if (!zeroVelocity())  _dir_alpha += 0.1;
	if (keyboard_result_code == Keyboard::Right)
		if (!zeroVelocity())  _dir_alpha -= 0.1;


}

void Car::makeFriction()
{
	if (!zeroVelocity()) {
		if (_velocity.x >= _friction) { _velocity.x -= _friction; cout << "x friction" << endl; }
		if (_velocity.y >= _friction) { _velocity.y -= _friction; cout << "y friction" << endl; }
	}
}


void Car::updateSpriteByPosition()
{
	_sprite.setPosition(_position.x, _position.y);
	_sprite.setRotation(-_dir_alpha*180 / M_PI);
}

void Car::moveBall(Vector2f v0)
{
	//cout << "v0.x: " << v0.x << " v0.y: " << v0.y << ". Current velocity: x " << _velocity.x << ", y: " << _velocity.y << endl;
	_position.x += _velocity.x;//Helper::getMetersTraveledForLoopCycle( v0.x, _velocity.x);
	_position.y += _velocity.y; //Helper::getMetersTraveledForLoopCycle(v0.y, _velocity.y);
	updateSpriteByPosition();
}

float Car::getCurrentSpeedAproximately()
{
	return sqrt(pow(_velocity.x,2) + pow(_velocity.y, 2));
}

Vector2f Car::getCurrentVelocity()
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


