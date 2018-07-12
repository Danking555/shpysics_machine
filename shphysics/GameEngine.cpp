#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine()
{
	do {
		cout << "Welcome to the great game engine!" << endl;
		cout << "Games available are:" << endl;
		cout << "1. Cars (top down racing)" << endl;
		cin >> _choice;
	} while (_choice <= 0 || _choice > 1);	
}


void GameEngine::openRelevantGame()
{
	if (_choice == 1)
	{	
		CarsGame c(_width = 640, _height = 480);
		RenderWindow r(VideoMode(_width, _height), "Cars racing (top down)");
		Sprite background(Helper::loadTextureFromFile("images/background.png"));
		c.mainGameLoop(r,background);
	}
}


GameEngine::~GameEngine()
{
}
