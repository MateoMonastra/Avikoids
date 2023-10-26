#include "SpaceShip.h"

#include "Bullet.h"

namespace asteroids
{
	namespace game
	{
		void SpaceshipUpdate(Spaceship& player)
		{

			SpaceshipMobility(player);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				SpaceshipShoot(player);
			}

			for (int i = 0; i < player.maxBullets; i++)
			{
				BulletUpdate(player.bullets[i]);
			}
		}

		void SpaceshipMobility(Spaceship& player)
		{
			if (player.position.y < 0)
			{
				player.position.y = GetScreenHeight() - player.textureRec.height;
			}
			if (player.position.y > GetScreenHeight())
			{
				player.position.y = player.textureRec.height;
			}
			if (player.position.x < 0)
			{
				player.position.x = GetScreenWidth() - player.textureRec.width;
			}
			if (player.position.x > GetScreenWidth())
			{
				player.position.x = player.textureRec.width;
			}

			Vector2 mousePos = GetMousePosition();

			Vector2 direction = Vector2Subtract(player.position, mousePos);

			double angle = atan2(static_cast<double>(direction.y), static_cast<double>(direction.x)) * RAD2DEG + 90;

			player.shipRotation = angle;

			 player.normalizedDirection = Vector2Normalize(direction);

			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				player.velocity = Vector2Add(player.velocity, Vector2Scale(direction, player.aceleration * GetFrameTime()));
			}

			player.position = Vector2Add(player.position, Vector2Scale(player.velocity, GetFrameTime()));
			player.dest.x = player.position.x;
			player.dest.y = player.position.y;
		}

		void SpaceshipShoot(Spaceship& player)
		{
			CreateBullet(player.bullets[player.currentBullet],player.position,player.normalizedDirection);
			
			player.currentBullet++;

			if (player.currentBullet >= player.maxBullets)
			{
				player.currentBullet = 0;
			}
		}
	}
}