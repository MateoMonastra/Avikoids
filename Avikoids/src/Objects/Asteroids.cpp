#include "Asteroids.h"


namespace asteroids
{
	namespace game
	{
		static void CreateBigAsteroid(Asteroid& asteroid);
		static void CreateMediumAsteroid(Asteroid& asteroid, Asteroid bigAsteroid);
		/*	static void CreateSmallAsteroid(Asteroid& asteroid, Asteroid mediumAsteroid);*/


		const int TOTAL_BIG_ASTEROIDS = 10;
		const int TOTAL_MEDIUM_ASTEROIDS = 20;
		const int TOTAL_SMALL_ASTEROIDS = 40;

		double timerBigAsteroidSpawn = 0;

		static void CreateBigAsteroid(Asteroid& asteroid)
		{
			float width = static_cast<float>(GetScreenWidth());
			/*float height = static_cast<float>(GetScreenHeight());*/
			int randomSpawn = GetRandomValue(1, 4);


			if (randomSpawn == 1)
			{
				asteroid.hitBox.radius = { 30 };
				asteroid.hitBox.position = { width,static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 30 };
				asteroid.aceleration = { RandomDirection(-1,-100),RandomDirection(1,100) };
				asteroid.IsAlive = true;
			}
			else if (randomSpawn == 2)
			{
				asteroid.hitBox.radius = { 30 };
				asteroid.hitBox.position = { 20, static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 30 };
				asteroid.aceleration = { RandomDirection(1,100),RandomDirection(1,100) };
				asteroid.IsAlive = true;
			}
			else if (randomSpawn == 3)
			{
				asteroid.hitBox.radius = { 30 };
				asteroid.hitBox.position = { static_cast<float>(GetRandomValue(100, 700)), 0 };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 30 };
				asteroid.aceleration = { RandomDirection(1,100),RandomDirection(-1,-100) };
				asteroid.IsAlive = true;
			}
			else if (randomSpawn == 4)
			{
				asteroid.hitBox.radius = { 30 };
				asteroid.hitBox.position = { width, static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 30 };
				asteroid.aceleration = { RandomDirection(1,100),RandomDirection(-1,-100) };
				asteroid.IsAlive = true;
			}



		}

		static void CreateMediumAsteroid(Asteroid& asteroid, Asteroid bigAsteroid)
		{
			

			asteroid.hitBox.radius = { 15 };
			asteroid.hitBox.position = bigAsteroid.hitBox.position;
			asteroid.aceleration = { RandomDirection(-100,100), RandomDirection(-100,100)};
			asteroid.velocity = { 50 };
			asteroid.hitBox.color = WHITE;
			asteroid.IsAlive = true;
		}

