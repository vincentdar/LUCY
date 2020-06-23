#include "Projectile.h"

namespace UNITS
{
	Projectile::Projectile(Lane * ref, float speed, float damage, bool hasSlow, bool hasPoison, bool hasStun)
		: currentLane(ref), speed(speed), damage(damage), hasSlow(hasSlow), hasPoison(hasPoison), hasStun(hasStun)
	{}

	void Projectile::setSpeed(int speed)
	{
		this->speed = speed;
	}

	void Projectile::setAilments(bool slow, bool poison, bool stun)
	{
		this->hasSlow = slow;
		this->hasPoison = poison;
		this->hasStun = stun;
	}

	void Projectile::setLaneRef(Lane * ref)
	{
		this->currentLane = ref;
	}

	void Projectile::update()
	{
		sprite.move(-1 * speed, 0);
	}

	void Projectile::draw(sf::RenderTarget & target)
	{
		sf::Color tintRgba = { 0, 0, 0, 255 };

		if (hasSlow) {
			tintRgba.b = 150;
			sprite.setColor(sf::Color::Blue);
		}
		if (hasPoison) {
			tintRgba.g = 150;
			sprite.setColor(sf::Color::Green);
		}
		if (hasStun) {
			tintRgba.r = 150;
			sprite.setColor(sf::Color::Cyan);
		}

		target.draw(sprite);
	}
}