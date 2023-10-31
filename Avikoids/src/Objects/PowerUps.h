#pragma once

#include "Objects/Asteroids.h"

namespace asteroids
{
	namespace game
	{
		void DrawPowerUps();
		void UpdatePowerUps(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[], Spaceship player);
		void InitPowerUp();

	}
}