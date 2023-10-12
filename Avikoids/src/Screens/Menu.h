#pragma once
#include "ScreenManagements/Screen.h"

namespace asteroids
{
	namespace menu
	{
		void InitMenu();
		void MenuUpdate(Screen& currentScene);
		void MenuDrawing();
	}
}