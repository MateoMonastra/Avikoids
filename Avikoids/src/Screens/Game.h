#pragma once
#include "ScreenManagements/Screen.h"

namespace asteroids
{
	namespace game
	{
		void InitGame();
		void GameUpdate(Screen& currentScene);
		void DrawGame();
	}
}