
#include "SFML\Graphics.hpp"
#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

# define M_PI           3.14159265358979323846

float width = 800, height = 600;

float x = width / 8, y = height / 2; // m' from top left corner
float dx = 0, dy = 0;               // m' / sec
float alpha = 0;
float acceleration = 1, friction = 0.01, max_speed = 5, current_speed = 0; // m' / (sec ^ 2)
float timer = 0, delay = 0.3;

bool rev = false;

/*
	Noted physics in this stuff (FOR NOW...):

	V = V0 + at  ==> V=DX && a=acceleration(alpha serves as the vector for this) && t=is implemented in computer's timer ticks(we won't block the performance by our implemention of ticks)
*/

void accelerateInDirection();

void deaccelerateInDirection();

// Uses 2 functions above depending on the keyboard key that pressed
void changeBallSpeed(int keyboard_result_code);

// Deaccelerates the speed
void makeFriction();

// Updates dx(x speed), dy(y speed) and current speed
void updateCurrentSpeed();

// Increases x, y using dx,dy
void moveBall();

Texture loadTextureFromFile(Texture t, string path);

int main()
{
	RenderWindow win(VideoMode(width, height), "it works!!!");
	win.setFramerateLimit(60);
	Sprite s;
	Texture ball;
	ball = loadTextureFromFile(ball, "red.png");

	s.setTexture(ball);

	Clock clock;
	while (win.isOpen())
	{
		Event ev;
		while (win.pollEvent(ev))
		{

			if (ev.type == Event::Closed) win.close();
			if (ev.type == Event::KeyPressed)
				changeBallSpeed(ev.key.code);
			
		}
		makeFriction();

		updateCurrentSpeed(); // Will be updated both from friction and keyboard if was pressed
		
		moveBall(); // Updates position by speed parameters; dx, dy

		s.setPosition(x, y);
		
		win.clear();
		win.draw(s);
		win.display();
	}
	return 0;
}


void accelerateInDirection()
{
	if (rev) {

		if (!current_speed) // Change from R to D 
		{
			alpha += M_PI; // Change direction to be forward
			current_speed += acceleration; // accelerate as expected
			rev = false;  // (forward moves)
		}
		else if ((current_speed - acceleration) <= 0) current_speed = 0;
		else  current_speed -= acceleration; // Try to stop from reverse
	}
	else { // We are moving forward

		if (current_speed + acceleration > max_speed)
			cout << "Can't move faster than speed limit" << endl;
		else current_speed += acceleration;
	}
}

void deaccelerateInDirection()
{
	if (rev)
	{
		if (current_speed + acceleration > max_speed)
			cout << "Can't move faster than speed limit" << endl;
		else current_speed += acceleration;
	}
	else {

		if (!current_speed) // Change from D to R 
		{
			alpha += M_PI; // Change direction to be Reverse
			current_speed += acceleration; // accelerate as expected
			rev = true;  // (reverse moves)
		}
		else if ((current_speed - acceleration) <= 0) current_speed = 0;
		else  current_speed -= acceleration;
	}

}

void changeBallSpeed(int keyboard_result_code)
{
	if (keyboard_result_code == Keyboard::Up)
		accelerateInDirection();
	if (keyboard_result_code == Keyboard::Down)
		deaccelerateInDirection();
	if (keyboard_result_code == Keyboard::Left)
		if (current_speed != 0)  alpha += 0.1;
	if (keyboard_result_code == Keyboard::Right)
		if (current_speed != 0)  alpha -= 0.1;


}

void makeFriction()
{
	if (current_speed > friction) current_speed -= friction;
}

void updateCurrentSpeed()
{
	dx = cos(alpha) * current_speed;
	dy = -sin(alpha) * current_speed;

	current_speed = sqrt(pow(dx, 2) + pow(dy, 2));
}

void moveBall()
{
	x += dx;
	y += dy;
}

Texture loadTextureFromFile(Texture t, string path)
{
	bool suc = t.loadFromFile(path);
	if (!suc) {
		cout << "Error" << endl;
		cout << "Error occourd opening texture from " + path << endl;
		system("pause");
		exit(1);
	}
	return t;
}
