#pragma once

#include "ProjectUtilities/Utilities.h"

namespace asteroids
{
	namespace game
	{
		struct Circle
		{
			Vector2 position = {};
			float radius = {};
			Color color = {};
		};

		struct Bullet
		{

			Circle hitBox = {};
			bool IsActive = {};

			Vector2 aceleration = {};
			float speed = {};

		};

		void CreateBullet(Bullet& bullet, Vector2 position, Vector2 rotation);
		void BulletUpdate(Bullet& bullet);
		void DrawBullet(Bullet bullet);
	}
}