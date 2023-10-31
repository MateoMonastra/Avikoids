#include "PowerUps.h"

#include "ProjectUtilities/Utilities.h"

namespace asteroids
{
	namespace game
	{
		enum PowerUpType
		{
			Nuke,
			ShotGun
		};

		struct PowerUp
		{
			Circle hitBox;
			Texture2D sprite;
			PowerUpType effect = {};
			double spawnTime = {};
			bool IsActive = false;
		};
		
		static void CreatePowerUp();
		static void PowerUpNuke(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[]);


		const int TOTAL_BIG_ASTEROIDS = 20;
		const int TOTAL_MEDIUM_ASTEROIDS = 40;
		const int TOTAL_SMALL_ASTEROIDS = 80;

		PowerUp actualPowerUp;

		Sound NukeSound;

		void DrawPowerUps()
		{
			float textureFix = 27;
			if (actualPowerUp.IsActive)
			{
			DrawCircle(static_cast<int>(actualPowerUp.hitBox.position.x), static_cast<int>(actualPowerUp.hitBox.position.y), actualPowerUp.hitBox.radius, actualPowerUp.hitBox.color);
			DrawTextureEx(actualPowerUp.sprite, Vector2SubtractValue(actualPowerUp.hitBox.position, textureFix),0,0.1f,actualPowerUp.hitBox.color);
			}
			
			/*DrawButton(actualPowerUp.Sprite);*/
		}

		void UpdatePowerUps(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[], Spaceship& player)
		{
			if (actualPowerUp.IsActive)
			{
				if (CollitionCheckCircles(actualPowerUp.hitBox.position, actualPowerUp.hitBox.radius, player.hitBox.position, player.hitBox.radius))
				{
					if (actualPowerUp.effect == PowerUpType::Nuke)
					{
						PlaySound(NukeSound);

						PowerUpNuke(bigAsteroid, mediumAsteroid, smallAsteroid);
					}
					else if(actualPowerUp.effect == PowerUpType::ShotGun)
					{
						player.IsShotGunOn = true;
						actualPowerUp.IsActive = false;
					}
				}
			}

			if (GetTime() - actualPowerUp.spawnTime > 15)
			{
				CreatePowerUp();
				player.IsShotGunOn = false;
			}
		}

		static void CreatePowerUp()
		{
			int randomNumber = GetRandomValue(1,2);

			if (randomNumber == 1)
			{
				actualPowerUp.effect = PowerUpType::Nuke;
				actualPowerUp.spawnTime = {GetTime()};
				actualPowerUp.IsActive = true;

				actualPowerUp.hitBox.radius = 20;
				actualPowerUp.hitBox.position = { static_cast<float>(GetRandomValue(70,900)),static_cast<float>(GetRandomValue(60,600)) };
				actualPowerUp.hitBox.color = WHITE;

				actualPowerUp.sprite = LoadTexture("res/PNG/Game/Play/PowerUps/NukeIcon.png");

			}
			else if (randomNumber == 2)
			{
				actualPowerUp.effect = PowerUpType::ShotGun;
				actualPowerUp.spawnTime = { GetTime() };
				actualPowerUp.IsActive = true;

				actualPowerUp.hitBox.radius = 20;
				actualPowerUp.hitBox.position = { static_cast<float>(GetRandomValue(70,900)),static_cast<float>(GetRandomValue(60,600)) };
				actualPowerUp.hitBox.color = WHITE;

				actualPowerUp.sprite = LoadTexture("res/PNG/Game/Play/PowerUps/ShotGunIcon.png");
			}

		}

		void InitPowerUp()
		{
			NukeSound = LoadSound("res/MUSIC/SoundEffects/NukeSound.wav");
			SetSoundVolume(NukeSound, 0.1f);
		
		}

		static void PowerUpNuke(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[])
		{

			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				bigAsteroid[i].IsAlive = false;
			}

			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				mediumAsteroid[i].IsAlive = false;
			}

			for (int i = 0; i < TOTAL_SMALL_ASTEROIDS; i++)
			{
				smallAsteroid[i].IsAlive = false;
			}

			actualPowerUp.IsActive = false;

		}

	}
}