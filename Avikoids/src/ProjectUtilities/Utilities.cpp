#include "Utilities.h"

namespace asteroids
{
	float RandomDirection(int min, int max)
	{
		float randomNumber = static_cast<float>(GetRandomValue(min, max));

		randomNumber /= 100;

		return randomNumber;
	}

	bool MouseMenuColision(Button rec)
	{
		Vector2 mousePosition = GetMousePosition();

		if (mousePosition.x >= rec.position.x &&
			mousePosition.x <= rec.position.x + rec.sprite.width * rec.scale &&
			mousePosition.y >= rec.position.y &&
			mousePosition.y <= rec.position.y + rec.sprite.height * rec.scale)
		{
			return true;
		}
		return false;
	}
}