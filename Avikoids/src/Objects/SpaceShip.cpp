#include "SpaceShip.h"

#include "Bullet.h"

namespace asteroids
{
	namespace game
	{
		static void SpaceshipShoot(Spaceship& player);

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
			if (player.hitBox.position.y < 0)
			{
				player.hitBox.position.y = GetScreenHeight() - player.textureRec.height;
			}
			if (player.hitBox.position.y > GetScreenHeight())
			{
				player.hitBox.position.y = player.textureRec.height;
			}
			if (player.hitBox.position.x < 0)
			{
				player.hitBox.position.x = GetScreenWidth() - player.textureRec.width;
			}
			if (player.hitBox.position.x > GetScreenWidth())
			{
				player.hitBox.position.x = player.textureRec.width;
			}

			Vector2 mousePos = GetMousePosition();

			Vector2 direction = Vector2Subtract(player.hitBox.position, mousePos);

			double angle = atan2(static_cast<double>(direction.y), static_cast<double>(direction.x)) * RAD2DEG + 90;

			player.shipRotation = angle;

			player.normalizedDirection = Vector2Normalize(direction);

			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				player.velocity = Vector2Add(player.velocity, Vector2Scale(direction, player.aceleration * GetFrameTime()));
			}

			player.hitBox.position = Vector2Add(player.hitBox.position, Vector2Scale(player.velocity, GetFrameTime()));
			player.dest.x = player.hitBox.position.x;
			player.dest.y = player.hitBox.position.y;
		}

		static void SpaceshipShoot(Spaceship& player)
		{
			CreateBullet(player.bullets[player.currentBullet], player.hitBox.position, player.normalizedDirection);

			player.currentBullet++;

			if (player.currentBullet >= player.maxBullets)
			{
				player.currentBullet = 0;
			}
		}

		void SpaceshipDraw(Spaceship player)
		{
			if (player.IsAlive)
			{
				DrawTexturePro(player.texture, player.source, player.dest, player.origin, static_cast<float>(player.shipRotation), WHITE);
				DrawCircle(static_cast<int>(player.hitBox.position.x), static_cast<int>(player.hitBox.position.y), player.hitBox.radius, GREEN);
			}
		}
	}
}