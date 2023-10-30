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

		static void DrawButton(Button button);

		void InitMenu()
		{
			float middleScreenf = static_cast<float>(GetScreenWidth() / 2);

			title.position = { middleScreenf - 360 , 40 };
			title.sprite = LoadTexture("res/PNG/Menu/Header.png");
			title.scale = 0.7f;

			game.position = { middleScreenf - 118 , 380 };
			game.sprite = LoadTexture("res/PNG/Menu/PlayButton.png");
			game.scale = 0.6f;

			credits.position = { middleScreenf - 118, 470 };
			credits.sprite = LoadTexture("res/PNG/Menu/CreditsButton.png");
			credits.scale = 0.6f;
			
			exit.position = { middleScreenf - 118, 560 };
			exit.sprite = LoadTexture("res/PNG/Menu/ExitButton.png");
			exit.scale = 0.6f;

		}

		void MenuUpdate(Screen& currentScreen)
		{
			if (MouseMenuColision( game))
			{
				game.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
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
					currentScreen = Screen::Credits;
					credits::InitCredits();
				}
			}
			else
			{
				credits.color = WHITE;
			}


		}

		void MenuDrawing()
		{
			ClearBackground(BLACK);

			DrawButton(title);
			DrawButton(game);
			DrawButton(exit);
			DrawButton(credits);
		}

		static void DrawButton(Button button)
		{
			DrawTextureEx(button.sprite,button.position,0,button.scale,button.color);
		}
	}
}