#pragma once

#include "ProjectUtilities/Utilities.h"
#include "Bullet.h"

namespace asteroids
{
	namespace game
	{

		struct Spaceship
		{
			static const int maxBullets = 30;
			int currentBullet = 0;

			Rectangle textureRec = {};

			Rectangle dest = {};
			Rectangle source = {};

			Vector2 normalizedDirection = {};
			Vector2 position = {};
			Vector2 origin = {};

			double shipRotation = {};
			Vector2 velocity = {};
			float aceleration = { -1 };

			Texture2D texture = {};

			Bullet bullets[maxBullets];
		};


		void SpaceshipUpdate(Spaceship& player);
		void SpaceshipMobility(Spaceship& player);
		void SpaceshipShoot(Spaceship& player);

	}

}