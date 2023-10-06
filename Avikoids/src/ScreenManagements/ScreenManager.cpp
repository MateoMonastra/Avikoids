#include "ScreenManager.h"

#include "Screen.h"
#include "ProjectUtilities/Utilities.h"



namespace scenemanager
{
	Screen currentScreen;

	static void InitProgram();
	static void Update();
	static void Draw();

	void RunProgram()
	{
		InitProgram();

		while (!WindowShouldClose() && currentScreen != Screen::Exit)
		{
			Update();
			Draw();
		}

		
	}

	static void InitProgram()
	{
		int windowH = 950;
		int windowW = 1100;

		
		

		currentScreen = Screen::Menu;

		SetExitKey(NULL);
		
		/*InitMenu();*/
	}

	static void Update()
	{

		switch (currentScreen)
		{
		case Screen::Menu:
			/*MenuUpdate(currentScreen);*/
			break;
		case Screen::Game:
			/*GameUpdate(currentScreen);*/
			break;
		case Screen::Credits:
			/*CreditsUpdate(currentScreen);*/
			break;
		case Screen::Exit:
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
		/*	MenuDrawing();*/
			break;
		case Screen::Game:
		/*DrawGame(currentScreen);*/
			break;
		case Screen::Credits:
		/*CreditsDrawing();*/
			break;
		default:
			break;
		}

	}


}