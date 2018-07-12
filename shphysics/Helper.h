#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

# define M_PI           3.14159265358979323846

static class Helper
{
public:

	static Texture loadTextureFromFile(string path) {
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

	// Physics stuff
	static float getMetersTraveledForTime(float time_delta, float v_before, float v_after)
	{
		return time_delta * (v_before + (v_before + v_after) / 2);
	}

	// Physics stuff
	static float getMetersTraveledForTime(float time_delta, Vector2f v_before, Vector2f v_after)
	{
		return sqrt(pow(v_after.x - v_before.x, 2) + pow(v_after.y - v_after.x,2));
	}

	static float getDistance(Vector2f a, Vector2f b)
	{
		return abs(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}

	static float getAcceleration(float time_delta, float before, float after)
	{
		return (after - before) / time_delta;
	}

	Helper();
	~Helper();
};
