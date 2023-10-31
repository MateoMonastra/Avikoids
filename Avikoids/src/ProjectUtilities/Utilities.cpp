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

	void DrawButton(Button button)
	{
		DrawTextureEx(button.sprite, button.position, 0, button.scale, button.color);
	}

	bool CollitionCheckCircles(Vector2 Circle1, float Circle1Radius, Vector2 Circle2, float Circle2Radius)
	{

		double distancia = sqrt((Circle1.x - Circle2.x) * (Circle1.x - Circle2.x) + (Circle1.y - Circle2.y) * (Circle1.y - Circle2.y));

		if (distancia < Circle1Radius + Circle2Radius)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	
}