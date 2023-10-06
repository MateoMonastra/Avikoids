#pragma once

#include "ScreenManagements/Screen.h"

namespace game
{
	void InitGame(Screen currentScreen);
	int GameUpdate(Screen& currentScreen);
	void DrawGame(Screen currentScreen);
};