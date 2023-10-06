#include "ScreenManager.h"

#include "Screen.h"
#include "ProjectUtilities/Utilities.h"
#include "Screens/Menu.h"
#include "Screens/Game.h"

using namespace menu;
using namespace game;

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

		InitWindow(windowW, windowH,"Avikoids by Mateo Viko Monastra");
		
		currentScreen = Screen::Menu;

		SetExitKey(NULL);
		
		InitMenu();
	}

	static void Update()
	{

		switch (currentScreen)
		{
		case Screen::Menu:
			MenuUpdate(currentScreen);
			break;
		case Screen::Game:
			GameUpdate(currentScreen);
			break;
		case Screen::Credits:
			/*CreditsUpdate(currentScreen);*/
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
		switch (currentScreen)
		{
		case Screen::Menu:
			MenuDrawing();
			break;
		case Screen::Game:
			DrawGame(currentScreen);
			break;
		case Screen::Credits:
			/*CreditsDrawing();*/
			break;
		default:
			break;
		}

	}

	static void Close()
	{
		CloseWindow();
	}


}