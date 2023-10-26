#pragma once

#include "ProjectUtilities/Utilities.h"

namespace asteroids
{
	namespace game
	{
		struct Circle
		{
			Vector2 position = {};
			float radius = {};
			Color color = {};
		};

		struct Bullet
		{

			Circle hitBox = {};
			bool IsActive = {};

			Rectangle textureRec = {};
			Vector2 origin = {};
			Rectangle dest = {};
			Rectangle source = {};
			double rotation = {};

			Texture2D texture = {};

			Vector2 aceleration = {};
			float speed = {};

		};

		void CreateBullet(Bullet& bullet, Vector2 position, Vector2 rotation, double playerRotation);
		void BulletUpdate(Bullet& bullet);
		void DrawBullet(Bullet bullet);
	}
}