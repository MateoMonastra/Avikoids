#pragma once

#include "ProjectUtilities/Utilities.h"

namespace asteroids
{
	struct Spaceship
	{
		Vector2 position = { 0,0 };

		float height = 55;

		float width = 55;

		Vector2 origin = {};

		double shipRotation = {};

		Vector2 velocity = {};

		float aceleration = {-1};

		Texture2D texture = {};
		
	};


	void SpaceshipUpdate(Spaceship& player);



}