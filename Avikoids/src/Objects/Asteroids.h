#pragma once

#include "ProjectUtilities/Utilities.h"
#include "Spaceship.h"

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

			float velocity = {};
			Vector2 aceleration = {};

			float rotation = {};

			bool IsAlive = false;
			bool SpawnChild = false;

			Texture2D texture = {};

			const int ASTEROID_DIVITION = 2;

			float SCALE = {};

		};

		
		void InitAsteroids(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[]);
		void DrawAsteroid(Asteroid bigAsteroids[], Asteroid mediumAsteroids[], Asteroid smallAsteroids[]);
		void AsteroidUpdate(Asteroid bigAsteroids[], Asteroid mediumAsteroids[], Asteroid smallAsteroids[], Spaceship player);


	}
}