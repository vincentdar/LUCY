#pragma once

#include "Projectile.h"

namespace UNITS
{
	class Arrow
		: public Projectile
	{
	public:
		Arrow(Lane* ref, 
			sf::Vector2f spawnPosition,
			float speed = 1,
			float damage = 1,
			bool hasSlow = false,
			bool hasPoison = false,
			bool hasStun = false);
	};
}