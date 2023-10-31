#pragma once

#include "ScreenManagements/Screen.h"
#include "ProjectUtilities/Utilities.h"

namespace asteroids
{
	namespace credits
	{
		void InitCredits(Music& menuMusic);
		void CreditsUpdate(Screen& currentScene);
		void CreditsDrawing();
	}
}
