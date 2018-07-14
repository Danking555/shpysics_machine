#pragma once

#include "Helper.h"

class Car {
public:
	Car(String path, Vector2f position, float dir_alpha, float max_speed, float acceleration, float friction);
	Car();
	~Car();

	// Changes speed of the car depending on the keyboard key that pressed
	void changeCarsSpeed(int keyboard_result_code);

	// Deaccelerates the speed
	void makeFriction();

	// Increases x, y using dx,dy
	void moveBall(Vector2f v0);

	float getCurrentSpeedAproximately();

	Vector2f getCurrentVelocity();

	bool carStopped();

	void setRotation(float alpha);

	float getRotation();

	bool boolReverse();

	Sprite getSprite();

	void updateSpriteByPosition();

private:
	Texture _texture;
	Sprite _sprite;

	Vector2f _velocity; // dx, dy
	Vector2f _position; // x, y
	float _acceleration; // d(current_speed) Constant
	float _friction;


	float _meters_traveled; // += v0t + at^2/2
	float _dir_alpha; // -pai < dir < pai
	float _max_speed = 5;

	bool rev;
	

	void changeDirectionOrDecreaseSpeed();

	void increaseSpeed();

	void SpeedUp();

	void SpeedDown();

	void updateVelocityUp();

	void updateVelocityDown();

	bool zeroVelocity();

	bool shouldAccelerate();
};