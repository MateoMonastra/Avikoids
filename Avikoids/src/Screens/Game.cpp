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

			player.position_i = { WidthI / 2, HeightI / 2};

			player.position_f = { WidthF / 2, HeightF / 2};

			player.origin = { static_cast<float>(player.height / 2), static_cast<float> (player.width / 2) };

			playerSprite.x = WidthF / 2;
			playerSprite.y = HeightF / 2;
			playerSprite.width = player.width;
			playerSprite.height = player.height;
		}

		void GameUpdate()
		{
			SpaceshipUpdate(player);
		}

		void DrawGame()
		{
			DrawRectanglePro(playerSprite, player.origin, static_cast<float>(player.shipRotation), RED);
		}
	}
};