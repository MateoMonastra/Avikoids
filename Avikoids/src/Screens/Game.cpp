#include "Game.h"

#include "ProjectUtilities/Utilities.h"
#include "Objects/SpaceShip.h"

namespace asteroids
{
	namespace game
	{
		Rectangle playerSprite;

		Spaceship player;

		void InitGame()
		{
			float WidthF = static_cast<float>(GetScreenWidth());
			int WidthI = GetScreenWidth();

			float HeightF = static_cast<float>(GetScreenHeight());
			int HeightI = GetScreenHeight();

			player.Position_i = { WidthI / 2, HeightI / 2};
			player.Position_f = { WidthF / 2, HeightF / 2};

			playerSprite.x = WidthF ;
			playerSprite.y = HeightF ;
			playerSprite.width = player.width;
			playerSprite.height = player.height;
		}

		void GameUpdate()
		{
			SpaceshipUpdate(player);
		}

		void DrawGame()
		{
			DrawRectanglePro(playerSprite, player.Position_f, player.shipRotation, RED);
		}
	}
};