#include "Asteroids.h"


namespace asteroids
{
	namespace game
	{
		static void CreateBigAsteroid(Asteroid& asteroid);
		/*void CreateMediumAsteroid(Asteroid& asteroid);
		void CreateSmallAsteroid(Asteroid& asteroid);*/

		const int TOTAL_ASTEROIDS = 60;
		int currentAsteroid = 0;

		static void CreateBigAsteroid(Asteroid& asteroid)
		{
			float width = static_cast<float>(GetScreenWidth());
			float height = static_cast<float>(GetScreenHeight());
			int randomSpawn = GetRandomValue(1, 4);


			if (randomSpawn == 1)
			{
				asteroid.hitBox.radius = 30;
				asteroid.hitBox.position = { width,static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.aceleration = { -1,1 };
				asteroid.IsAlive = true;
			}
			else if (randomSpawn == 2)
			{
				asteroid.hitBox.radius = 30;
				asteroid.hitBox.position = { 20, static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.aceleration = { 1,-1 };
				asteroid.IsAlive = true;
			}
			else if (randomSpawn == 3)
			{
				asteroid.hitBox.radius = 30;
				asteroid.hitBox.position = { static_cast<float>(GetRandomValue(100, 700)), 0 };
				asteroid.hitBox.color = WHITE;
				asteroid.hitBox = { 1,1 };
				asteroid.IsAlive = true;
			}
			else if (randomSpawn == 4)
			{
				asteroid.hitBox.radius = 30;
				asteroid.hitBox.position = { static_cast<float>(GetRandomValue(100, 700)), height };
				asteroid.hitBox.color = WHITE;
				asteroid.hitBox = { -1,-1 };
				asteroid.IsAlive = true;
			}



		}

		//void CreateMediumAsteroid(Asteroid& asteroid)
		//{
		//	float scale = 1.0f;
		//	int SpawnNum = 2;

		//	asteroid.texture = LoadTexture("assets/PNG/enemys/BigEnemy.png");
		//	asteroid.source = { 0,0,static_cast<float>(asteroid.texture.width),static_cast<float>(asteroid.texture.height) };
		//	asteroid.dest = { asteroid.colition.x,asteroid.colition.y,static_cast<float>(asteroid.texture.width) * scale,static_cast<float>(asteroid.texture.height) * scale };
		//	asteroid.origin = { static_cast<float>(asteroid.source.width / 2) * scale, static_cast<float> (asteroid.source.height / 2) * scale };
		//	asteroid.IsAlive = true;

		//	for (int i = 0; i < SpawnNum; i++)
		//	{
		//	asteroid.colition.radius = 15;
		//	asteroid.colition.x = static_cast<float>(GetScreenWidth()) / 2;
		//	asteroid.colition.y = static_cast<float>(GetScreenHeight()) / 3;
		//	}
		//}

		void DrawAsteroid(Asteroid bigAsteroids[], Asteroid mediumAsteroids[], Asteroid smallAsteroids[])
		{
			for (int i = 0; i < TOTAL_ASTEROIDS; i++)
			{
				if (bigAsteroids[i].IsAlive)
				{
					DrawTexturePro(bigAsteroids[i].textureBigAsteroid, bigAsteroids[i].source, bigAsteroids[i].dest, bigAsteroids[i].origin, bigAsteroids[i].rotation, bigAsteroids[i].hitBox.color);
					DrawCircle(static_cast<int>(bigAsteroids[i].hitBox.position.x), static_cast<int>(bigAsteroids[i].hitBox.position.y), bigAsteroids[i].hitBox.radius, RED);
				}
				if (mediumAsteroids[i].IsAlive)
				{
					DrawTexturePro(mediumAsteroids[i].textureMediumAsteroid, mediumAsteroids[i].source, mediumAsteroids[i].dest, mediumAsteroids[i].origin, mediumAsteroids[i].rotation, mediumAsteroids[i].hitBox.color);
					DrawCircle(static_cast<int>(mediumAsteroids[i].hitBox.position.x), static_cast<int>(mediumAsteroids[i].hitBox.position.y), mediumAsteroids[i].hitBox.radius, mediumAsteroids[i].hitBox.color);
				}
				if (smallAsteroids[i].IsAlive)
				{
					DrawTexturePro(smallAsteroids[i].textureSmallAsteroid, smallAsteroids[i].source, smallAsteroids[i].dest, smallAsteroids[i].origin, smallAsteroids[i].rotation, smallAsteroids[i].hitBox.color);
					DrawCircle(static_cast<int>(smallAsteroids[i].hitBox.position.x), static_cast<int>(smallAsteroids[i].hitBox.position.y), smallAsteroids[i].hitBox.radius, smallAsteroids[i].hitBox.color);
				}

			}
		}

		void AsteroidUpdate(Asteroid asteroids[])
		{
			int bigAsteroidsCount = {};
			for (int i = 0; i < TOTAL_ASTEROIDS; i++)
			{
				if (asteroids[i].IsAlive)
				{
					bigAsteroidsCount++;
				}
			}

			for (int i = 0; i < TOTAL_ASTEROIDS; i++)
			{
				if (bigAsteroidsCount < 4)
				{
					CreateBigAsteroid(asteroids[currentAsteroid]);

					currentAsteroid++;

					if (currentAsteroid >= TOTAL_ASTEROIDS)
					{
						currentAsteroid = 0;
					}
				}
				

					if (asteroids[i].IsAlive)
					{
						float scale = 0.1f;

						asteroids[i].hitBox.position.x += asteroids[i].aceleration.x * asteroids[i].velocity * GetFrameTime();
						asteroids[i].hitBox.position.y += asteroids[i].aceleration.y * asteroids[i].velocity * GetFrameTime();

						asteroids[i].source = { 0,0,static_cast<float>(asteroids[i].textureBigAsteroid.width),static_cast<float>(asteroids[i].textureBigAsteroid.height) };
						asteroids[i].dest = { asteroids[i].hitBox.position.x,asteroids[i].hitBox.position.y,static_cast<float>(asteroids[i].textureBigAsteroid.width) * scale,static_cast<float>(asteroids[i].textureBigAsteroid.height) * scale };
						asteroids[i].origin = { static_cast<float>(asteroids[i].source.width / 2) * scale, static_cast<float> (asteroids[i].source.height / 2) * scale };
					}

					if (asteroids[i].hitBox.position.y < 0)
					{
						asteroids[i].hitBox.position.y = GetScreenHeight() - asteroids[i].hitBox.radius / 5;
					}
					if (asteroids[i].hitBox.position.y > GetScreenHeight())
					{
						asteroids[i].hitBox.position.y = asteroids[i].hitBox.radius / 5;
					}
					if (asteroids[i].hitBox.position.x < 0)
					{
						asteroids[i].hitBox.position.x = GetScreenWidth() + asteroids[i].hitBox.radius / 5;
					}
					if (asteroids[i].hitBox.position.x > GetScreenWidth())
					{
						asteroids[i].hitBox.position.x = asteroids[i].hitBox.radius / 5;
					}
				
			}
		}
	}
}