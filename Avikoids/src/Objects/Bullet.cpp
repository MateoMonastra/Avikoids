#include "Bullet.h"

namespace asteroids
{
	namespace game
	{
		void CreateBullet(Bullet& bullet, Vector2 position, Vector2 rotation, double playerRotation)
		{

			bullet.hitBox.color = WHITE;
			bullet.hitBox.radius = 6;
			bullet.hitBox.position.x = position.x;
			bullet.hitBox.position.y = position.y;

			bullet.aceleration = { rotation.x,rotation.y };

			bullet.rotation = playerRotation;
			bullet.IsActive = true;
			bullet.speed = { 700 };
		}

		void BulletUpdate(Bullet& bullet)
		{
			if (bullet.IsActive)
			{
				float scale = 0.1f;

				bullet.hitBox.position.x -= bullet.aceleration.x * bullet.speed * GetFrameTime();
				bullet.hitBox.position.y -= bullet.aceleration.y * bullet.speed * GetFrameTime();

				bullet.source = { 0,0,static_cast<float>(bullet.texture.width),static_cast<float>(bullet.texture.height) };
				bullet.dest = { bullet.hitBox.position.x,bullet.hitBox.position.y,static_cast<float>(bullet.texture.width) * scale,static_cast<float>(bullet.texture.height) * scale };
				bullet.origin = { static_cast<float>(bullet.source.width / 2) * scale, static_cast<float> (bullet.source.height / 2) * scale };
			}
		}

		void DrawBullet(Bullet bullet)
		{
			if (bullet.IsActive)
			{
				DrawCircle(static_cast<int>(bullet.hitBox.position.x), static_cast<int>(bullet.hitBox.position.y), bullet.hitBox.radius, bullet.hitBox.color);
				DrawTexturePro(bullet.texture, bullet.source, bullet.dest, bullet.origin, static_cast<float>(bullet.rotation), bullet.hitBox.color);
			}

		}

	}
}