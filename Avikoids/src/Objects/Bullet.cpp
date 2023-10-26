#include "Bullet.h"

namespace asteroids
{
	namespace game
	{
		void CreateBullet(Bullet& bullet, Vector2 position, Vector2 rotation)
		{

			bullet.hitBox.color = WHITE;
			bullet.hitBox.radius = 10;
			bullet.hitBox.position.x = position.x;
			bullet.hitBox.position.y = position.y;

			bullet.aceleration = { rotation.x,rotation.y };
			bullet.IsActive = true;
			bullet.speed = { 200 };
		}

		void BulletUpdate(Bullet& bullet)
		{
			if (bullet.IsActive)
			{
				bullet.hitBox.position.x -= bullet.aceleration.x * bullet.speed * GetFrameTime();
				bullet.hitBox.position.y -= bullet.aceleration.y * bullet.speed * GetFrameTime();
			}
		}

		void DrawBullet(Bullet bullet)
		{
			if (bullet.IsActive)
			{
				DrawCircle(static_cast<int>(bullet.hitBox.position.x), static_cast<int>(bullet.hitBox.position.y), bullet.hitBox.radius, bullet.hitBox.color);
			}

		}

	}
}