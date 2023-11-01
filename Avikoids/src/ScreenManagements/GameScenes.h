#pragma once

namespace asteroids
{
	namespace game 
	{
		enum class GameScenes
		{
			ShowPlayerRules = 1,
			ShowAlienRules,
			ShowPowerUpsRules,
			Playing,
			Paused,
			Lose
		};
	}
}