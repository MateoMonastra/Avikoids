#pragma once

#include "raylib.h"
#include "raymath.h"

namespace asteroids
{
	struct Button
	{
		Vector2 position = {};
		Color color = WHITE;
		Texture2D sprite = {};
		float scale = 0;
		
		float fontSize = {};
	};

	struct Circle
	{
		Vector2 position = {};
		float radius = {};
		Color color = {};
	};

	float RandomDirection(int min, int max);

	bool MouseMenuColision(Button rec);

	void DrawButton(Button button);

	bool CollitionCheckCircles(Vector2 Circle1, float Circle1Radius, Vector2 Circle2, float Circle2Radius);

	void DrawMouse();
}