#include "Menu.h"

#include "ProjectUtilities/Utilities.h"

#include "ScreenManagements/Screen.h"
#include "Game.h"
#include "Credits.h"


namespace asteroids
{
	namespace menu
	{
		static Button title;
		static Button game;
		static Button exit;
		static Button credits;
		static Button backGround;

		Music menuMusic;
		Sound menuTouchSFX;

		void InitMenu()
		{
			float middleScreenf = static_cast<float>(GetScreenWidth() / 2);

			title.position = { 20 , 80 };
			title.sprite = LoadTexture("res/PNG/Menu/Title.png");
			title.scale = 1.2f;

			game.position = { middleScreenf - 118 , 330 };
			game.sprite = LoadTexture("res/PNG/Menu/PlayButton.png");
			game.scale = 0.6f;

			credits.position = { middleScreenf - 118, 420 };
			credits.sprite = LoadTexture("res/PNG/Menu/CreditsButton.png");
			credits.scale = 0.6f;
			
			exit.position = { middleScreenf - 118, 510 };
			exit.sprite = LoadTexture("res/PNG/Menu/ExitButton.png");
			exit.scale = 0.6f;

			backGround.position = {0,0};
			backGround.sprite = LoadTexture("res/PNG/Menu/MenuBackground.png");
			backGround.scale = 1;

			menuMusic = LoadMusicStream("res/MUSIC/MenuMusic.mp3");
			menuTouchSFX = LoadSound("res/MUSIC/SoundEffects/MenuClickSound.wav");
			
		}

		void MenuUpdate(Screen& currentScreen)
		{
			PlayMusicStream(menuMusic);
			SetMusicVolume(menuMusic, 0.2f);
			UpdateMusicStream(menuMusic);

			if (MouseMenuColision( game))
			{
				game.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					PlaySound(menuTouchSFX);
					StopMusicStream(menuMusic);
					currentScreen = Screen::Game;
					game::InitGame();
				}
			}
			else
			{
				game.color = WHITE;
			}

			if (MouseMenuColision(exit))
			{
				exit.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					PlaySound(menuTouchSFX);
					currentScreen = Screen::Exit;
				}
			}
			else
			{
				exit.color = WHITE;
			}
			
			if (MouseMenuColision(credits))
			{
				credits.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					PlaySound(menuTouchSFX);
					currentScreen = Screen::Credits;
					credits::InitCredits(menuMusic, menuTouchSFX);
				}
			}
			else
			{
				credits.color = WHITE;
			}
		}

		void MenuDrawing()
		{
			DrawButton(backGround);
			DrawButton(title);
			DrawButton(game);
			DrawButton(exit);
			DrawButton(credits);
		}

	}
}