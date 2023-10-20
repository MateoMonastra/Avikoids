#include "Game.h"

#include "ProjectUtilities/Utilities.h"
#include "Objects/Player.h"

namespace asteroids
{
	namespace game
	{

			Spaceship player;

		void InitGame()
		{
			float WidthF = static_cast<float>(GetScreenWidth());
			int WidthI = GetScreenWidth();

			float HeightF = static_cast<float>(GetScreenHeight());
			int HeightI = GetScreenHeight();

			player.Position_i = { WidthI / 2, HeightI / 2};
			player.Position_f = { WidthF / 2, HeightF / 2};
		}

		void GameUpdate()
		{
			SpaceshipUpdate(player);
		}

		void DrawGame()
		{
			DrawRectangle(player.Position_i.x, player.Position_i.y, 55,55, RED);
		}
	}
};