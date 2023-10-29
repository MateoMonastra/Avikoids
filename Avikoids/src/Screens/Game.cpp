#include "Game.h"

#include "ProjectUtilities/Utilities.h"
#include "Objects/SpaceShip.h"
#include "Objects/Bullet.h"
#include "Objects/Asteroids.h"

namespace asteroids
{
	namespace game
	{

		static void GameColitions();
		static void Reset();
		static void InitAsteroids();

		const int TOTAL_BIG_ASTEROIDS = 20;
		const int TOTAL_MEDIUM_ASTEROIDS = 40;
		const int TOTAL_SMALL_ASTEROIDS = 80;

		Asteroid bigAsteroids[TOTAL_BIG_ASTEROIDS];
		Asteroid mediumAsteroids[TOTAL_MEDIUM_ASTEROIDS];
		Asteroid smallAsteroids[TOTAL_SMALL_ASTEROIDS];
		Spaceship player;


		void InitGame()
		{

			float scale = 0.15f;
			float WidthF = static_cast<float>(GetScreenWidth());
			float HeightF = static_cast<float>(GetScreenHeight());

			Texture2D bulletTexture = LoadTexture("assets/PNG/Bullets/BaseBullet.png");
			InitPlayer(player,WidthF, HeightF, scale, bulletTexture);

			InitAsteroids();
		}

		void GameUpdate()
		{
			SpaceshipUpdate(player);

			AsteroidUpdate(bigAsteroids, mediumAsteroids, smallAsteroids, player);

			GameColitions();
		}

		void DrawGame()
		{
			SpaceshipDraw(player);

			for (int i = 0; i < player.maxBullets; i++)
			{
				DrawBullet(player.bullets[i]);
			}

			DrawAsteroid(bigAsteroids, mediumAsteroids, smallAsteroids);

			DrawText(TextFormat("SCORE: %i", player.score), 30, 30, 40, WHITE);
			DrawText(TextFormat("SCORE: %i", player.lives), 30, 70, 40, WHITE);
		}

		static void GameColitions()
		{
			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				if (CheckCollisionCircles(player.hitBox.position, player.hitBox.radius, bigAsteroids[i].hitBox.position, bigAsteroids[i].hitBox.radius) && bigAsteroids[i].IsAlive)
				{
					player.lives--;
					Reset();

					if (player.lives == 0)
					{
						player.IsAlive = false;
					}
				}
				for (int j = 0; j < player.maxBullets; j++)
				{
					if (player.bullets[j].IsActive && bigAsteroids[i].IsAlive)
					{
						if (CheckCollisionCircles(player.bullets[j].hitBox.position, player.bullets[j].hitBox.radius, bigAsteroids[i].hitBox.position, bigAsteroids[i].hitBox.radius))
						{
							bigAsteroids[i].IsAlive = false;
							bigAsteroids[i].SpawnChild = true;
							player.bullets[j].IsActive = false;

							player.score += 75;
						}
					}
				}
			}

			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				if (CheckCollisionCircles(player.hitBox.position, player.hitBox.radius, mediumAsteroids[i].hitBox.position, mediumAsteroids[i].hitBox.radius) && mediumAsteroids[i].IsAlive)
				{
					player.lives--;
					Reset();

					if (player.lives == 0)
					{
						player.IsAlive = false;
					}
				}
				for (int j = 0; j < player.maxBullets; j++)
				{
					if (player.bullets[j].IsActive && mediumAsteroids[i].IsAlive)
					{
						if (CheckCollisionCircles(player.bullets[j].hitBox.position, player.bullets[j].hitBox.radius, mediumAsteroids[i].hitBox.position, mediumAsteroids[i].hitBox.radius))
						{
							mediumAsteroids[i].IsAlive = false;
							mediumAsteroids[i].SpawnChild = true;
							player.bullets[j].IsActive = false;

							player.score += 120;

						}
					}
				}
			}

			for (int i = 0; i < TOTAL_SMALL_ASTEROIDS; i++)
			{
				if (CheckCollisionCircles(player.hitBox.position, player.hitBox.radius, smallAsteroids[i].hitBox.position, smallAsteroids[i].hitBox.radius) && smallAsteroids[i].IsAlive)
				{
					player.lives--;
					Reset();

					if (player.lives == 0)
					{
						player.IsAlive = false;
					}
				}
				for (int j = 0; j < player.maxBullets; j++)
				{
					if (player.bullets[j].IsActive && smallAsteroids[i].IsAlive)
					{
						if (CheckCollisionCircles(player.bullets[j].hitBox.position, player.bullets[j].hitBox.radius, smallAsteroids[i].hitBox.position, smallAsteroids[i].hitBox.radius))
						{
							smallAsteroids[i].IsAlive = false;
							smallAsteroids[i].SpawnChild = true;
							player.bullets[j].IsActive = false;

							player.score += 175;
						}
					}
				}
			}
		}

		static void Reset()
		{
			float WidthF = static_cast<float>(GetScreenWidth());
			float HeightF = static_cast<float>(GetScreenHeight());

			player.hitBox.position = { WidthF / 2, HeightF / 2 };

			for (int i = 0; i < player.maxBullets; i++)
			{
				player.bullets[i].IsActive = false;
			}

			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				bigAsteroids[i].IsAlive = false;
			}

			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				mediumAsteroids[i].IsAlive = false;
			}

			for (int i = 0; i < TOTAL_SMALL_ASTEROIDS; i++)
			{
				smallAsteroids[i].IsAlive = false;
			}

			

		}

		static void InitAsteroids()
		{
			Texture2D bigAsteroidTexture = LoadTexture("assets/PNG/Asteroids/BigAsteroid.png");
			Texture2D mediumAsteroidTexture = LoadTexture("assets/PNG/Asteroids/MediumAsteroid.png");
			Texture2D smallAsteroidTexture = LoadTexture("assets/PNG/Asteroids/SmallAsteroid.png");

			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				bigAsteroids[i].texture = bigAsteroidTexture;
			}
			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				mediumAsteroids[i].texture = mediumAsteroidTexture;
			}
			for (int i = 0; i < TOTAL_SMALL_ASTEROIDS; i++)
			{
				smallAsteroids[i].texture = smallAsteroidTexture;
			}

		}
	}
};