#include "Menu.h"

#include "ProjectUtilities/Utilities.h"
#include "ScreenManagements/Screen.h"
#include "Game.h"


namespace menu
{

	struct Button
	{
		Vector2 RecPosition;
		int RecW;
		int RecH;
		Color color = WHITE;

		const char* text = " ";
		Vector2 TextPosition;
		int size;
	};

	static Button title;
	static Button game;
	static Button exit;

	static bool MouseMenuColision(float mousex, float mousey, float recx, float recy, float recw, float rech);

	void InitMenu()
	{

		title.RecPosition = { (float)GetScreenWidth() / 2 - 180 , 20 };
		title.RecW = 350;
		title.RecH = 90;
		title.color = BLUE;

		title.TextPosition = { (float)GetScreenWidth() / 2 - 100, 50 };
		title.text = "VikoPong";
		title.size = 40;


		game.RecPosition = { (float)GetScreenWidth() / 2 - 325, 175 };
		game.RecW = 250;
		game.RecH = 90;
		game.color = RED;

		game.TextPosition = { (float)GetScreenWidth() / 2 - 320, 200 };
		game.text = "Single Mode";
		game.size = 40;

		exit.RecPosition = { (float)GetScreenWidth() / 2 - 128, 350 };
		exit.RecW = 250;
		exit.RecH = 90;
		exit.color = YELLOW;

		exit.TextPosition = { (float)GetScreenWidth() / 2 - 40, 375 };
		exit.text = "Exit";
		exit.size = 40;

	}

	bool MouseMenuColision(float mousex, float mousey, float recx, float recy, float recw, float rech)
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


		if (MouseMenuColision(mousePosition.x, mousePosition.y, game.RecPosition.x, game.RecPosition.y, game.RecW, game.RecH))
		{
			game.color = WHITE;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Game;
				game::InitGame(currentScreen);
			}
		}
		else if (MouseMenuColision(mousePosition.x, mousePosition.y, exit.RecPosition.x, exit.RecPosition.y, exit.RecW, exit.RecH))
		{
			exit.color = WHITE;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentScreen = Screen::Exit;
			}
		}
		else
		{
			game.color = MAROON;
			exit.color = YELLOW;
		}


	}

	void MenuDrawing()
	{
		ClearBackground(BLACK);

		DrawRectangle(title.RecPosition.x, title.RecPosition.y, title.RecW, title.RecH, title.color);
		DrawRectangle(game.RecPosition.x, game.RecPosition.y, game.RecW, game.RecH, game.color);
		DrawRectangle(exit.RecPosition.x, exit.RecPosition.y, exit.RecW, exit.RecH, exit.color);

		DrawText("VikoPong", title.TextPosition.x, title.TextPosition.y, title.size, BLACK);
		DrawText("Game", game.TextPosition.x, game.TextPosition.y, game.size, BLACK);
		DrawText("Exit", exit.TextPosition.x, exit.TextPosition.y, exit.size, BLACK);
	}

}