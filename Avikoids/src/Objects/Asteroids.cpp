#include "Asteroids.h"


namespace asteroids
{
	namespace game
	{

		static void CreateBigAsteroid(Asteroid& asteroid);
		static void CreateMediumAsteroid(Asteroid& asteroid, Asteroid bigAsteroid);
		static void CreateSmallAsteroid(Asteroid& asteroid, Asteroid mediumAsteroid);
		static void CreateFollowingAsteroid(Asteroid& asteroid);

		const int TOTAL_BIG_ASTEROIDS = 25;
		const int TOTAL_MEDIUM_ASTEROIDS = 50;
		const int TOTAL_SMALL_ASTEROIDS = 100;
		const int TOTAL_FOLLOWING_ASTEROIDS = 3;

		const int FIRST_PHASE = 3000;
		const int SECOND_PHASE = 8000;

		int maxFollowingAsteroidSpawn = 1;

		double timerBigAsteroidSpawn = 0;
		double timerFollowingAsteroidSpawn = 0;


		void InitAsteroids(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[], Asteroid followingAsteroids[])
		{
			Texture2D bigAsteroidTexture = LoadTexture("res/PNG/Game/Play/Asteroids/BigAsteroid.png");
			Texture2D mediumAsteroidTexture = LoadTexture("res/PNG/Game/Play/Asteroids/MediumAsteroid.png");
			Texture2D smallAsteroidTexture = LoadTexture("res/PNG/Game/Play/Asteroids/SmallAsteroid.png");
			Texture2D followingAsteroidTexture = LoadTexture("res/PNG/Game/Play/Asteroids/FollowingAsteroid.png");

			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				bigAsteroid[i].texture = bigAsteroidTexture;
			}
			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				mediumAsteroid[i].texture = mediumAsteroidTexture;
			}
			for (int i = 0; i < TOTAL_SMALL_ASTEROIDS; i++)
			{
				smallAsteroid[i].texture = smallAsteroidTexture;
			}
			for (int i = 0; i < TOTAL_FOLLOWING_ASTEROIDS; i++)
			{
				followingAsteroids[i].texture = followingAsteroidTexture;
			}

