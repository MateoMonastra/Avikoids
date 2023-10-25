#include "Bullet.h"

#include <iostream>

namespace asteroids
{
	namespace game
	{
		void CreateBullet(Bullet& bullet, Vector2 position, Vector2 rotation)
		{

			bullet.colition.color = WHITE;
			bullet.colition.radius = 10;
			bullet.colition.x = position.x;
			bullet.colition.y = position.y;

			bullet.aceleration = { rotation.x,rotation.y };
			bullet.IsActive = true;
			bullet.speed = { 200 };
		}

		void BulletUpdate(Bullet& bullet)
		{
			if (bullet.IsActive)
			{
				bullet.colition.x -= bullet.aceleration.x * bullet.speed * GetFrameTime();
				bullet.colition.y -= bullet.aceleration.y * bullet.speed * GetFrameTime();
			}
		}

		void DrawBullet(Bullet bullet)
		{
			if (bullet.IsActive)
			{
				DrawCircle(static_cast<int>(bullet.colition.x), static_cast<int>(bullet.colition.y), bullet.colition.radius, bullet.colition.color);
			}

		}

	}
}