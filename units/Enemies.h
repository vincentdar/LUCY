#pragma once

#include "Base_Unit.h"

class Enemies : public BaseUnit {
protected:
	float movementSpeed;

public:
	Enemies(GameDataRef data, Lane* lane) : BaseUnit(data, lane){}
	
	virtual void setup(float hp, float atk, float def, float range, float doT, int lane, float ms, float as, sf::Vector2f position) {
		BaseUnit::setUnit(hp, atk, def, 0, range, doT, lane, as);
		lifes = 1;
		movementSpeed = ms;
	}

	void checkLifes() {
		if (lifes <= 0)
			isAlive = false;
	}

	void takeDamage(float dmg) override {
		BaseUnit::takeDamage(dmg);
		checkLifes();
	}
};
