#pragma once

#include "Archer.h"

class PoisonA : public Archer {
public:
	PoisonA(GameDataRef data): Archer(data){}

	void setup(sf::Vector2f position) {

		Friendly::setUnit(1.5, 0.75, 5, 3, 1.8, 1.25, 0, 1, 10.0f, 1 * 0.5, -1, 5, 5.0f); // 5 extra cost to upgrade the unit

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr(""),	//Need a file name
			sf::IntRect(0, 52 * 2, 86, 52),	//Probably stays the same as the golden knight
			sf::Vector2i(86, 0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 3, false, false
		);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		//Skills

		animator.addAnimationState(
			"AttackUp",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"PoisonUp",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"FatalShot",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 5, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void Skill1() override {
		animator.playAnimation("PoisonArrow");
		ostate = SKILL1;
		if(manaCost(20) == true)
			updateAttack(0.75);
		//For 30 seconds, CD = 15s
	}

	void Skill2() override {
		animator.playAnimation("PoisonUp");
		ostate = SKILL2;
		if (manaCost(5) == true)
			updateDoT(0.5);
		//InfiniteDuration, Staccable, CD = 5s
	}

	void Ultimate() override {
		animator.playAnimation("FatalShot");
		ostate = SKILL4;
		if (manaCost(50) == true)
			updateAttack(dot + Attack * 3);
		//For one shot or attack, CD = 60s
	}
};