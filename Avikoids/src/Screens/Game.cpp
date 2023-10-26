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
		static void InitAsteroid(Asteroid asteroids[], Texture2D texture);

		const int TOTAL_ASTEROIDS = 60;
		Asteroid bigAsteroids[TOTAL_ASTEROIDS];
		Asteroid mediumAsteroids[TOTAL_ASTEROIDS];
		Asteroid smallAsteroids[TOTAL_ASTEROIDS];
		Spaceship player;


		void InitGame()
		{
			float scale = 0.15f;
			float WidthF = static_cast<float>(GetScreenWidth());
			float HeightF = static_cast<float>(GetScreenHeight());


			player.lives = 3;
			player.IsAlive = true;
			player.hitBox.radius = 25;
			player.hitBox.position = { WidthF / 2, HeightF / 2 };
			player.textureRec.x = WidthF / 2;
			player.textureRec.y = HeightF / 2;
			player.textureRec.height = 50;
			player.textureRec.width = 50;
			player.texture = LoadTexture("assets/PNG/player/Player.png");

			player.source = { 0,0,static_cast<float>(player.texture.width),static_cast<float>(player.texture.height) };

			player.dest = { player.hitBox.position.x,player.hitBox.position.y,static_cast<float>(player.texture.width) * scale,static_cast<float>(player.texture.height) * scale };

			player.origin = { static_cast<float>(player.source.width / 2) * scale , static_cast<float> (player.source.height / 4) * scale };

			Texture2D bigAsteroidTexture = LoadTexture("assets/PNG/Asteroids/BigAsteroid.png");
			Texture2D mediumAsteroidTexture = LoadTexture("assets/PNG/Asteroids/MediumAsteroid.png");
			Texture2D smallAsteroidTexture = LoadTexture("assets/PNG/Asteroids/SmallAsteroid.png");


			InitAsteroid(bigAsteroids, bigAsteroidTexture);
			InitAsteroid(mediumAsteroids, mediumAsteroidTexture);
			InitAsteroid(smallAsteroids, smallAsteroidTexture);


		}

		void GameUpdate()
		{
			SpaceshipUpdate(player);

			AsteroidUpdate(bigAsteroids/*, mediumAsteroids, smallAsteroids*/);

		}

		void DrawGame()
		{
			GameColitions();

			SpaceshipDraw(player);

			for (int i = 0; i < player.maxBullets; i++)
			{
				DrawBullet(player.bullets[i]);
			}

			DrawAsteroid(bigAsteroids, mediumAsteroids, smallAsteroids);

		}

		static void GameColitions()
		{
			for (int i = 0; i < TOTAL_ASTEROIDS; i++)
			{
				if (CheckCollisionCircles(player.hitBox.position, player.hitBox.radius, bigAsteroids[i].hitBox.position, bigAsteroids[i].hitBox.radius))
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
					if (CheckCollisionCircles(player.bullets[j].hitBox.position, player.bullets[j].hitBox.radius, bigAsteroids[i].hitBox.position, bigAsteroids[i].hitBox.radius))
					{
						bigAsteroids[i].IsAlive = false;
						player.bullets[j].IsActive = false;

					}
				}
			}
		}

		static void Reset()
		{
			float WidthF = static_cast<float>(GetScreenWidth());
				float HeightF = static_cast<float>(GetScreenHeight());

			player.hitBox.position = { WidthF / 2, HeightF / 2 };

			for (int i = 0; i < TOTAL_ASTEROIDS; i++)
			{
				bigAsteroids[i].hitBox.position = { NULL, NULL };
				bigAsteroids[i].IsAlive = false;
			}

		}

		static void InitAsteroid(Asteroid asteroids[], Texture2D texture)
		{
			for (int i = 0; i < TOTAL_ASTEROIDS; i++)
			{
				asteroids[i].textureBigAsteroid = texture;
			}

		}
	}
};