#pragma once

namespace asteroids
{
	namespace game 
	{
		enum class GameScenes
		{
			ShowPlayerRules = 1,
			ShowReminder,
			ShowAlienRules,
			ShowFollowingAlienRules,
			ShowPowerUpsRules,
			Playing,
			Paused,
			Lose
		};
	}
}