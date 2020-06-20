#pragma once

#include "GoldenKnight.h"

class Swordsman : public GoldenKnight {
public:
	Swordsman(GameDataRef data): GoldenKnight(data){}

	void setup(sf::Vector2f position) {
		//1.5, 0.1, 5, 1, 1.2, 1, 0, 3, 4.5f, 0, -1, 10, 6.0f
		Friendly::setUnit(3, 0.5, 7, 4, 2.4, 2, 0, 3, 5.0f, 0, -1, 13, 6.5f);

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 2, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, true, true);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 3, false, false);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		//Skill
		animator.addAnimationState("ManaBurst",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState("Excalibur",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 5, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState("Doomslayer",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

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

	void Skill1() override {
		animator.playAnimation("ManaBurst");
		ostate = SKILL1;
		if (manaCost(Friendly::MP * 0.5) == true)
			updateAttack(3);
		//For 10 sec, CD = 20s
	}

	void Skill2() override {
		GoldenKnight::Ultimate();
	}
	void Ultimate() {
		animator.playAnimation("Doomslayer");
		ostate = SKILL4;
		if (manaCost(Friendly::MP * 1.5) == true)
			updateAttack(20);
		//For 10s, CD = 240s
	}
};
