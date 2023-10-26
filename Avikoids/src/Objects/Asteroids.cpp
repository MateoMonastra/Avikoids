#include "Asteroids.h"


namespace asteroids
{
	namespace game
	{
		static void CreateBigAsteroid(Asteroid& asteroid);
		/*void CreateMediumAsteroid(Asteroid& asteroid);
		void CreateSmallAsteroid(Asteroid& asteroid);*/

		const int MAX_ASTEROIDS = 60;
		int bigAsteroidsCount = {};

		static void CreateBigAsteroid(Asteroid& asteroid)
		{
				float scale = 0.1f;

			if (bigAsteroidsCount < 10)
			{
				float width = static_cast<float>(GetScreenWidth());
				float height = static_cast<float>(GetScreenHeight());
				int randomSpawn = GetRandomValue(1, 3);


				if (randomSpawn == 1)
				{
					asteroid.colition.radius = 30;
					asteroid.colition = { width, height / 2 };
					asteroid.colition.color = WHITE;
					asteroid.aceleration = { -1,1 };
					asteroid.texture = LoadTexture("assets/PNG/enemys/BigEnemy.png");
					asteroid.IsAlive = true;
				}
				else if (randomSpawn == 2)
				{
					asteroid.colition.radius = 30;
					asteroid.colition = { 20, height / 3 };
					asteroid.colition.color = WHITE;
					asteroid.aceleration = { 1,-1 };
					asteroid.texture = LoadTexture("assets/PNG/enemys/BigEnemy.png");
					asteroid.IsAlive = true;
				}
				else if (randomSpawn == 3)
				{
					asteroid.colition.radius = 30;
					asteroid.colition = { width/2, height };
					asteroid.colition.color = WHITE;
					asteroid.aceleration = { -1,-1 };
					asteroid.texture = LoadTexture("assets/PNG/enemys/BigEnemy.png");
					asteroid.IsAlive = true;
				}
				bigAsteroidsCount++;
			}
				asteroid.source = { 0,0,static_cast<float>(asteroid.texture.width),static_cast<float>(asteroid.texture.height) };
				asteroid.dest = { asteroid.colition.x,asteroid.colition.y,static_cast<float>(asteroid.texture.width) * scale,static_cast<float>(asteroid.texture.height) * scale };
				asteroid.origin = { static_cast<float>(asteroid.source.width / 2) * scale, static_cast<float> (asteroid.source.height / 2) * scale };
				
			

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
			for (int i = 0; i < MAX_ASTEROIDS; i++)
			{
				if (bigAsteroids[i].IsAlive)
				{
					DrawCircle(static_cast<int>(bigAsteroids[i].colition.x), static_cast<int>(bigAsteroids[i].colition.y), bigAsteroids[i].colition.radius, bigAsteroids[i].colition.color);
					DrawTexturePro(bigAsteroids[i].texture, bigAsteroids[i].source, bigAsteroids[i].dest, bigAsteroids[i].origin, bigAsteroids[i].rotation, bigAsteroids[i].colition.color);
				}
				if (mediumAsteroids[i].IsAlive)
				{
					DrawCircle(static_cast<int>(mediumAsteroids[i].colition.x), static_cast<int>(mediumAsteroids[i].colition.y), mediumAsteroids[i].colition.radius, mediumAsteroids[i].colition.color);
					DrawTexturePro(mediumAsteroids[i].texture, mediumAsteroids[i].source, mediumAsteroids[i].dest, mediumAsteroids[i].origin, mediumAsteroids[i].rotation, mediumAsteroids[i].colition.color);
				}
				if (smallAsteroids[i].IsAlive)
				{
					DrawCircle(static_cast<int>(smallAsteroids[i].colition.x), static_cast<int>(smallAsteroids[i].colition.y), smallAsteroids[i].colition.radius, smallAsteroids[i].colition.color);
					DrawTexturePro(smallAsteroids[i].texture, smallAsteroids[i].source, smallAsteroids[i].dest, smallAsteroids[i].origin, smallAsteroids[i].rotation, smallAsteroids[i].colition.color);
				}

			}
		}

		void AsteroidUpdate(Asteroid bigAsteroids[]/*, Asteroid mediumAsteroids[], Asteroid smallAsteroids[]*/)
		{

			for (int i = 0; i < MAX_ASTEROIDS; i++)
			{
			CreateBigAsteroid(bigAsteroids[i]);
			}

			for (int i = 0; i < MAX_ASTEROIDS; i++)
			{
				if (bigAsteroids[i].IsAlive)
				{
					bigAsteroids[i].colition.x += bigAsteroids[i].aceleration.x * bigAsteroids[i].velocity * GetFrameTime();
					bigAsteroids[i].colition.y += bigAsteroids[i].aceleration.y * bigAsteroids[i].velocity * GetFrameTime();
				}

				if (bigAsteroids[i].colition.y < 0)
				{
					bigAsteroids[i].colition.y = GetScreenHeight() - bigAsteroids[i].colition.radius / 5;
				}
				if (bigAsteroids[i].colition.y > GetScreenHeight())
				{
					bigAsteroids[i].colition.y = bigAsteroids[i].colition.radius/5;
				}
				if (bigAsteroids[i].colition.x < 0)
				{
					bigAsteroids[i].colition.x = GetScreenWidth() + bigAsteroids[i].colition.radius / 5;
				}
				if (bigAsteroids[i].colition.x > GetScreenWidth())
				{
					bigAsteroids[i].colition.x = bigAsteroids[i].colition.radius / 5;
				}
			}
		}
	}
}