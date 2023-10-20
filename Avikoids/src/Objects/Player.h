#pragma once

#include "ProjectUtilities/Utilities.h"

namespace asteroids
{
	struct Spaceship
	{
		Vector2i Position_i= {0,0};
		Vector2 Position_f= {0,0};

		float shipRotation = {};

		float BASE_SPEED = {};

		float aceleration = {};

		Texture2D texture = {};
		
	};


	void SpaceshipUpdate(Spaceship& player);



}