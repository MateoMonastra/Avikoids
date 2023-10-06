#include "Menu.h"

#include "ProjectUtilities/Utilities.h"
#include "ScreenManagements/Screen.h"
#include "Game.h"

namespace asteroids
{
	namespace menu
	{
		struct Vector2i
		{
			int x = {};
			int y = {};
		
		};

		struct Button
		{
			Vector2i recPosition = {};
			int recW = {};
			int recH = {};
			Color RecColor = WHITE;

			const char* text = " ";
			Vector2i TextPosition = {};
			Color TextColor = BLACK;
			int size = {};
		};

		static Button title;
		static Button game;
		static Button exit;

		static bool MouseMenuColision(float mousex, float mousey, int recx, int recy, int recw, int rech);
		static void DrawButton(Button button);

		void InitMenu()
		{
			int middleScreen = GetScreenWidth() / 2;

			title.recPosition = { middleScreen - 180 , 20 };
			title.recW = 350;
			title.recH = 90;
			title.RecColor = BLUE;

			title.TextPosition = { middleScreen - 100, 50 };
			title.text = "VikoPong";
			title.size = 40;


			game.recPosition = { middleScreen - 325, 175 };
			game.recW = 250;
			game.recH = 90;
			game.RecColor = RED;

			game.TextPosition = { middleScreen - 320, 200 };
			game.text = "Single Mode";
			game.size = 40;

			exit.recPosition = { middleScreen - 128, 350 };
			exit.recW = 250;
			exit.recH = 90;
			exit.RecColor = YELLOW;

			exit.TextPosition = { middleScreen - 40, 375 };
			exit.text = "Exit";
			exit.size = 40;

		}

		bool MouseMenuColision(float mousex, float mousey, int recx, int recy, int recw, int rech)
		{

			if (mousex >= recx &&
				mousex <= recx + recw &&
				mousey >= recy &&
				mousey <= recy + rech)
			{
				return true;
			}
			return false;
		}

		void MenuUpdate(Screen& currentScreen)
		{
			Vector2 mousePosition = GetMousePosition();


			if (MouseMenuColision(mousePosition.x, mousePosition.y, game.recPosition.x, game.recPosition.y, game.recW, game.recH))
			{
				game.RecColor = WHITE;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					/*currentScreen = Screen::Game;
					game::InitGame(currentScreen);*/
				}
			}
			else if (MouseMenuColision(mousePosition.x, mousePosition.y, exit.recPosition.x, exit.recPosition.y, exit.recW, exit.recH))
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
			DrawRectangle(button.recPosition.x, button.recPosition.y, button.recW, button.recH, button.RecColor);
			DrawText(button.text, button.TextPosition.x, button.TextPosition.y, button.size, button.RecColor);

		}
	}
}