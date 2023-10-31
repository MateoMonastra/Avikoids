#include "Credits.h"

#include "ProjectUtilities/Utilities.h"


namespace asteroids
{
	namespace credits
	{
		Button ShowCredits;
		Button ReturnMenuButton;



		void InitCredits()
		{
			ShowCredits.position = { 140,100 };
			ShowCredits.scale = 1;
			ShowCredits.sprite = LoadTexture("res/PNG/Credits/ShowCredits.png");

			ReturnMenuButton.position = { 400,550 };
			ReturnMenuButton.scale = 0.6f;
			ReturnMenuButton.sprite = LoadTexture("res/PNG/Credits/ReturnMenuButton.png");

		}

		void CreditsUpdate(Screen& currentScene)
		{
			if (MouseMenuColision(ReturnMenuButton))
			{
				ReturnMenuButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					currentScene = Screen::Menu;
				}
			}
			else
			{
				ReturnMenuButton.color = WHITE;
			}

		}

		void CreditsDrawing()
		{
			DrawTextureEx(ShowCredits.sprite, ShowCredits.position, 0, ShowCredits.scale, ShowCredits.color);
			DrawTextureEx(ReturnMenuButton.sprite, ReturnMenuButton.position, 0, ReturnMenuButton.scale, ReturnMenuButton.color);
		}
	}
}