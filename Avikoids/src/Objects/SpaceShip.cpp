#include "SpaceShip.h"

#include "Bullet.h"

namespace asteroids
{
	namespace game
	{
		static void SpaceshipShoot(Spaceship& player);
		static void SpaceshipMobility(Spaceship& player);

		double autoShootingTimer = GetTime();
		float animationTimer = 0;

		Sound Shoot;


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
					float shootRecoil = 0.23f;
					if (GetTime() - autoShootingTimer > shootRecoil)
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

		void SpaceshipDraw(Spaceship player)
		{
			if (player.IsAlive)
			{
				DrawTexturePro(player.texture, player.source, player.dest, Vector2AddValue(player.origin, player.hitBox.radius), static_cast<float>(player.shipRotation), WHITE);
			}
		}

		void InitPlayer(Spaceship& player)
		{
			float scale = 0.18f;
			float WidthF = static_cast<float>(GetScreenWidth());
			float HeightF = static_cast<float>(GetScreenHeight());
			Texture2D bulletTexture = LoadTexture("res/PNG/Game/Play/Bullets/BaseBullet.png");


			player.lives = 3;
			player.IsAlive = true;
			player.hitBox.radius = 30;
			player.hitBox.position = { WidthF / 2, HeightF / 2 };
			player.texture = LoadTexture("res/PNG/Game/Play/player/Player.png");
			player.score = 0;
			player.velocity = { 0, 0 };

			const float playerOriginWidth = static_cast<float>((player.source.width / 3) / 4) * scale - 20;
			const float playerOriginHeight = static_cast<float> (player.source.height / 4) * scale;

			float playerDestWidth = (player.hitBox.radius * 8) / 3;
			float playerDestHeight = player.hitBox.radius * 5;

			player.source = { 0,0,static_cast<float>(player.texture.width),static_cast<float>(player.texture.height) };

			player.dest = { player.hitBox.position.x,player.hitBox.position.y,playerDestWidth,playerDestHeight };

			player.origin = { playerOriginWidth, playerOriginHeight };

			Shoot = LoadSound("res/MUSIC/SoundEffects/ShootSound.mp3");

			SetSoundVolume(Shoot, 0.3f);


			for (int i = 0; i < player.maxBullets; i++)
			{
				player.bullets[i].texture = bulletTexture;
			}
		}

		void UpdateHighScore(Spaceship& player)
		{

			if (player.score > player.highScore)
			{
				player.highScore = player.score;
			}

		}

		static void SpaceshipShoot(Spaceship& player)
		{
			if (!player.IsShotGunOn)
			{
				CreateBullet(player.bullets[player.currentBullet], player.hitBox.position, player.normalizedDirection, player.shipRotation);

				player.currentBullet++;

				if (player.currentBullet >= player.maxBullets)
				{
					player.currentBullet = 0;
				}
			}
			else
			{
				float angle = 0.3f;

				CreateBullet(player.bullets[player.currentBullet], player.hitBox.position, player.normalizedDirection, player.shipRotation);
				player.currentBullet++;

				if (player.currentBullet >= player.maxBullets)
				{
					player.currentBullet = 0;
				}

				CreateBullet(player.bullets[player.currentBullet], player.hitBox.position, Vector2Rotate(player.normalizedDirection, angle), player.shipRotation);
				player.currentBullet++;

				if (player.currentBullet >= player.maxBullets)
				{
					player.currentBullet = 0;
				}

				CreateBullet(player.bullets[player.currentBullet], player.hitBox.position, Vector2Rotate(player.normalizedDirection, -angle), player.shipRotation);
				player.currentBullet++;

				if (player.currentBullet >= player.maxBullets)
				{
					player.currentBullet = 0;
				}
			}

			PlaySound(Shoot);
		}

		static void SpaceshipMobility(Spaceship& player)
		{
			float playerDestWidth = (player.hitBox.radius * 8) / 3;
			float playerDestHeight = player.hitBox.radius * 5;

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
				float texturePos1 = player.texture.width / 3.0f;
				float texturePos2 = player.texture.width / 3.0f * 2.0f;

				const float animationCooldown = 0.3f;

				animationTimer += GetFrameTime();

				if (animationTimer >= animationCooldown)
				{
					if (player.source.x == texturePos1)
					{
						player.source = { texturePos2,0,static_cast<float>(player.texture.width / 3),static_cast<float>(player.texture.height) };
					}
					else
					{
						player.source = { texturePos1,0,static_cast<float>(player.texture.width / 3),static_cast<float>(player.texture.height) };
					}

					animationTimer = 0;
				}

				player.velocity = Vector2Add(player.velocity, Vector2Scale(direction, player.aceleration * GetFrameTime()));
			}
			else
			{
				player.source = { 0,0,static_cast<float>(player.texture.width / 3),static_cast<float>(player.texture.height) };
			}

			player.hitBox.position = Vector2Add(player.hitBox.position, Vector2Scale(player.velocity, GetFrameTime()));
			player.dest = { player.hitBox.position.x,player.hitBox.position.y,playerDestWidth,playerDestHeight };

		}


	}
}