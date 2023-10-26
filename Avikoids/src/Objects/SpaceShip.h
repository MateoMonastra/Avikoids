#pragma once

#include "ProjectUtilities/Utilities.h"
#include "Bullet.h"

namespace asteroids
{
	namespace game
	{

		struct Spaceship
		{
			Circle hitBox;
			static const int maxBullets = 30;
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
			float aceleration = { -1 };

			Texture2D texture = {};

			Bullet bullets[maxBullets];
		};


		void SpaceshipUpdate(Spaceship& player);
		void SpaceshipMobility(Spaceship& player);
		void SpaceshipDraw(Spaceship player);

	}

}