#include "Game.h"

#include "ProjectUtilities/Utilities.h"
#include "Objects/SpaceShip.h"
#include "Objects/Bullet.h"

namespace asteroids
{
	namespace game
	{
		
		Spaceship player;


		void InitGame()
		{
			float scale = 0.2f;
			float WidthF = static_cast<float>(GetScreenWidth());
			
			float HeightF = static_cast<float>(GetScreenHeight());

			player.position = { WidthF / 2, HeightF / 2};
			player.textureRec.x = WidthF / 2;
			player.textureRec.y = HeightF / 2;
			player.textureRec.height = 50;
			player.textureRec.width = 50;
			player.texture = LoadTexture("assets/PNG/player/PersonajeJugable.png");
			
			player.source = { 0,0,static_cast<float>(player.texture.width),static_cast<float>(player.texture.height) };
			
			player.dest = { player.position.x,player.position.y,static_cast<float>(player.texture.width)* scale,static_cast<float>(player.texture.height)* scale };

			player.origin = { static_cast<float>(player.source.width / 2)* scale, static_cast<float> (player.source.height / 2)* scale };
			
		}

		void GameUpdate()
		{
			SpaceshipUpdate(player);

		}

		void DrawGame()
		{
			/*DrawRectanglePro(player.textureRec, player.origin, static_cast<float>(player.shipRotation), RED);*/

			DrawTexturePro(player.texture, player.source,player.dest,player.origin, static_cast<float>(player.shipRotation),WHITE);

			for (int i = 0; i < player.maxBullets; i++)
			{
				DrawBullet(player.bullets[i]);
			}
		}
	}
};