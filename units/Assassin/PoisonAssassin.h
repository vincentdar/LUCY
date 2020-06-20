#pragma once

#include "Assassin.h"

class PoisonAssassin : public Assassin {
public:
	PoisonAssassin(GameDataRef data) : Assassin(data) {}

	void setup(sf::Vector2f position) {
		//0.5, 0.3, 2, 4, 2.5, 0.8, 0, 1, 3.0f, 0, -1, 8, 6.0f
		Friendly::setUnit(1.2, 0.5, 2, 4, 3, 2.5, 0, 1, 4.5f, 2.5 * 0.8, -1, 12, 5.0f); //Sets unit info
		isInvis = false;
		//This unit can not go invis
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
			"VitalStrike",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"PoisonMastery",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 5, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void Skill1() override {
		animator.playAnimation("VitalStrike");
		ostate = SKILL1;
		if (manaCost(5) == true) {
			updateAttack(1.5);
			updateDoT(0.25);
		}
		//For one attack, CD = 2s
	}

	void Ultimate() override {
		animator.playAnimation("PoisonMastery");
		ostate = SKILL4;
		if (manaCost(45) == true)
			updateAttack(5 + dot);
		//For 5 sec, CD = 60s
	}
};