			timerBigAsteroidSpawn = GetTime();
			timerFollowingAsteroidSpawn = GetTime();
		}

		void DrawAsteroid(Asteroid bigAsteroids[], Asteroid mediumAsteroids[], Asteroid smallAsteroids[], Asteroid followingAsteroids[])
		{
			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				if (bigAsteroids[i].IsAlive)
				{
					DrawTexturePro(bigAsteroids[i].texture, bigAsteroids[i].source, bigAsteroids[i].dest, bigAsteroids[i].origin, bigAsteroids[i].rotation, bigAsteroids[i].hitBox.color);
				}
			}
			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				if (mediumAsteroids[i].IsAlive)
				{
					DrawTexturePro(mediumAsteroids[i].texture, mediumAsteroids[i].source, mediumAsteroids[i].dest, mediumAsteroids[i].origin, mediumAsteroids[i].rotation, mediumAsteroids[i].hitBox.color);
				}
			}

			for (int i = 0; i < TOTAL_SMALL_ASTEROIDS; i++)
			{
				if (smallAsteroids[i].IsAlive)
				{
					DrawTexturePro(smallAsteroids[i].texture, smallAsteroids[i].source, smallAsteroids[i].dest, smallAsteroids[i].origin, smallAsteroids[i].rotation, smallAsteroids[i].hitBox.color);
				}
			}

			for (int i = 0; i < TOTAL_FOLLOWING_ASTEROIDS; i++)
			{
				if (followingAsteroids[i].IsAlive)
				{
					DrawTexturePro(followingAsteroids[i].texture, followingAsteroids[i].source, followingAsteroids[i].dest, followingAsteroids[i].origin, followingAsteroids[i].rotation, followingAsteroids[i].hitBox.color);
				}
			}

		}

		void AsteroidUpdate(Asteroid bigAsteroid[], Asteroid mediumAsteroid[], Asteroid smallAsteroid[], Spaceship player, Asteroid followingAsteroid[])
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


					if (bigAsteroid[i].hitBox.position.y - bigAsteroid[i].hitBox.radius / 2 < 0)
					{
						bigAsteroid[i].hitBox.position.y = GetScreenHeight() - bigAsteroid[i].hitBox.radius;
					}
					if (bigAsteroid[i].hitBox.position.y + bigAsteroid[i].hitBox.radius / 2 > GetScreenHeight())
					{
						bigAsteroid[i].hitBox.position.y = bigAsteroid[i].hitBox.radius;
					}
					if (bigAsteroid[i].hitBox.position.x - bigAsteroid[i].hitBox.radius / 2 < 0)
					{
						bigAsteroid[i].hitBox.position.x = GetScreenWidth() - bigAsteroid[i].hitBox.radius;
					}
					if (bigAsteroid[i].hitBox.position.x + bigAsteroid[i].hitBox.radius / 2 > GetScreenWidth())
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

				if (GetTime() - timerBigAsteroidSpawn > bigAsteroid[i].BIG_ASTEROID_SPAWN_RECOIL && !bigAsteroid[i].IsAlive)
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


					if (mediumAsteroid[i].hitBox.position.y - mediumAsteroid[i].hitBox.radius / 2 < 0)
					{
						mediumAsteroid[i].hitBox.position.y = GetScreenHeight() - mediumAsteroid[i].hitBox.radius;
					}
					if (mediumAsteroid[i].hitBox.position.y + mediumAsteroid[i].hitBox.radius / 2 > GetScreenHeight())
					{
						mediumAsteroid[i].hitBox.position.y = mediumAsteroid[i].hitBox.radius;
					}
					if (mediumAsteroid[i].hitBox.position.x - mediumAsteroid[i].hitBox.radius / 2 < 0)
					{
						mediumAsteroid[i].hitBox.position.x = GetScreenWidth() - mediumAsteroid[i].hitBox.radius;
					}
					if (mediumAsteroid[i].hitBox.position.x + mediumAsteroid[i].hitBox.radius / 2 > GetScreenWidth())
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


					if (smallAsteroid[i].hitBox.position.y - smallAsteroid[i].hitBox.radius / 2 < 0)
					{
						smallAsteroid[i].hitBox.position.y = GetScreenHeight() - smallAsteroid[i].hitBox.radius;
					}
					if (smallAsteroid[i].hitBox.position.y + smallAsteroid[i].hitBox.radius / 2 > GetScreenHeight())
					{
						smallAsteroid[i].hitBox.position.y = smallAsteroid[i].hitBox.radius;
					}
					if (smallAsteroid[i].hitBox.position.x - smallAsteroid[i].hitBox.radius / 2 < 0)
					{
						smallAsteroid[i].hitBox.position.x = GetScreenWidth() - smallAsteroid[i].hitBox.radius;
					}
					if (smallAsteroid[i].hitBox.position.x + smallAsteroid[i].hitBox.radius / 2 > GetScreenWidth())
					{
						smallAsteroid[i].hitBox.position.x = smallAsteroid[i].hitBox.radius;
					}
				}
			}

			for (int i = 0; i < TOTAL_FOLLOWING_ASTEROIDS; i++)
			{
				int followingAsteroidsCount = 0;

				for (int j = 0; j < TOTAL_FOLLOWING_ASTEROIDS; j++)
				{
					if (followingAsteroid[j].IsAlive)
					{
						followingAsteroidsCount++;
					}
				}

				if (followingAsteroid[i].IsAlive)
				{

					if (followingAsteroid[i].hitBox.position.y - followingAsteroid[i].hitBox.radius / 2 < 0)
					{
						followingAsteroid[i].hitBox.position.y = GetScreenHeight() - followingAsteroid[i].hitBox.radius;
						followingAsteroid[i].aceleration = { 0,0 };
					}
					if (followingAsteroid[i].hitBox.position.y + followingAsteroid[i].hitBox.radius / 2 > GetScreenHeight())
					{
						followingAsteroid[i].hitBox.position.y = followingAsteroid[i].hitBox.radius;
						followingAsteroid[i].aceleration = { 0,0 };
					}
					if (followingAsteroid[i].hitBox.position.x - followingAsteroid[i].hitBox.radius / 2 < 0)
					{
						followingAsteroid[i].hitBox.position.x = GetScreenWidth() - followingAsteroid[i].hitBox.radius;
						followingAsteroid[i].aceleration = { 0,0 };
					}
					if (followingAsteroid[i].hitBox.position.x + followingAsteroid[i].hitBox.radius / 2 > GetScreenWidth())
					{
						followingAsteroid[i].hitBox.position.x = followingAsteroid[i].hitBox.radius;
						followingAsteroid[i].aceleration = { 0,0 };
					}


					Vector2 direction = Vector2Subtract(followingAsteroid[i].hitBox.position, player.hitBox.position);

					double angle = atan2(static_cast<double>(direction.y), static_cast<double>(direction.x)) * RAD2DEG + 90;

					followingAsteroid[i].rotation = static_cast<float>(angle);

					followingAsteroid[i].source = { 0,0,static_cast<float>(followingAsteroid[i].texture.width),static_cast<float>(followingAsteroid[i].texture.height) };
					followingAsteroid[i].dest = { followingAsteroid[i].hitBox.position.x,followingAsteroid[i].hitBox.position.y,static_cast<float>(followingAsteroid[i].texture.width) * followingAsteroid[i].SCALE,static_cast<float>(followingAsteroid[i].texture.height) * followingAsteroid[i].SCALE };
					followingAsteroid[i].origin = { static_cast<float>(followingAsteroid[i].source.width / 2) * followingAsteroid[i].SCALE, static_cast<float> (followingAsteroid[i].source.height / 2) * followingAsteroid[i].SCALE };

					float followingAsteroidMaxVelocity = -0.5f;

					if (followingAsteroid[i].velocity > followingAsteroidMaxVelocity)
					{
						followingAsteroid[i].velocity = -0.5f;
					}

					followingAsteroid[i].aceleration = Vector2Add(followingAsteroid[i].aceleration, Vector2Scale(direction, followingAsteroid[i].velocity * GetFrameTime()));

					followingAsteroid[i].hitBox.position.x -= followingAsteroid[i].aceleration.x * followingAsteroid[i].velocity * GetFrameTime();
					followingAsteroid[i].hitBox.position.y -= followingAsteroid[i].aceleration.y * followingAsteroid[i].velocity * GetFrameTime();
				}
				else if (GetTime() - timerFollowingAsteroidSpawn > followingAsteroid[i].FOLLOWING_ASTEROID_SPAWN_RECOIL && !followingAsteroid[i].IsAlive && followingAsteroidsCount < maxFollowingAsteroidSpawn)
				{
					CreateFollowingAsteroid(followingAsteroid[i]);
					timerFollowingAsteroidSpawn = GetTime();
				}

				if (player.score > FIRST_PHASE && maxFollowingAsteroidSpawn == 1)
				{
					maxFollowingAsteroidSpawn++;
				}
				else if (player.score > SECOND_PHASE && maxFollowingAsteroidSpawn == 2)
				{
					maxFollowingAsteroidSpawn++;
				}

			}



		}

		static void CreateBigAsteroid(Asteroid& asteroid)
		{
			float width = static_cast<float>(GetScreenWidth());
			float height = static_cast<float>(GetScreenHeight());
			int randomSpawn = GetRandomValue(1, 4);


			if (randomSpawn == 1)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(50, 55)) };
				asteroid.hitBox.position = { width,static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 60 };
				asteroid.aceleration = { RandomDirection(-1,-100),RandomDirection(-100,100) };
				asteroid.IsAlive = true;
				asteroid.SpawnChild = false;
				asteroid.SCALE = asteroid.hitBox.radius / 180;
			}
			else if (randomSpawn == 2)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(50, 55)) };
				asteroid.hitBox.position = { 40, static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 60 };
				asteroid.aceleration = { RandomDirection(1,100),RandomDirection(-100,100) };
				asteroid.IsAlive = true;
				asteroid.SpawnChild = false;
				asteroid.SCALE = asteroid.hitBox.radius / 180;
			}
			else if (randomSpawn == 3)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(50, 55)) };
				asteroid.hitBox.position = { static_cast<float>(GetRandomValue(100, 700)), 40 };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 60 };
				asteroid.aceleration = { RandomDirection(1,100),RandomDirection(-1,-100) };
				asteroid.IsAlive = true;
				asteroid.SpawnChild = false;
				asteroid.SCALE = asteroid.hitBox.radius / 180;
			}
			else if (randomSpawn == 4)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(50, 55)) };
				asteroid.hitBox.position = { static_cast<float>(GetRandomValue(100, 1000)), height };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { 60 };
				asteroid.aceleration = { RandomDirection(-100,100),RandomDirection(1,100) };
				asteroid.IsAlive = true;
				asteroid.SpawnChild = false;
				asteroid.SCALE = asteroid.hitBox.radius / 180;
			}



		}

		static void CreateMediumAsteroid(Asteroid& asteroid, Asteroid bigAsteroid)
		{

			asteroid.hitBox.radius = { bigAsteroid.hitBox.radius / 2 };
			asteroid.hitBox.position = bigAsteroid.hitBox.position;
			asteroid.aceleration = { RandomDirection(-100,100), RandomDirection(-100,100) };
			asteroid.velocity = { 70 };
			asteroid.hitBox.color = WHITE;
			asteroid.IsAlive = true;
			asteroid.SpawnChild = false;
			asteroid.SCALE = asteroid.hitBox.radius / 140;
		}

		static void CreateSmallAsteroid(Asteroid& asteroid, Asteroid mediumAsteroid)
		{
			asteroid.hitBox.radius = { mediumAsteroid.hitBox.radius / 2 };
			asteroid.hitBox.position = mediumAsteroid.hitBox.position;
			asteroid.aceleration = { RandomDirection(-100,100), RandomDirection(-100,100) };
			asteroid.velocity = { 80 };
			asteroid.hitBox.color = WHITE;
			asteroid.IsAlive = true;
			asteroid.SCALE = asteroid.hitBox.radius / 150;
		}

		static void CreateFollowingAsteroid(Asteroid& asteroid)
		{
			float width = static_cast<float>(GetScreenWidth());
			float height = static_cast<float>(GetScreenHeight());
			int randomSpawn = GetRandomValue(1, 4);


			if (randomSpawn == 1)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(25, 30)) };
				asteroid.hitBox.position = { width,static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { -0.5f };
				asteroid.IsAlive = true;
				asteroid.SCALE = asteroid.hitBox.radius / 150;
			}
			else if (randomSpawn == 2)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(25, 30)) };
				asteroid.hitBox.position = { 40, static_cast<float>(GetRandomValue(100, 1000)) };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { -0.5f };
				asteroid.IsAlive = true;
				asteroid.SCALE = asteroid.hitBox.radius / 200;
			}
			else if (randomSpawn == 3)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(25, 30)) };
				asteroid.hitBox.position = { static_cast<float>(GetRandomValue(100, 700)), 40 };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { -0.5f };
				asteroid.IsAlive = true;
				asteroid.SCALE = asteroid.hitBox.radius / 200;
			}
			else if (randomSpawn == 4)
			{
				asteroid.hitBox.radius = { static_cast<float>(GetRandomValue(25, 30)) };
				asteroid.hitBox.position = { static_cast<float>(GetRandomValue(100, 1000)), height };
				asteroid.hitBox.color = WHITE;
				asteroid.velocity = { -0.5f };
				asteroid.IsAlive = true;
				asteroid.SCALE = asteroid.hitBox.radius / 220;
			}
		}

	}
}
