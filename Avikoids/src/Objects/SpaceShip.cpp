#include "SpaceShip.h"

namespace asteroids
{
	void SpaceshipUpdate(Spaceship& player)
	{
		Vector2 mousePos = GetMousePosition();

		Vector2 direction = Vector2Subtract(player.position_f, mousePos);

		double angle = atan2 (static_cast<double>(direction.y),static_cast<double>(direction.x)) * RAD2DEG + 90;
	
		player.shipRotation = angle;
	}
}