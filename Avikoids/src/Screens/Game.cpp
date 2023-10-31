#include "Game.h"

#include "ProjectUtilities/Utilities.h"

#include "ScreenManagements/GameScenes.h"
#include "Objects/SpaceShip.h"
#include "Objects/Bullet.h"
#include "Objects/Asteroids.h"
#include "Objects/PowerUps.h"


namespace asteroids
{
	namespace game
	{

		static void GameColitions();
		static void Reset();
		static void initSprites();
		static void RulesUpdate();
		static void LoseUpdate(Screen& currentScene);
		static void PauseButtonUpdate();
		static void PausedUpdate(Screen& currentScreen);
		static void InitGameMusic();

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
		Button showRules;
		Button NextButton;
		Button ReturnMenuButton;
		Button PlayAganButton;
		Button showPlayerHighscore;
		Button PauseButton;
		Button PurpleRec;
		Button MenuButton;
		Button RestartButton;
		Button ResumeButton;

		Music gameMusic;

		Sound AsteroidHitSound;
		Sound PlayerDeadSound;

		void InitGame()
		{
			initSprites();
			InitPlayer(player);
			InitAsteroids(bigAsteroids, mediumAsteroids, smallAsteroids);
			Reset(); 
			InitGameMusic();
			InitPowerUp();

			actualScene = GameScenes::ShowRules;
		}

		void GameUpdate(Screen& currentScene)
		{

			if (actualScene == GameScenes::Playing)
			{
				SpaceshipUpdate(player);

				AsteroidUpdate(bigAsteroids, mediumAsteroids, smallAsteroids, player);

				UpdatePowerUps(bigAsteroids, mediumAsteroids, smallAsteroids, player);

				GameColitions();

				PauseButtonUpdate();
			}
			else if (actualScene == GameScenes::ShowRules)
			{
				RulesUpdate();
			}
			else if (actualScene == GameScenes::Lose)
			{
				LoseUpdate(currentScene);
			}
			else if (actualScene == GameScenes::Paused)
			{
				PausedUpdate(currentScene);
			}

			PlayMusicStream(gameMusic);
			UpdateMusicStream(gameMusic);
		}

		void DrawGame()
		{
			
			if (actualScene == GameScenes::ShowRules)
			{
				DrawTextureEx(showRules.sprite, showRules.position, 0, showRules.scale, showRules.color);
				DrawTextureEx(NextButton.sprite, NextButton.position, 0, NextButton.scale, NextButton.color);
			}
			else if (actualScene == GameScenes::Playing)
			{
				DrawPowerUps();

				SpaceshipDraw(player);

				for (int i = 0; i < player.maxBullets; i++)
				{
					DrawBullet(player.bullets[i]);
				}

				DrawAsteroid(bigAsteroids, mediumAsteroids, smallAsteroids);

				DrawText(TextFormat("SCORE: %i", player.score), static_cast<int>(showScore.position.x), static_cast<int>(showScore.position.y), showScore.fontSize, showScore.color);
				DrawText(TextFormat("LIVES: %i", player.lives), static_cast<int>(showPlayerLife.position.x), static_cast<int>(showPlayerLife.position.y), showPlayerLife.fontSize, showPlayerLife.color);

				DrawButton(PauseButton);
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
			else if (actualScene == GameScenes::Paused)
			{
				DrawButton(PurpleRec);
				DrawButton(MenuButton);
				DrawButton(RestartButton);
				DrawButton(ResumeButton);
			
			}
		}

		static void GameColitions()
		{
			for (int i = 0; i < TOTAL_BIG_ASTEROIDS; i++)
			{
				if (CollitionCheckCircles(player.hitBox.position, player.hitBox.radius, bigAsteroids[i].hitBox.position, bigAsteroids[i].hitBox.radius) && bigAsteroids[i].IsAlive)
				{
					PlaySound(PlayerDeadSound);
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
						if (CollitionCheckCircles(player.bullets[j].hitBox.position, player.bullets[j].hitBox.radius, bigAsteroids[i].hitBox.position, bigAsteroids[i].hitBox.radius))
						{
							PlaySound(AsteroidHitSound);
							bigAsteroids[i].IsAlive = false;
							bigAsteroids[i].SpawnChild = true;
							player.bullets[j].IsActive = false;

							player.score += 25;
						}
					}
				}
			}

			for (int i = 0; i < TOTAL_MEDIUM_ASTEROIDS; i++)
			{
				if (CollitionCheckCircles(player.hitBox.position, player.hitBox.radius, mediumAsteroids[i].hitBox.position, mediumAsteroids[i].hitBox.radius) && mediumAsteroids[i].IsAlive)
				{
					PlaySound(PlayerDeadSound);
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
						if (CollitionCheckCircles(player.bullets[j].hitBox.position, player.bullets[j].hitBox.radius, mediumAsteroids[i].hitBox.position, mediumAsteroids[i].hitBox.radius))
						{
							PlaySound(AsteroidHitSound);
							mediumAsteroids[i].IsAlive = false;
							mediumAsteroids[i].SpawnChild = true;
							player.bullets[j].IsActive = false;

							player.score += 50;

						}
					}
				}
			}

