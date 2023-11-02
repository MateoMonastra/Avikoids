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
		static void PlayerRulesUpdate();
		static void LoseUpdate(Screen& currentScene);
		static void PauseButtonUpdate();
		static void PausedUpdate(Screen& currentScreen);
		static void InitGameMusic();
		static void AlienRulesUpdate();
		static void PowerUpRulesUpdate();
		static void ReminderUpdate();
		static void FollowingAlienRulesUpdate();

		const int TOTAL_BIG_ASTEROIDS = 25;
		const int TOTAL_MEDIUM_ASTEROIDS = 50;
		const int TOTAL_SMALL_ASTEROIDS = 100;
		const int TOTAL_FOLLOWING_ASTEROIDS = 3;

		Asteroid bigAsteroids[TOTAL_BIG_ASTEROIDS];
		Asteroid mediumAsteroids[TOTAL_MEDIUM_ASTEROIDS];
		Asteroid smallAsteroids[TOTAL_SMALL_ASTEROIDS];
		Asteroid followingAsteroids[TOTAL_FOLLOWING_ASTEROIDS];

		Spaceship player;

		GameScenes actualScene;

		Button ShowScore;
		Button ShowPlayerLife;
		Button NextButton;
		Button ReturnMenuButton;
		Button PlayAganButton;
		Button ShowPlayerHighscore;
		Button PauseButton;
		Button PurpleRec;
		Button MenuButton;
		Button RestartButton;
		Button ResumeButton;
		Button BackGround;
		Button ReturnButton;
		Button ShowPlayerRules;
		Button ShowAlienRules;
		Button ShowPowerUpRules;
		Button ShowReminder;
		Button ShowFollowingAlienRules;

		Music gameMusic;

		Sound AsteroidHitSound;
		Sound PlayerDeadSound;

		Font TextFont;

		void InitGame()
		{
			initSprites();
			InitPlayer(player);
			InitAsteroids(bigAsteroids, mediumAsteroids, smallAsteroids, followingAsteroids);
			Reset();
			InitGameMusic();
			InitPowerUp();

			actualScene = GameScenes::ShowPlayerRules;
		}

		void GameUpdate(Screen& currentScene)
		{

			if (actualScene == GameScenes::Playing)
			{
				GameColitions();

				SpaceshipUpdate(player);

				AsteroidUpdate(bigAsteroids, mediumAsteroids, smallAsteroids, player, followingAsteroids);

				UpdatePowerUps(bigAsteroids, mediumAsteroids, smallAsteroids, player, followingAsteroids);

				PauseButtonUpdate();
			}
			else if (actualScene == GameScenes::ShowPlayerRules)
			{
				PlayerRulesUpdate();
			}
			else if (actualScene == GameScenes::ShowReminder)
			{
				ReminderUpdate();
			}
			else if (actualScene == GameScenes::ShowAlienRules)
			{
				AlienRulesUpdate();
			}
			else if (actualScene == GameScenes::ShowFollowingAlienRules)
			{
				FollowingAlienRulesUpdate();
			}
			else if (actualScene == GameScenes::ShowPowerUpsRules)
			{
				PowerUpRulesUpdate();
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
			DrawButton(BackGround);

			if (actualScene == GameScenes::ShowPlayerRules)
			{
				DrawButton(ShowPlayerRules);
				DrawButton(NextButton);
			}
			else if (actualScene == GameScenes::ShowReminder)
			{
				DrawButton(ShowReminder);
				DrawButton(NextButton);
				DrawButton(ReturnButton);
			}
			else if (actualScene == GameScenes::ShowAlienRules)
			{
				DrawButton(ShowAlienRules);
				DrawButton(NextButton);
				DrawButton(ReturnButton);
			}
			else if (actualScene == GameScenes::ShowFollowingAlienRules)
			{
				DrawButton(ShowFollowingAlienRules);
				DrawButton(NextButton);
				DrawButton(ReturnButton);
			}
			else if (actualScene == GameScenes::ShowPowerUpsRules)
			{
				DrawButton(ShowPowerUpRules);
				DrawButton(NextButton);
				DrawButton(ReturnButton);
			}
			else if (actualScene == GameScenes::Playing)
			{
				DrawPowerUps();


				for (int i = 0; i < player.maxBullets; i++)
				{
					DrawBullet(player.bullets[i]);
				}

				DrawAsteroid(bigAsteroids, mediumAsteroids, smallAsteroids, followingAsteroids);

				SpaceshipDraw(player);
				
				DrawTextEx(TextFont,TextFormat("SCORE: %i", player.score), ShowScore.position, ShowScore.fontSize,0, ShowScore.color);
				DrawTextEx(TextFont,TextFormat("LIVES: %i", player.lives), ShowPlayerLife.position, ShowPlayerLife.fontSize,0, ShowPlayerLife.color);

				DrawButton(PauseButton);
			}
			else if (actualScene == GameScenes::Lose)
			{
				ShowScore.position = { 100, 300 };
				ShowScore.fontSize = 60;
				float ShowPlayerHighscoreX = ShowPlayerHighscore.position.x + 10;

				DrawTextEx(TextFont, TextFormat("HIGHSCORE: %i", player.highScore), { ShowPlayerHighscoreX,ShowPlayerHighscore.position.y }, ShowPlayerHighscore.fontSize, 0, BLACK);
				DrawTextEx(TextFont,TextFormat("HIGHSCORE: %i", player.highScore), ShowPlayerHighscore.position, ShowPlayerHighscore.fontSize,0, ShowPlayerHighscore.color);
				DrawTextEx(TextFont,TextFormat("YOUR SCORE WAS: %i", player.score),ShowScore.position, ShowScore.fontSize,0, ShowScore.color);
				DrawButton(PlayAganButton);
				DrawButton(ReturnMenuButton);
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

			for (int i = 0; i < TOTAL_FOLLOWING_ASTEROIDS; i++)
			{
				if (CollitionCheckCircles(player.hitBox.position, player.hitBox.radius, followingAsteroids[i].hitBox.position, followingAsteroids[i].hitBox.radius) && followingAsteroids[i].IsAlive)
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
					if (player.bullets[j].IsActive && followingAsteroids[i].IsAlive)
					{
						if (CollitionCheckCircles(player.bullets[j].hitBox.position, player.bullets[j].hitBox.radius, followingAsteroids[i].hitBox.position, followingAsteroids[i].hitBox.radius))
						{
							PlaySound(AsteroidHitSound);
							followingAsteroids[i].IsAlive = false;
							followingAsteroids[i].SpawnChild = true;
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

			for (int i = 0; i < TOTAL_FOLLOWING_ASTEROIDS; i++)
			{
				followingAsteroids[i].IsAlive = false;
			}

		}

		static void initSprites()
		{
			ShowScore.fontSize = 40;
			ShowScore.position = { 30,30 };
			ShowScore.color = BLACK;

			ShowPlayerLife.fontSize = 40;
			ShowPlayerLife.position = { 30,70 };
			ShowPlayerLife.color = BLACK;

			NextButton.position = { 600,600 };
			NextButton.scale = 0.6f;
			NextButton.sprite = LoadTexture("res/PNG/Game/Rules/NextButton.png");

			ReturnMenuButton.position = { 400,550 };
			ReturnMenuButton.scale = 0.6f;
			ReturnMenuButton.sprite = LoadTexture("res/PNG/Game/Lose/ReturnMenuButton.png");

			ShowPlayerHighscore.position = { 100, 150 };
			ShowPlayerHighscore.fontSize = 100;
			ShowPlayerHighscore.color = MAROON;

			PlayAganButton.position = { 400,450 };
			PlayAganButton.scale = 0.6f;
			PlayAganButton.sprite = LoadTexture("res/PNG/Game/Lose/PlayAgainButton.png");

			PauseButton.position = { 900,40 };
			PauseButton.scale = 0.3f;
			PauseButton.sprite = LoadTexture("res/PNG/Game/Pause/PauseButton.png");

			PurpleRec.position = { 340,100 };
			PurpleRec.scale = 0.8f;
			PurpleRec.sprite = LoadTexture("res/PNG/Game/Pause/PurpleRecPause.png");

			ResumeButton.position = { 370,250 };
			ResumeButton.scale = 0.7f;
			ResumeButton.sprite = LoadTexture("res/PNG/Game/Pause/ResumeButton.png");

			RestartButton.position = { 370,400 };
			RestartButton.scale = 0.7f;
			RestartButton.sprite = LoadTexture("res/PNG/Game/Pause/RestartButton.png");

			MenuButton.position = { 370,550 };
			MenuButton.scale = 0.7f;
			MenuButton.sprite = LoadTexture("res/PNG/Game/Pause/MenuButton.png");

			BackGround.position = { 0,0 };
			BackGround.scale = 1;
			BackGround.sprite = LoadTexture("res/PNG/Game/GameBackGround.png");

			ReturnButton.position = { 200,600 };
			ReturnButton.scale = 0.6f;
			ReturnButton.sprite = LoadTexture("res/PNG/Game/Rules/BackButton.png");

			ShowPlayerRules.position = { 140,100 };
			ShowPlayerRules.scale = 1;
			ShowPlayerRules.sprite = LoadTexture("res/PNG/Game/Rules/ShowRules.png");

			ShowAlienRules.position = { 140,100 };
			ShowAlienRules.scale = 1;
			ShowAlienRules.sprite = LoadTexture("res/PNG/Game/Rules/ShowAlienRules.png");

			ShowPowerUpRules.position = { 140,100 };
			ShowPowerUpRules.scale = 1;
			ShowPowerUpRules.sprite = LoadTexture("res/PNG/Game/Rules/ShowPowerUpRules.png");

			ShowReminder.position = { 140,100 };
			ShowReminder.scale = 1;
			ShowReminder.sprite = LoadTexture("res/PNG/Game/Rules/ShowReminder.png");

			ShowFollowingAlienRules.position = { 140,100 };
			ShowFollowingAlienRules.scale = 1;
			ShowFollowingAlienRules.sprite = LoadTexture("res/PNG/Game/Rules/FollowingAlienRules.png");


			TextFont = LoadFont("res/Orbitron.ttf");
		}

		static void PlayerRulesUpdate()
		{
			if (MouseMenuColision(NextButton))
			{
				NextButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::ShowReminder;
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
					ShowScore.fontSize = 40;
					ShowScore.position = { 30,30 };

					actualScene = GameScenes::ShowPlayerRules;
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
					ShowScore.fontSize = 40;
					ShowScore.position = { 30,30 };

					actualScene = GameScenes::ShowPlayerRules;
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

			if (IsKeyPressed(KEY_ESCAPE))
			{
				actualScene = GameScenes::Paused;
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
					actualScene = GameScenes::ShowPlayerRules;
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
					actualScene = GameScenes::ShowPlayerRules;
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

		static void AlienRulesUpdate()
		{
			if (MouseMenuColision(NextButton))
			{
				NextButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::ShowFollowingAlienRules;
				}
			}
			else
			{
				NextButton.color = WHITE;
			}

			if (MouseMenuColision(ReturnButton))
			{
				ReturnButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::ShowReminder;
				}
			}
			else
			{
				ReturnButton.color = WHITE;
			}


		}

		static void PowerUpRulesUpdate()
		{
			if (MouseMenuColision(NextButton))
			{
				NextButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					InitPlayer(player);
					Reset();
					actualScene = GameScenes::Playing;
				}
			}
			else
			{
				NextButton.color = WHITE;
			}

			if (MouseMenuColision(ReturnButton))
			{
				ReturnButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::ShowFollowingAlienRules;
				}
			}
			else
			{
				ReturnButton.color = WHITE;
			}
		}

		static void ReminderUpdate()
		{
			if (MouseMenuColision(NextButton))
			{
				NextButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::ShowAlienRules;
				}
			}
			else
			{
				NextButton.color = WHITE;
			}

			if (MouseMenuColision(ReturnButton))
			{
				ReturnButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::ShowPlayerRules;
				}
			}
			else
			{
				ReturnButton.color = WHITE;
			}
		
		
		}

		static void FollowingAlienRulesUpdate()
		{
			if (MouseMenuColision(NextButton))
			{
				NextButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::ShowPowerUpsRules;
				}
			}
			else
			{
				NextButton.color = WHITE;
			}

			if (MouseMenuColision(ReturnButton))
			{
				ReturnButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					actualScene = GameScenes::ShowAlienRules;
				}
			}
			else
			{
				ReturnButton.color = WHITE;
			}
		
		}
	}
};