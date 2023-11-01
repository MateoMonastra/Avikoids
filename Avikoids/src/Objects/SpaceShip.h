#pragma once

#include "ProjectUtilities/Utilities.h"

#include "Bullet.h"

namespace asteroids
{
	namespace game
	{

		struct Spaceship
		{
			Circle hitBox = {};
			static const int maxBullets = 60;
			int currentBullet = 0;

			Rectangle textureRec = {};
			Vector2 origin = {};
			Rectangle dest = {};
			Rectangle source = {};
			double shipRotation = {};

			Vector2 normalizedDirection = {};

			int lives = {};
			bool IsAlive = {};

			Vector2 velocity = {};
			float aceleration = {-1};

			Texture2D texture = {};

			Bullet bullets[maxBullets];

			int score = 0;
			int highScore = 0;

			bool IsAutoShooting = false;
			bool IsShotGunOn = false;

		};


		void SpaceshipUpdate(Spaceship& player);
		void SpaceshipDraw(Spaceship player);
		void InitPlayer(Spaceship& player);
		void UpdateHighScore(Spaceship& player);

	}

}