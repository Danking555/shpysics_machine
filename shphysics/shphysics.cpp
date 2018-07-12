
#include "GameEngine.h"
//#include "Car.h"
using namespace std;
using namespace sf;

/*
	Noted physics in this stuff (FOR NOW...):

	V = V0 + at  ==> V=DX && a=acceleration(alpha serves as the vector for this) && t=is implemented in computer's timer ticks(we won't block the performance by our implemention of ticks)
*/

int main()
{
	GameEngine game_engine;

	game_engine.openRelevantGame();

	system("pause");
	return 0;
}

