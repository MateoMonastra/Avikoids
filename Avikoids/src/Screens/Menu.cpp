#include "Menu.h"

#include "ProjectUtilities/Utilities.h"
#include "ScreenManagements/Screen.h"
#include "Game.h"


namespace asteroids
{
	namespace menu
	{
		static Button title;
		static Button game;
		static Button exit;

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

			exit.position = { middleScreenf - 118, 550 };
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
			else if (MouseMenuColision(exit))
			{
				exit.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					currentScreen = Screen::Exit;
				}
			}
			else
			{
				game.color = WHITE;
				exit.color = WHITE;
			}


		}

		void MenuDrawing()
		{
			ClearBackground(BLACK);

			DrawButton(title);
			DrawButton(game);
			DrawButton(exit);
		}

		static void DrawButton(Button button)
		{
			DrawTextureEx(button.sprite,button.position,0,button.scale,button.color);
		}
	}
}