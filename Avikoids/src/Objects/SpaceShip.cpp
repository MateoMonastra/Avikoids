#include "SpaceShip.h"

namespace asteroids
{
	void SpaceshipUpdate(Spaceship& player)
	{
		Vector2 mousePos = GetMousePosition();

		Vector2 direction = Vector2Subtract(player.Position_f, mousePos);

		float angle = direction.x / direction.y;
	
		player.shipRotation = angle;
	}
}