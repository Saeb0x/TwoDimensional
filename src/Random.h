#pragma once
#include <random>
#include "MathForGames.h"

class Random
{
public:
	static void initialization();

	// seed the generator with the specified integer
	static void seed(unsigned int seed);

	// get a float between 0 and 1
	static float getFloat();

	// get a float within a specified range
	static float getFloatRange(float min, float max);

	// get an integer within a specified range
	static int getIntRange(int min, int max);

	// get a random vector given the minimum and maximum bounds
	static Vector2D getVector(const Vector2D& min, const Vector2D& max);
private:
	static std::mt19937 sGenerator; // mersenne Twister 19937 generator
};