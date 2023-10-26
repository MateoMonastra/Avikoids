#pragma once

#include "ProjectUtilities/Utilities.h"
#include "Objects/Bullet.h"

namespace asteroids
{
	namespace game
	{
		struct Asteroid
		{
			Circle hitBox = {};

			Rectangle dest = {};
			Rectangle source = {};
			Vector2 origin = {};

			float velocity = {30};
			Vector2 aceleration = {};

			float rotation = {};

			bool IsAlive = false;

			Texture2D textureBigAsteroid = {};
			Texture2D textureMediumAsteroid = {};
			Texture2D textureSmallAsteroid = {};
			

		};

		
		void DrawAsteroid(Asteroid bigAsteroids[], Asteroid mediumAsteroids[], Asteroid smallAsteroids[]);
		void AsteroidUpdate(Asteroid bigAsteroids[]/*, Asteroid mediumAsteroids[], Asteroid smallAsteroids[]*/);


	}
}