#include "Game.h"

#include "ProjectUtilities/Utilities.h"
#include "Objects/SpaceShip.h"
#include "Objects/Bullet.h"
#include "Objects/Asteroids.h"
#include "ScreenManagements/GameScenes.h"


namespace asteroids
{
	namespace game
	{

		static void GameColitions();
		static void Reset();
		static void initSprites();

		const int TOTAL_BIG_ASTEROIDS = 20;
		const int TOTAL_MEDIUM_ASTEROIDS = 40;
		const int TOTAL_SMALL_ASTEROIDS = 80;

		Asteroid bigAsteroids[TOTAL_BIG_ASTEROIDS];
		Asteroid mediumAsteroids[TOTAL_MEDIUM_ASTEROIDS];
		Asteroid smallAsteroids[TOTAL_SMALL_ASTEROIDS];
		Spaceship player;
		GameScenes actualScene;
		Button showScore;
		Button showPlayerLife;
		Button ShowRules;
		Button NextButton;
		Button ReturnMenuButton;
		Button PlayAganButton;
		Button showPlayerHighscore;

		void InitGame()
		{
			initSprites();
			InitPlayer(player);
			InitAsteroids(bigAsteroids, mediumAsteroids, smallAsteroids);
			Reset();

			actualScene = GameScenes::ShowRules;
		}

		void GameUpdate(Screen& currentScene)
		{
			if (actualScene == GameScenes::Playing)
			{
				SpaceshipUpdate(player);

				AsteroidUpdate(bigAsteroids, mediumAsteroids, smallAsteroids, player);

				GameColitions();
			}
			else if (actualScene == GameScenes::ShowRules)
			{
				if (MouseMenuColision(NextButton))
				{
					NextButton.color = GRAY;

					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						InitGame();
						actualScene = GameScenes::Playing;
					}
				}
				else
				{
					NextButton.color = WHITE;
				}
			}
			else if (actualScene == GameScenes::Lose)
			{
				if (MouseMenuColision(ReturnMenuButton))
				{
					ReturnMenuButton.color = GRAY;

					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						actualScene = GameScenes::ShowRules;
						currentScene = Screen::Menu;
					}
				}
				else
				{
					ReturnMenuButton.color = WHITE;
				}
				
				if (MouseMenuColision(PlayAganButton))
				{
					PlayAganButton.color = GRAY;

					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						actualScene = GameScenes::ShowRules;
					}
				}
				else
				{
					PlayAganButton.color = WHITE;
				}
			}
		}

		void DrawGame()
		{
			if (actualScene == GameScenes::ShowRules)
			{
				DrawTextureEx(ShowRules.sprite, ShowRules.position, 0, ShowRules.scale, ShowRules.color);
				DrawTextureEx(NextButton.sprite, NextButton.position, 0, NextButton.scale, NextButton.color);
			}
			else if (actualScene == GameScenes::Playing)
			{
				SpaceshipDraw(player);

				for (int i = 0; i < player.maxBullets; i++)
				{
					DrawBullet(player.bullets[i]);
				}

				DrawAsteroid(bigAsteroids, mediumAsteroids, smallAsteroids);

				DrawText(TextFormat("SCORE: %i", player.score), static_cast<int>(showScore.position.x), static_cast<int>(showScore.position.y), showScore.fontSize, showScore.color);
				DrawText(TextFormat("LIVES: %i", player.lives), static_cast<int>(showPlayerLife.position.x), static_cast<int>(showPlayerLife.position.y), showPlayerLife.fontSize, showPlayerLife.color);
			}
			else if (actualScene == GameScenes::Lose)
			{
				showScore.position = { 100, 300 };
				showScore.fontSize = 60;

				DrawText(TextFormat("HIGHSCORE: %i", player.highScore), static_cast<int>(showPlayerHighscore.position.x), static_cast<int>(showPlayerHighscore.position.y), showPlayerHighscore.fontSize, showPlayerHighscore.color);
				DrawText(TextFormat("YOUR SCORE WAS: %i", player.score), static_cast<int>(showScore.position.x), static_cast<int>(showScore.position.y), showScore.fontSize, showScore.color);
				DrawTextureEx(PlayAganButton.sprite, PlayAganButton.position, 0, PlayAganButton.scale, PlayAganButton.color);
				DrawTextureEx(ReturnMenuButton.sprite, ReturnMenuButton.position, 0, ReturnMenuButton.scale, ReturnMenuButton.color);
			}
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
						actualScene = GameScenes::Lose;
						UpdateHighScore(player);
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
						actualScene = GameScenes::Lose;
						UpdateHighScore(player);
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
						actualScene = GameScenes::Lose;
						UpdateHighScore(player);
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
			player.IsAutoShooting = false;
			player.velocity = { 0, 0 };

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

		static void initSprites()
		{
			showScore.fontSize = 40;
			showScore.position = { 30,30 };

			showPlayerLife.fontSize = 40;
			showPlayerLife.position = { 30,70 };

			ShowRules.position = { 140,100 };
			ShowRules.scale = 1;
			ShowRules.sprite = LoadTexture("res/PNG/Game/Rules/ShowRules.png");

			NextButton.position = { 600,600 };
			NextButton.scale = 0.6f;
			NextButton.sprite = LoadTexture("res/PNG/Game/Rules/NextButton.png");

			ReturnMenuButton.position = { 400,550 };
			ReturnMenuButton.scale = 0.6f;
			ReturnMenuButton.sprite = LoadTexture("res/PNG/Game/Lose/ReturnMenuButton.png");

			showPlayerHighscore.position = { 100, 150 };
			showPlayerHighscore.fontSize = 80;
			showPlayerHighscore.color = PINK;

			PlayAganButton.position = { 400,450 };
			PlayAganButton.scale = 0.6f;
			PlayAganButton.sprite = LoadTexture("res/PNG/Game/Lose/PlayAgainButton.png");

		}
	}
};