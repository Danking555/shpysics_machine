
#include "SFML\Graphics.hpp"
#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

# define M_PI           3.14159265358979323846

float width = 800, height = 600;

float x = width / 8, y = height / 2; // position (m' from top left corner)
float dx = 0, dy = 0;               // speed (m' / sec)
float alpha = 0;				   // Direction (0 is right)
float acceleration = 1;           // m' / (sec ^ 2)
float friction = 0.01;		     // Friction forces
float current_speed = 0;        // sqrt ( dx^2 + dy^2 )
float max_speed = 5;

bool rev = false;            // if moving back it's true

/*
	Noted physics in this stuff (FOR NOW...):

	V = V0 + at  ==> V=DX && a=acceleration(alpha serves as the vector for this) && t=is implemented in computer's timer ticks(we won't block the performance by our implemention of ticks)
*/

// Changes speed of the ball depending on the keyboard key that pressed
void changeBallSpeed(int keyboard_result_code);

// Deaccelerates the speed
void makeFriction();

// Updates dx(x speed), dy(y speed) and current speed
void updateCurrentSpeed();

// Increases x, y using dx,dy
void moveBall();

Texture loadTextureFromFile( string path);

int main()
{
	RenderWindow win(VideoMode(width, height), "Racing (top down)");
	win.setFramerateLimit(60);

	Sprite ball, background;
	Texture ball_texture = loadTextureFromFile("images/car.png");
	Texture background_texture = loadTextureFromFile("images/background.png");
	ball_texture.setSmooth(true);
	background_texture.setSmooth(true);

	ball.setTexture(ball_texture);
	background.setTexture(background_texture);

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

		ball.setPosition(x, y);

		if(current_speed) 
			ball.setRotation(-alpha * 180 / M_PI);

		win.clear(Color::White);
		win.draw(background);
		win.draw(ball);


		win.display();
	}
	return 0;
}


void changeDirectionOrDecreaseSpeed()
{
	if (!current_speed) // Change from R to D 
	{
		alpha += M_PI; // Change direction to be forward
		current_speed += acceleration; // accelerate as expected
		rev = !rev;  
		cout << rev << endl;
	}
	else if ((current_speed - acceleration) <= 0) current_speed = 0;
	else  current_speed -= acceleration; // Try to stop from reverse

}

void increaseSpeed()
{

	if (current_speed + acceleration > max_speed)
		cout << "Can't move faster than speed limit" << endl;
	else current_speed += acceleration;
}

void SpeedUp()
{
	if (rev) changeDirectionOrDecreaseSpeed();
	else increaseSpeed();
}

void SpeedDown()
{
	if (rev) increaseSpeed();
	else changeDirectionOrDecreaseSpeed();
}

void changeBallSpeed(int keyboard_result_code)
{
	if (keyboard_result_code == Keyboard::Up)
		SpeedUp();
	if (keyboard_result_code == Keyboard::Down)
		SpeedDown();
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
	if (current_speed < 0.1) current_speed = 0;
}

void moveBall()
{
	x += dx;
	y += dy;
}

Texture loadTextureFromFile( string path)
{
	Texture ret;
	bool suc = ret.loadFromFile(path);
	if (!suc) {
		cout << "Error" << endl;
		cout << "Error occourd opening texture from " + path << endl;
		system("pause");
		exit(1);
	}
	return ret;
}
