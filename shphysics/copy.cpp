/*
#include "Car.h"
using namespace std;
using namespace sf;


float width = 640, height = 480;

float x = width / 8, y = height / 2; // position (m' from top left corner)
float dx = 0, dy = 0;               // speed (m' / sec)
float alpha = 0;				   // Direction (0 is right)
float acceleration = 1;           // m' / (sec ^ 2)
float friction = 0.01;		     // Friction forces
float current_speed = 0;        // sqrt ( dx^2 + dy^2 )
float max_speed = 5;
float turn_speed = 0.12;

bool rev = false;            // if moving back it's true

float timer = 0, delay = 1;


// Changes speed of the car depending on the keyboard key that pressed
void changeCarsSpeed(int keyboard_result_code);

// Deaccelerates the speed
void makeFriction();

// Updates dx(x speed), dy(y speed) and current speed
void updateCurrentSpeed();

// Increases x, y using dx,dy
void moveBall();



int main()
{
	RenderWindow win(VideoMode(width, height), "Racing (top down)");
	win.setFramerateLimit(60);


	Sprite car, background;
	Texture car_texture = Helper::loadTextureFromFile("images/car.png");
	Texture background_texture = Helper::loadTextureFromFile("images/background.png");

	car_texture.setSmooth(true);
	background_texture.setSmooth(true);

	car.setTexture(car_texture);
	background.setTexture(background_texture);

	Clock clock;

	float last_speed = 0;
	float last_time = 0;
	float meters_traveled = 0;

	while (win.isOpen())
	{
		last_time = timer;
		last_speed = current_speed;

		Event ev;
		while (win.pollEvent(ev))
		{

			if (ev.type == Event::Closed) win.close();
			if (ev.type == Event::KeyPressed)
				changeCarsSpeed(ev.key.code);

		}
		makeFriction();

		updateCurrentSpeed(); // Will be updated both from friction and keyboard if was pressed

		moveBall(); // Updates position by speed parameters; dx, dy

		car.setPosition(x, y);

		if (current_speed)
			car.setRotation(-alpha * 180 / M_PI);
		if (rev)
			car.setRotation(-(M_PI + alpha) * 180 / M_PI);


		timer = clock.getElapsedTime().asSeconds();

		meters_traveled += Helper::getMetersTraveledForTime(timer - last_time, last_speed, current_speed);

		cout << timer - last_time << "\t" << "acceleration: " << last_speed - current_speed << " Current x duration: " << meters_traveled << endl;


		win.clear(Color::White);
		win.draw(background);
		win.draw(car);


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

void changeCarsSpeed(int keyboard_result_code)
{
	if (keyboard_result_code == Keyboard::Up)
		SpeedUp();
	if (keyboard_result_code == Keyboard::Down)
		SpeedDown();
	if (keyboard_result_code == Keyboard::Left)
		if (current_speed != 0)  alpha += turn_speed * current_speed / max_speed;
	if (keyboard_result_code == Keyboard::Right)
		if (current_speed != 0)  alpha -= turn_speed * current_speed / max_speed;


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

Texture loadTextureFromFile(string path)
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
*/