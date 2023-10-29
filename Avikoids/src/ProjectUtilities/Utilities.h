#pragma once

#include "raylib.h"
#include "raymath.h"

struct Vector2i
{
	int x = {};
	int y = {};

};

struct Circle
{
	Vector2 position = {};
	float radius = {};
	Color color = {};
};

float RandomDirection(int min, int max);

