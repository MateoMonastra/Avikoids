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

			const int ASTEROID_DIVITION = 3;

			float SCALE = {};

			const float BIG_ASTEROID_SPAWN_RECOIL = 1.5f;
			const float FOLLOWING_ASTEROID_SPAWN_RECOIL = 5.5f;
		};

		
		void InitAsteroids(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[], Asteroid followingAsteroids[]);
		void DrawAsteroid(Asteroid bigAsteroids[], Asteroid mediumAsteroids[], Asteroid smallAsteroids[], Asteroid followingAsteroids[]);
		void AsteroidUpdate(Asteroid bigAsteroids[], Asteroid mediumAsteroids[], Asteroid smallAsteroids[], Spaceship player, Asteroid followingAsteroids[]);


	}
}