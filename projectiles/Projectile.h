#pragma once

#include "SFML/Graphics.hpp"

class Lane;

namespace UNITS
{
	class Projectile
	{
	protected:
		float	speed;
		float	damage;

		bool	hasSlow	= false;
		bool	hasPoison	= false;
		bool	hasStun	= false;

		int		poisonDamage = 0;

		Lane*	currentLane;

		sf::Sprite sprite;

		Projectile(Lane* ref,
			float speed = 1,
			float damage = 1,
			bool hasSlow = false,
			bool hasPoison = false,
			bool hasStun = false);

	public:
		
		// Get information from projectile
		float getDamage()	{ return damage; }
		bool getSlow()		{ return hasSlow; }
		bool getPoison()	{ return hasPoison; }
		bool getStun()		{ return hasStun; }

		void setSpeed(int speed);
		void setAilments(bool slow, bool poison, bool stun);
		void setLaneRef(Lane* ref);

		virtual void update();
		virtual void draw(sf::RenderTarget& target);
	};
}