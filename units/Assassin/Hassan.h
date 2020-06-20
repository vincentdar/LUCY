#pragma once

#include "Assassin.h"

class Hassan :public Assassin {
public:
	Hassan(GameDataRef data): Assassin(data){}

	void setup(sf::Vector2f position) {

		Friendly::setUnit(0.1, 0.75, 5, 7, 4, 2.5, 0, 0, 3.0f, 0, -1, 12, 7.5f); //Sets unit info
		isInvis = true;
		//This unit will always stay invis

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
			"DoubleStrike",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"Zabaniya",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 5, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void Skill1() override {
		animator.playAnimation("DoubleStrike");
		ostate = SKILL1;
		if (manaCost(5) == true)
			updateAttack(2);
		//For one attack only, CD = 3s
	}

	void Ultimate() override {
		animator.playAnimation("Zabaniya");
		ostate = SKILL4;
		if (manaCost(60) == true)
			updateAttack(8);
		//For one attack, CD = 80s
	}
};