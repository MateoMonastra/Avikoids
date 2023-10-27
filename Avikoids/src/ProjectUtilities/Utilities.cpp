#include "Utilities.h"

float RandomDirection(int min, int max)
{
	float randomNumber = static_cast<float>(GetRandomValue(min, max));

	randomNumber /= 100;

	return randomNumber;
}