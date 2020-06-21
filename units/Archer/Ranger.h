#pragma once

#include "Archer.h"

class Ranger : public Archer {
public:
	Ranger (GameDataRef data): Archer(data){}

	void setup(sf::Vector2f position) {

		Friendly::setUnit(1.3, 1.2, 3, 6, 2, 1, 0, 1, 11.0f, 0, -1, 7, 7.5f); //Sets unit info
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

		animator.addAnimationState(
			"PrecisionShot2",
			data->assets.GetTexturePtr("Archer_Black"),
			sf::IntRect(0, 53 * 3, 37, 53),
			sf::Vector2i(37, 0), 0.2, 6, false, false
		);

		animator.addAnimationState(
			"Barrage",
			data->assets.GetTexturePtr("Archer_Black"),
			sf::IntRect(0, 53 * 4, 37, 53),
			sf::Vector2i(37, 0), 0.2, 6, false, false
		);

		animator.addAnimationState(
			"Projectile Mastery",
			data->assets.GetTexturePtr("Archer_Black"),
			sf::IntRect(0, 53 * 5, 37, 53),
			sf::Vector2i(37, 0), 0.2, 6, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void Skill1() override {
		animator.playAnimation("PrecisionShot2");
		ostate = SKILL1;
		if (manaCost(15) == true)
			updateAttack(7.5);
		//For One attack, CD = 12s
		
	}

	void Skill2() override {
		animator.playAnimation("Barrage");
		ostate = SKILL2;
		if (manaCost(25) == true)
			updateAttack(5);
		//For 5 second, attack 3 lane simultaneously, CD = 40s
	}

	void Ultimate() override {
		animator.playAnimation("ProjectileMastery");
		ostate = SKILL4;
		if (manaCost(75) == true)
			updateAttack(10);
		//For 20s, has 30% chance of stunning enemies, CD = 80s
	}
};
