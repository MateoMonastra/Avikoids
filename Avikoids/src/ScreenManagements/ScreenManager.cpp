#include "ScreenManager.h"

#include "ProjectUtilities/Utilities.h"

#include "Screen.h"
#include "Screens/Menu.h"
#include "Screens/Game.h"
#include "Screens/Credits.h"

namespace asteroids
{
	namespace scenemanager
	{
		Screen currentScreen;

		static void InitProgram();
		static void Update();
		static void Draw();
		static void Close();


		void RunProgram()
		{
			InitProgram();

			while (!WindowShouldClose() && currentScreen != Screen::Exit)
			{
				Update();
				Draw();
			}

			Close();
		}

		static void InitProgram()
		{
			int windowH = 768;
			int windowW = 1024;

			InitWindow(windowW, windowH, "Avikoids by Mateo Viko Monastra");

			currentScreen = Screen::Menu;

			SetExitKey(NULL);
			SetRandomSeed(NULL);
			InitAudioDevice();
			menu::InitMenu();
		}

		static void Update()
		{
			
			switch (currentScreen)
			{
			case Screen::Menu:
				menu::MenuUpdate(currentScreen);
				break;
			case Screen::Game:
				game::GameUpdate(currentScreen);
				break;
			case Screen::Credits:
				credits::CreditsUpdate(currentScreen);
				break;
			case Screen::Exit:
				Close();
				break;
			default:
				break;
			}
			
		}

		static void Draw()
		{
			BeginDrawing();
			ClearBackground(BLACK);
			switch (currentScreen)
			{
			case Screen::Menu:
				menu::MenuDrawing();
				break;
			case Screen::Game:
				game::DrawGame();
				break;
			case Screen::Credits:
				credits::CreditsDrawing();
				break;
			default:
				break;
			}
			EndDrawing();
		}

		static void Close()
		{
			CloseAudioDevice();
			CloseWindow();
		}


	}
}