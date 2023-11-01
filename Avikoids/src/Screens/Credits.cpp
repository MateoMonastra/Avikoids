#include "Credits.h"


namespace asteroids
{
	namespace credits
	{
		Button ShowCredits;
		Button BackGround;
		Button ReturnMenuButton;
		Music music;
		Sound sound;


		void InitCredits(Music& menuMusic, Sound menuTouchSFX)
		{
			ShowCredits.position = { 140,100 };
			ShowCredits.scale = 1;
			ShowCredits.sprite = LoadTexture("res/PNG/Credits/ShowCredits.png");

			ReturnMenuButton.position = { 400,550 };
			ReturnMenuButton.scale = 0.6f;
			ReturnMenuButton.sprite = LoadTexture("res/PNG/Credits/ReturnMenuButton.png");

			BackGround.position = {0,0};
			BackGround.scale = 1;
			BackGround.sprite = LoadTexture("res/PNG/Game/GameBackGround.png");

			music = menuMusic;
			sound = menuTouchSFX;
		}

		void CreditsUpdate(Screen& currentScene)
		{
			UpdateMusicStream(music);

			if (MouseMenuColision(ReturnMenuButton))
			{
				ReturnMenuButton.color = GRAY;

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					PlaySound(sound);
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
			DrawButton(BackGround);
			DrawButton(ShowCredits);
			DrawButton(ReturnMenuButton);
		}
	}
}
