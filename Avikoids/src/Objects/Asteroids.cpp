#include "Asteroids.h"
#include <iostream>


namespace asteroids
{
	namespace game
	{
		static void CreateBigAsteroid(Asteroid& asteroid);
		static void CreateMediumAsteroid(Asteroid& asteroid, Asteroid bigAsteroid);
		static void CreateSmallAsteroid(Asteroid& asteroid, Asteroid mediumAsteroid);


		const int TOTAL_BIG_ASTEROIDS = 20;
		const int TOTAL_MEDIUM_ASTEROIDS = 40;
		const int TOTAL_SMALL_ASTEROIDS = 80;

		double timerBigAsteroidSpawn = 0;

		static void CreateBigAsteroid(Asteroid& asteroid)
		{
			float width = static_cast<float>(GetScreenWidth());
			/*float height = static_cast<float>(GetScreenHeight());*/
			int randomSpawn = GetRandomValue(1, 4);


			if (randomSpawn == 1)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(50, 55)) };
				asteroid.hitBox.position = { width,static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 40 };
				asteroid.aceleration = { RandomDirection(-1,-100),RandomDirection(1,100) };
				asteroid.IsAlive = true;
				asteroid.SpawnChild = false;
				asteroid.SCALE = asteroid.hitBox.radius / 150;
			}
			else if (randomSpawn == 2)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(50, 55)) };
				asteroid.hitBox.position = { 20, static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 40 };
				asteroid.aceleration = { RandomDirection(1,100),RandomDirection(1,100) };
				asteroid.IsAlive = true;
				asteroid.SpawnChild = false;
				asteroid.SCALE = asteroid.hitBox.radius / 200;
			}
			else if (randomSpawn == 3)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(50, 55)) };
				asteroid.hitBox.position = { static_cast<float>(GetRandomValue(100, 700)), 0 };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 40 };
				asteroid.aceleration = { RandomDirection(1,100),RandomDirection(-1,-100) };
				asteroid.IsAlive = true;
				asteroid.SpawnChild = false;
				asteroid.SCALE = asteroid.hitBox.radius / 200;
			}
			else if (randomSpawn == 4)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(50, 55)) };
				asteroid.hitBox.position = { width, static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 40 };
				asteroid.aceleration = { RandomDirection(1,100),RandomDirection(-1,-100) };
				asteroid.IsAlive = true;
				asteroid.SpawnChild = false;
				asteroid.SCALE = asteroid.hitBox.radius / 220;
			}



		}

		static void CreateMediumAsteroid(Asteroid& asteroid, Asteroid bigAsteroid)
		{

			asteroid.hitBox.radius = { bigAsteroid.hitBox.radius / 2 };
			asteroid.hitBox.position = bigAsteroid.hitBox.position;
			asteroid.aceleration = { RandomDirection(-100,100), RandomDirection(-100,100) };
			asteroid.velocity = { 50 };
			asteroid.hitBox.color = WHITE;
			asteroid.IsAlive = true;
			asteroid.SpawnChild = false;
			asteroid.SCALE = asteroid.hitBox.radius / 200;
			std::cout << "Asteroide Mediano Creado " << &bigAsteroid << std::endl;
		}

		static void CreateSmallAsteroid(Asteroid& asteroid, Asteroid mediumAsteroid)
		{
			asteroid.hitBox.radius = { mediumAsteroid.hitBox.radius / 2 };
			asteroid.hitBox.position = mediumAsteroid.hitBox.position;
			asteroid.aceleration = { RandomDirection(-100,100), RandomDirection(-100,100) };
			asteroid.velocity = { 60 };
			asteroid.hitBox.color = WHITE;
			asteroid.IsAlive = true;
			asteroid.SCALE = asteroid.hitBox.radius / 160;
			std::cout << "Asteroide pequeño Creado " << &mediumAsteroid << std::endl;
		}

		void DrawAsteroid(Asteroid bigAsteroids[], Asteroid mediumAsteroids[], Asteroid smallAsteroids[])
		{
			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				if (bigAsteroids[i].IsAlive)
				{
					DrawCircle(static_cast<int>(bigAsteroids[i].hitBox.position.x), static_cast<int>(bigAsteroids[i].hitBox.position.y), bigAsteroids[i].hitBox.radius, RED);
					DrawTexturePro(bigAsteroids[i].texture, bigAsteroids[i].source, bigAsteroids[i].dest, bigAsteroids[i].origin, bigAsteroids[i].rotation, bigAsteroids[i].hitBox.color);
				}
			}
			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				if (mediumAsteroids[i].IsAlive)
				{
					DrawCircle(static_cast<int>(mediumAsteroids[i].hitBox.position.x), static_cast<int>(mediumAsteroids[i].hitBox.position.y), mediumAsteroids[i].hitBox.radius, mediumAsteroids[i].hitBox.color);
					DrawTexturePro(mediumAsteroids[i].texture, mediumAsteroids[i].source, mediumAsteroids[i].dest, mediumAsteroids[i].origin, mediumAsteroids[i].rotation, mediumAsteroids[i].hitBox.color);
				}
			}

			for (int i = 0; i < TOTAL_SMALL_ASTEROIDS; i++)
			{
				if (smallAsteroids[i].IsAlive)
				{
					DrawCircle(static_cast<int>(smallAsteroids[i].hitBox.position.x), static_cast<int>(smallAsteroids[i].hitBox.position.y), smallAsteroids[i].hitBox.radius, smallAsteroids[i].hitBox.color);
					DrawTexturePro(smallAsteroids[i].texture, smallAsteroids[i].source, smallAsteroids[i].dest, smallAsteroids[i].origin, smallAsteroids[i].rotation, smallAsteroids[i].hitBox.color);
				}
			}


		}

		void AsteroidUpdate(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[], Spaceship player)
		{
			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				if (bigAsteroid[i].IsAlive)
				{
					bigAsteroid[i].hitBox.position.x += bigAsteroid[i].aceleration.x * bigAsteroid[i].velocity * GetFrameTime();
					bigAsteroid[i].hitBox.position.y += bigAsteroid[i].aceleration.y * bigAsteroid[i].velocity * GetFrameTime();

					Vector2 direction = Vector2Subtract(bigAsteroid[i].hitBox.position, player.hitBox.position);

					double angle = atan2(static_cast<double>(direction.y), static_cast<double>(direction.x)) * RAD2DEG + 90;

					bigAsteroid[i].rotation = static_cast<float>(angle);

					bigAsteroid[i].source = { 0,0,static_cast<float>(bigAsteroid[i].texture.width),static_cast<float>(bigAsteroid[i].texture.height) };
					bigAsteroid[i].dest = { bigAsteroid[i].hitBox.position.x,bigAsteroid[i].hitBox.position.y,static_cast<float>(bigAsteroid[i].texture.width) * bigAsteroid[i].SCALE,static_cast<float>(bigAsteroid[i].texture.height) * bigAsteroid[i].SCALE };
					bigAsteroid[i].origin = { static_cast<float>(bigAsteroid[i].source.width / 2) * bigAsteroid[i].SCALE, static_cast<float> (bigAsteroid[i].source.height / 2) * bigAsteroid[i].SCALE };


					if (bigAsteroid[i].hitBox.position.y + bigAsteroid[i].hitBox.radius < 0)
					{
						bigAsteroid[i].hitBox.position.y = GetScreenHeight() - bigAsteroid[i].hitBox.radius;
					}
					if (bigAsteroid[i].hitBox.position.y - bigAsteroid[i].hitBox.radius > GetScreenHeight())
					{
						bigAsteroid[i].hitBox.position.y = bigAsteroid[i].hitBox.radius;
					}
					if (bigAsteroid[i].hitBox.position.x + bigAsteroid[i].hitBox.radius < 0)
					{
						bigAsteroid[i].hitBox.position.x = GetScreenWidth() - bigAsteroid[i].hitBox.radius;
					}
					if (bigAsteroid[i].hitBox.position.x - bigAsteroid[i].hitBox.radius > GetScreenWidth())
					{
						bigAsteroid[i].hitBox.position.x = bigAsteroid[i].hitBox.radius;
					}
				}

				if (!bigAsteroid[i].IsAlive && bigAsteroid[i].SpawnChild)
				{
					int spawnChildCounter = 0;
					for (int j = 0; j < TOTAL_MEDIUM_ASTEROIDS; j++)
					{
						if (!mediumAsteroid[j].IsAlive && bigAsteroid[i].SpawnChild)
						{
							CreateMediumAsteroid(mediumAsteroid[j], bigAsteroid[i]);
							spawnChildCounter++;

						}
						if (spawnChildCounter >= bigAsteroid[i].ASTEROID_DIVITION)
						{
							bigAsteroid[i].SpawnChild = false;
						}
					}
				}

				if (GetTime() - timerBigAsteroidSpawn > 2 && !bigAsteroid[i].IsAlive)
				{
					CreateBigAsteroid(bigAsteroid[i]);

					timerBigAsteroidSpawn = GetTime();
				}
			}

			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				if (mediumAsteroid[i].IsAlive)
				{

					mediumAsteroid[i].hitBox.position.x += mediumAsteroid[i].aceleration.x * mediumAsteroid[i].velocity * GetFrameTime();
					mediumAsteroid[i].hitBox.position.y += mediumAsteroid[i].aceleration.y * mediumAsteroid[i].velocity * GetFrameTime();

					Vector2 direction = Vector2Subtract(mediumAsteroid[i].hitBox.position, player.hitBox.position);

					double angle = atan2(static_cast<double>(direction.y), static_cast<double>(direction.x)) * RAD2DEG + 90;

					mediumAsteroid[i].rotation = static_cast<float>(angle);

					mediumAsteroid[i].source = { 0,0,static_cast<float>(mediumAsteroid[i].texture.width),static_cast<float>(mediumAsteroid[i].texture.height) };
					mediumAsteroid[i].dest = { mediumAsteroid[i].hitBox.position.x,mediumAsteroid[i].hitBox.position.y,static_cast<float>(mediumAsteroid[i].texture.width) * mediumAsteroid[i].SCALE,static_cast<float>(mediumAsteroid[i].texture.height) * mediumAsteroid[i].SCALE };
					mediumAsteroid[i].origin = { static_cast<float>(mediumAsteroid[i].source.width / 2) * mediumAsteroid[i].SCALE, static_cast<float> (mediumAsteroid[i].source.height / 2) * mediumAsteroid[i].SCALE };


					if (mediumAsteroid[i].hitBox.position.y + mediumAsteroid[i].hitBox.radius < 0)
					{
						mediumAsteroid[i].hitBox.position.y = GetScreenHeight() - mediumAsteroid[i].hitBox.radius;
					}
					if (mediumAsteroid[i].hitBox.position.y - mediumAsteroid[i].hitBox.radius > GetScreenHeight())
					{
						mediumAsteroid[i].hitBox.position.y = mediumAsteroid[i].hitBox.radius;
					}
					if (mediumAsteroid[i].hitBox.position.x + mediumAsteroid[i].hitBox.radius < 0)
					{
						mediumAsteroid[i].hitBox.position.x = GetScreenWidth() - mediumAsteroid[i].hitBox.radius;
					}
					if (mediumAsteroid[i].hitBox.position.x - mediumAsteroid[i].hitBox.radius > GetScreenWidth())
					{
						mediumAsteroid[i].hitBox.position.x = mediumAsteroid[i].hitBox.radius;
					}
				}
				else if (!mediumAsteroid[i].IsAlive && mediumAsteroid[i].SpawnChild)
				{
					int spawnChildCounter = 0;

					for (int j = 0; j < TOTAL_SMALL_ASTEROIDS; j++)
					{
						if (!smallAsteroid[j].IsAlive && mediumAsteroid[i].SpawnChild)
						{
							CreateSmallAsteroid(smallAsteroid[j], mediumAsteroid[i]);
							spawnChildCounter++;

						}
						if (spawnChildCounter >= mediumAsteroid[i].ASTEROID_DIVITION)
						{
							mediumAsteroid[i].SpawnChild = false;
						}
					}
				}
			}

			for (int i = 0; i < TOTAL_SMALL_ASTEROIDS; i++)
			{
				if (smallAsteroid[i].IsAlive)
				{

					smallAsteroid[i].hitBox.position.x += smallAsteroid[i].aceleration.x * smallAsteroid[i].velocity * GetFrameTime();
					smallAsteroid[i].hitBox.position.y += smallAsteroid[i].aceleration.y * smallAsteroid[i].velocity * GetFrameTime();

					smallAsteroid[i].source = { 0,0,static_cast<float>(smallAsteroid[i].texture.width),static_cast<float>(smallAsteroid[i].texture.height) };
					smallAsteroid[i].dest = { smallAsteroid[i].hitBox.position.x,smallAsteroid[i].hitBox.position.y,static_cast<float>(smallAsteroid[i].texture.width) * smallAsteroid[i].SCALE,static_cast<float>(smallAsteroid[i].texture.height) * smallAsteroid[i].SCALE };
					smallAsteroid[i].origin = { static_cast<float>(smallAsteroid[i].source.width / 2) * smallAsteroid[i].SCALE, static_cast<float> (smallAsteroid[i].source.height / 2) * smallAsteroid[i].SCALE };


					if (smallAsteroid[i].hitBox.position.y + smallAsteroid[i].hitBox.radius < 0)
					{
						smallAsteroid[i].hitBox.position.y = GetScreenHeight() - smallAsteroid[i].hitBox.radius;
					}
					if (smallAsteroid[i].hitBox.position.y - smallAsteroid[i].hitBox.radius > GetScreenHeight())
					{
						smallAsteroid[i].hitBox.position.y = smallAsteroid[i].hitBox.radius;
					}
					if (smallAsteroid[i].hitBox.position.x + smallAsteroid[i].hitBox.radius < 0)
					{
						smallAsteroid[i].hitBox.position.x = GetScreenWidth() - smallAsteroid[i].hitBox.radius;
					}
					if (smallAsteroid[i].hitBox.position.x - smallAsteroid[i].hitBox.radius > GetScreenWidth())
					{
						smallAsteroid[i].hitBox.position.x = smallAsteroid[i].hitBox.radius;
					}
				}
			}
		}
	}
}