		void DrawAsteroid(Asteroid bigAsteroids[], Asteroid mediumAsteroids[], Asteroid smallAsteroids[])
		{
			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				if (bigAsteroids[i].IsAlive)
				{
					DrawTexturePro(bigAsteroids[i].texture, bigAsteroids[i].source, bigAsteroids[i].dest, bigAsteroids[i].origin, bigAsteroids[i].rotation, bigAsteroids[i].hitBox.color);
					DrawCircle(static_cast<int>(bigAsteroids[i].hitBox.position.x), static_cast<int>(bigAsteroids[i].hitBox.position.y), bigAsteroids[i].hitBox.radius, RED);
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
					DrawTexturePro(smallAsteroids[i].texture, smallAsteroids[i].source, smallAsteroids[i].dest, smallAsteroids[i].origin, smallAsteroids[i].rotation, smallAsteroids[i].hitBox.color);
					DrawCircle(static_cast<int>(smallAsteroids[i].hitBox.position.x), static_cast<int>(smallAsteroids[i].hitBox.position.y), smallAsteroids[i].hitBox.radius, smallAsteroids[i].hitBox.color);
				}
			}
				
			
		}

		void AsteroidUpdate(Asteroid bigAsteroid[], Asteroid mediumAsteroid[]/*, Asteroid smallAsteroid[]*/)
		{
			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				if (GetTime() - timerBigAsteroidSpawn > 3 && !bigAsteroid[i].IsAlive)
				{
					CreateBigAsteroid(bigAsteroid[i]);

					i++;

					timerBigAsteroidSpawn = GetTime();
				}


				if (bigAsteroid[i].IsAlive)
				{
					float scale = 0.1f;

					bigAsteroid[i].hitBox.position.x += bigAsteroid[i].aceleration.x * bigAsteroid[i].velocity * GetFrameTime();
					bigAsteroid[i].hitBox.position.y += bigAsteroid[i].aceleration.y * bigAsteroid[i].velocity * GetFrameTime();

					bigAsteroid[i].source = { 0,0,static_cast<float>(bigAsteroid[i].texture.width),static_cast<float>(bigAsteroid[i].texture.height) };
					bigAsteroid[i].dest = { bigAsteroid[i].hitBox.position.x,bigAsteroid[i].hitBox.position.y,static_cast<float>(bigAsteroid[i].texture.width) * scale,static_cast<float>(bigAsteroid[i].texture.height) * scale };
					bigAsteroid[i].origin = { static_cast<float>(bigAsteroid[i].source.width / 2) * scale, static_cast<float> (bigAsteroid[i].source.height / 2) * scale };
				}

				if (bigAsteroid[i].hitBox.position.y + bigAsteroid[i].hitBox.radius / 3 < 0)
				{
					bigAsteroid[i].hitBox.position.y = GetScreenHeight() - bigAsteroid[i].hitBox.radius;
				}
				if (bigAsteroid[i].hitBox.position.y - bigAsteroid[i].hitBox.radius / 3 > GetScreenHeight())
				{
					bigAsteroid[i].hitBox.position.y = bigAsteroid[i].hitBox.radius;
				}
				if (bigAsteroid[i].hitBox.position.x + bigAsteroid[i].hitBox.radius / 3 < 0)
				{
					bigAsteroid[i].hitBox.position.x = GetScreenWidth() + bigAsteroid[i].hitBox.radius;
				}
				if (bigAsteroid[i].hitBox.position.x - bigAsteroid[i].hitBox.radius / 3 > GetScreenWidth())
				{
					bigAsteroid[i].hitBox.position.x = bigAsteroid[i].hitBox.radius;
				}

			}

			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				if (!bigAsteroid[i].IsAlive && bigAsteroid[i].SpawnChild)
				{
					for (int j = 0; j < TOTAL_MEDIUM_ASTEROIDS; j++)
					{
						if (!mediumAsteroid[j].IsAlive) 
						{
							CreateMediumAsteroid(mediumAsteroid[j], bigAsteroid[i]);
							CreateMediumAsteroid(mediumAsteroid[j], bigAsteroid[i]);
						}
					}
				}
			}

			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				if (!mediumAsteroid[i].IsAlive)
				{
					/*CreateMediumAsteroid(mediumAsteroid[currentMediumAsteroid], bigAsteroid[i]);
					currentMediumAsteroid++;
					CreateMediumAsteroid(mediumAsteroid[currentMediumAsteroid], bigAsteroid[i]);
					currentMediumAsteroid++;*/
				}
				else if (mediumAsteroid[i].IsAlive)
				{
					float scale = 0.1f;

					mediumAsteroid[i].hitBox.position.x += mediumAsteroid[i].aceleration.x * mediumAsteroid[i].velocity * GetFrameTime();
					mediumAsteroid[i].hitBox.position.y += mediumAsteroid[i].aceleration.y * mediumAsteroid[i].velocity * GetFrameTime();

					mediumAsteroid[i].source = { 0,0,static_cast<float>(mediumAsteroid[i].texture.width),static_cast<float>(mediumAsteroid[i].texture.height) };
					mediumAsteroid[i].dest = { mediumAsteroid[i].hitBox.position.x,mediumAsteroid[i].hitBox.position.y,static_cast<float>(mediumAsteroid[i].texture.width) * scale,static_cast<float>(mediumAsteroid[i].texture.height) * scale };
					mediumAsteroid[i].origin = { static_cast<float>(mediumAsteroid[i].source.width / 2) * scale, static_cast<float> (mediumAsteroid[i].source.height / 2) * scale };

				}
				if (mediumAsteroid[i].hitBox.position.y + mediumAsteroid[i].hitBox.radius / 3 < 0)
				{
					mediumAsteroid[i].hitBox.position.y = GetScreenHeight() - mediumAsteroid[i].hitBox.radius;
				}
				if (mediumAsteroid[i].hitBox.position.y - mediumAsteroid[i].hitBox.radius / 3 > GetScreenHeight())
				{
					bigAsteroid[i].hitBox.position.y = bigAsteroid[i].hitBox.radius;
				}
				if (mediumAsteroid[i].hitBox.position.x + mediumAsteroid[i].hitBox.radius / 3 < 0)
				{
					mediumAsteroid[i].hitBox.position.x = GetScreenWidth() + mediumAsteroid[i].hitBox.radius;
				}
				if (mediumAsteroid[i].hitBox.position.x - mediumAsteroid[i].hitBox.radius / 3 > GetScreenWidth())
				{
					mediumAsteroid[i].hitBox.position.x = mediumAsteroid[i].hitBox.radius;
				}
			}
		}
	}
}
