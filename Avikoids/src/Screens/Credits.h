#pragma once

#include "ProjectUtilities/Utilities.h"

#include "ScreenManagements/Screen.h"

namespace asteroids
{
	namespace credits
	{
		void InitCredits(Music& menuMusic, Sound menuTouchSFX);
		void CreditsUpdate(Screen& currentScene);
		void CreditsDrawing();
	}
}
