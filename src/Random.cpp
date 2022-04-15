#include "Random.h"

void Random::initialization()
{
	std::random_device randomDevice;
	Random::seed(randomDevice());
}

void Random::seed(unsigned int seed)
{
	sGenerator.seed(seed);
}

float Random::getFloat()
{
	return getFloatRange(0.0f, 1.0f);
}

float Random::getFloatRange(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(sGenerator);
}

int Random::getIntRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(sGenerator);
}

Vector2D Random::getVector(const Vector2D& min, const Vector2D& max)
{
	Vector2D r = Vector2D(getFloat(), getFloat());
	return min + (max - min) * r;
}

std::mt19937 Random::sGenerator;