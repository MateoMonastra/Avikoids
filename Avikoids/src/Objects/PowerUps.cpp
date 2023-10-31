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
			Button Sprite;
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
			if (actualPowerUp.IsActive)
			{
			DrawCircle(static_cast<int>(actualPowerUp.hitBox.position.x), static_cast<int>(actualPowerUp.hitBox.position.y), actualPowerUp.hitBox.radius, YELLOW);
			}

			/*DrawButton(actualPowerUp.Sprite);*/
		}

		void UpdatePowerUps(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[], Spaceship player)
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
				}
			}
			
			if (GetTime() - actualPowerUp.spawnTime > 10)
			{
				CreatePowerUp();
			}
		}

		static void CreatePowerUp()
		{
			int randomNumber = 1;

			if (randomNumber == 1)
			{
				actualPowerUp.effect = PowerUpType::Nuke;
				actualPowerUp.spawnTime = {GetTime()};
				actualPowerUp.IsActive = true;

				actualPowerUp.hitBox.radius = 20;
				actualPowerUp.hitBox.position = { static_cast<float>(GetRandomValue(70,900)),static_cast<float>(GetRandomValue(60,600)) };

			}

		}

		void InitPowerUp()
		{
			NukeSound = LoadSound("res/MUSIC/SoundEffects/NukeSound");
			SetSoundVolume(NukeSound, 0.8f);
		
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