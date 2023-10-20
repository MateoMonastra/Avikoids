#include "Menu.h"

#include "ProjectUtilities/Utilities.h"
#include "ScreenManagements/Screen.h"
#include "Game.h"

namespace asteroids
{
	namespace menu
	{

		struct Button
		{
			Vector2i recPosition_i = {};
			Vector2 recPosition_f = {};
			int recW = {};
			int recH = {};
			Color RecColor = WHITE;

			const char* text = " ";
			Vector2i TextPosition_i = {};
			Vector2 TextPosition_f = {};
			Color TextColor = BLACK;
			int size = {};
		};

		static Button title;
		static Button game;
		static Button exit;

		static bool MouseMenuColision(float mousex, float mousey, Button recPos);
		static void DrawButton(Button button);

		void InitMenu()
		{
			float middleScreenf = static_cast<float>(GetScreenWidth() / 2);
			int middleScreeni = GetScreenWidth() / 2;

			title.recPosition_i = { middleScreeni - 180 , 20 };
			title.recPosition_f = { middleScreenf - 180 , 20 };
			title.recW = 350;
			title.recH = 90;
			title.RecColor = BLUE;

			title.TextPosition_i = { middleScreeni - 100, 50 };
			title.TextPosition_f = { middleScreenf - 100, 50 };
			title.text = "Avikoids";
			title.size = 40;


			game.recPosition_i = { middleScreeni - 128, 175 };
			game.recPosition_f = { middleScreenf - 128 , 175 };
			game.recW = 250;
			game.recH = 90;
			game.RecColor = RED;

			game.TextPosition_i = { middleScreeni - 40, 200 };
			game.TextPosition_f = { middleScreenf - 40, 200 };
			game.text = "Play";
			game.size = 40;

			exit.recPosition_i = { middleScreeni - 128, 350 };
			exit.recPosition_f = { middleScreenf - 128, 350 };
			exit.recW = 250;
			exit.recH = 90;
			exit.RecColor = YELLOW;

			exit.TextPosition_i = { middleScreeni - 40, 375 };
			exit.TextPosition_f = { middleScreenf - 40, 375 };
			exit.text = "Exit";
			exit.size = 40;

		}

		bool MouseMenuColision(float mousex, float mousey, Button rec)
		{

			if (mousex >= rec.recPosition_f.x &&
				mousex <= rec.recPosition_f.x + rec.recW &&
				mousey >= rec.recPosition_f.y &&
				mousey <= rec.recPosition_f.y + rec.recH)
			{
				return true;
			}
			return false;
		}

		void MenuUpdate(Screen& currentScreen)
		{
			Vector2 mousePosition = GetMousePosition();


			if (MouseMenuColision(mousePosition.x, mousePosition.y, game))
			{
				game.RecColor = WHITE;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					currentScreen = Screen::Game;
					game::InitGame();
				}
			}
			else if (MouseMenuColision(mousePosition.x, mousePosition.y, exit))
			{
				exit.RecColor = WHITE;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					currentScreen = Screen::Exit;
				}
			}
			else
			{
				game.RecColor = MAROON;
				exit.RecColor = YELLOW;
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
			DrawRectangle(button.recPosition_i.x, button.recPosition_i.y, button.recW, button.recH, button.RecColor);
			DrawText(button.text, button.TextPosition_i.x, button.TextPosition_i.y, button.size, button.TextColor);

		}
	}
}