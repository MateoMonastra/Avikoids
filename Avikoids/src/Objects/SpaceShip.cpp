#include "SpaceShip.h"

#include <iostream>

namespace asteroids
{
	void SpaceshipUpdate(Spaceship& player)
	{

		if (player.position.y <  0)
		{
			player.position.y = GetScreenHeight() - player.height;
		}
		if (player.position.y > GetScreenHeight())
		{
			player.position.y = player.height;
		}
		if (player.position.x < 0)
		{
			player.position.x = GetScreenWidth() - player.width;
		}
		if (player.position.x > GetScreenWidth())
		{
			player.position.x = player.width;
		}

		Vector2 mousePos = GetMousePosition();

		Vector2 direction = Vector2Subtract(player.position, mousePos);

		double angle = atan2 (static_cast<double>(direction.y),static_cast<double>(direction.x)) * RAD2DEG + 90;
	
		player.shipRotation = angle;

		Vector2 normalizedDirection= Vector2Normalize(direction);

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			player.velocity = Vector2Add(player.velocity, Vector2Scale(direction, player.aceleration * GetFrameTime()));
		}
		
		player.position = Vector2Add(player.position, Vector2Scale( player.velocity, GetFrameTime()));
		
	}
}