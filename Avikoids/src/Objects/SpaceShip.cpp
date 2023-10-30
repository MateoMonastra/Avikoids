#include "SpaceShip.h"

#include "Bullet.h"

namespace asteroids
{
	namespace game
	{
		static void SpaceshipShoot(Spaceship& player);

		double autoShootingTimer = GetTime();

		void InitPlayer(Spaceship& player, float WidthF, float HeightF, float scale, const Texture2D& bulletTexture)
		{
			player.lives = 3;
			player.IsAlive = true;
			player.hitBox.radius = 25;
			player.hitBox.position = { WidthF / 2, HeightF / 2 };
			player.texture = LoadTexture("res/PNG/player/Player.png");

			player.source = { 0,0,static_cast<float>(player.texture.width),static_cast<float>(player.texture.height) };

			player.dest = { player.hitBox.position.x,player.hitBox.position.y,static_cast<float>(player.texture.width) * scale,static_cast<float>(player.texture.height) * scale };

			player.origin = { static_cast<float>(player.source.width / 2) * scale , static_cast<float> (player.source.height / 4) * scale };


			for (int i = 0; i < player.maxBullets; i++)
			{
				player.bullets[i].texture = bulletTexture;
			}
		}

		void SpaceshipUpdate(Spaceship& player)
		{

			SpaceshipMobility(player);

			if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
			{
				if (player.IsAutoShooting)
				{
					player.IsAutoShooting = false;
				}
				else
				{
					player.IsAutoShooting = true;
				}
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || player.IsAutoShooting)
			{
				if (!player.IsAutoShooting)
				{
					SpaceshipShoot(player);
				}
				else
				{
					if (GetTime() - autoShootingTimer > 0.23 )
					{
						SpaceshipShoot(player);

						autoShootingTimer = GetTime();
					}
				}
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
			CreateBullet(player.bullets[player.currentBullet], player.hitBox.position, player.normalizedDirection, player.shipRotation);

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