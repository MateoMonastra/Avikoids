#pragma once

#include "ProjectUtilities/Utilities.h"

namespace asteroids
{
	struct Spaceship
	{
		Vector2i position_i = { 0,0 };
		Vector2 position_f = { 0,0 };

		float height = 55;

		float width = 55;

		Vector2 origin = {};

		double shipRotation = {};

		float BASE_SPEED = {};

		float aceleration = {};

		Texture2D texture = {};
		
	};


	void SpaceshipUpdate(Spaceship& player);



}