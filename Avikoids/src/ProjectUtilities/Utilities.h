#pragma once

#include "raylib.h"
#include "raymath.h"

struct Button
{
	Vector2 position = {};
	Color color = WHITE;
	Texture2D sprite = {};
	float scale = 0;
};

struct Circle
{
	Vector2 position = {};
	float radius = {};
	Color color = {};
};

float RandomDirection(int min, int max);