			for (int i = 0; i < TOTAL_SMALL_ASTEROIDS; i++)
			{
				if (CollitionCheckCircles(player.hitBox.position, player.hitBox.radius, smallAsteroids[i].hitBox.position, smallAsteroids[i].hitBox.radius) && smallAsteroids[i].IsAlive)
				{
					PlaySound(PlayerDeadSound);
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
						if (CollitionCheckCircles(player.bullets[j].hitBox.position, player.bullets[j].hitBox.radius, smallAsteroids[i].hitBox.position, smallAsteroids[i].hitBox.radius))
						{
							PlaySound(AsteroidHitSound);
							smallAsteroids[i].IsAlive = false;
							smallAsteroids[i].SpawnChild = true;
							player.bullets[j].IsActive = false;

							player.score += 75;
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
			player.IsShotGunOn = false;

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

			showRules.position = { 140,100 };
			showRules.scale = 1;
			showRules.sprite = LoadTexture("res/PNG/Game/Rules/ShowRules.png");

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

			PauseButton.position = { 900,40 };
			PauseButton.scale = 0.3f;
			PauseButton.sprite = LoadTexture("res/PNG/Game/Pause/PauseButton.png");

			PurpleRec.position = { 340,100 };
			PurpleRec.scale = 0.8f;
			PurpleRec.sprite = LoadTexture("res/PNG/Game/Pause/PurpleRec.png");

			ResumeButton.position = { 370,250 };
			ResumeButton.scale = 0.7f;
			ResumeButton.sprite = LoadTexture("res/PNG/Game/Pause/ResumeButton.png");
			
			RestartButton.position = { 370,400 };
			RestartButton.scale = 0.7f;
			RestartButton.sprite = LoadTexture("res/PNG/Game/Pause/RestartButton.png");

			MenuButton.position = { 370,550 };
			MenuButton.scale = 0.7f;
			MenuButton.sprite = LoadTexture("res/PNG/Game/Pause/MenuButton.png");

		}

		static void RulesUpdate()
		{
			if (MouseMenuColision(NextButton))
			{
				NextButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					InitPlayer(player);
					initSprites();
					Reset();
					actualScene = GameScenes::Playing;
				}
			}
			else
			{
				NextButton.color = WHITE;
			}
		}

		static void LoseUpdate(Screen& currentScene)
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
		
		static void PauseButtonUpdate()
		{
			if (MouseMenuColision(PauseButton))
			{
				PauseButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::Paused;
				}
			}
			else
			{
				PauseButton.color = WHITE;
			}
		}

		static void PausedUpdate(Screen& currentScreen)
		{

			if (MouseMenuColision(MenuButton))
			{
				MenuButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					currentScreen = Screen::Menu;
					actualScene = GameScenes::ShowRules;
				}
			}
			else
			{
				MenuButton.color = WHITE;
			}

			if (MouseMenuColision(RestartButton))
			{
				RestartButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::ShowRules;
				}
			}
			else
			{
				RestartButton.color = WHITE;
			}


			if (MouseMenuColision(ResumeButton))
			{
				ResumeButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::Playing;
				}
			}
			else
			{
				ResumeButton.color = WHITE;
			}


		}

		static void InitGameMusic()
		{

			gameMusic = LoadMusicStream("res/MUSIC/PlayingMusic.mp3");
			SetMusicVolume(gameMusic, 0.1f);

			AsteroidHitSound = LoadSound("res/MUSIC/SoundEffects/AsteroidHitSound.mp3");
			PlayerDeadSound = LoadSound("res/MUSIC/SoundEffects/PlayerDeadSound.mp3");
			SetSoundVolume(AsteroidHitSound, 0.1f);
			SetSoundVolume(PlayerDeadSound, 0.1f);
		}
	}
};