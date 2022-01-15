#include "random-engine.hpp"

#include <ctime>

RandomEngine::RandomEngine()
{
	srand(time(NULL));
}

int RandomEngine::RandomInt(const int min, const int max) const
{
	return rand() % (max - min + 1) + min;
}

double RandomEngine::RandomDouble(double min, double max) const
{
	return min + RandomDouble() * (max - min);
}

double RandomEngine::RandomDouble() const
{
	return rand() / RAND_MAX;
}

bool RandomEngine::RandomBool() const
{
	return rand() > RAND_MAX / 2;
}
