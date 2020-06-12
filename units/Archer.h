#pragma once

#include "Base_Unit.h"

class Archer :
	public BaseUnit
{
public:
	Archer(LUCY::GameDataRef data) :BaseUnit(data) {}

	void setup(sf::Vector2f position) {

		BaseUnit::setUnit(0.75, 0.25, 3, 2, 0, 1, 0.75, 0, 1); //Sets unit info

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr("Archer_Black"),
			sf::IntRect(0, 53 * 1, 37, 53),
			sf::Vector2i(37, 0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr("Archer_Black"),
			sf::IntRect(0, 53 * 0, 37, 53),
			sf::Vector2i(37, 0), 0.2, 3, true, false
		);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr("Archer_Black"),
			sf::IntRect(0, 53 * 2, 37, 53),
			sf::Vector2i(37, 0), 0.2, 6, false, false
		);

		//Skills

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void update() {
		animator.updateAnimation();
	}

	void attack() {
		animator.playAnimation("Attack");
	}

	void run() {
		animator.playAnimation("Move");
	}
};

