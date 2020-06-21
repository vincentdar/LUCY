#pragma once

#include "GoldenKnight.h"

class Champion : public GoldenKnight {
public:
	Champion(GameDataRef data): GoldenKnight(data){}

	void setup(sf::Vector2f position) {
		
		Friendly::setUnit(3, 3, 10, 5, 4, 3, 300, 4, 4.5f, 0, -1, 15, 8.0f);

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

		//Skills
		animator.addAnimationState("20%Power",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState("80%Power",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 5, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState("BeyondPlusUltra",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		// kalo tidak ada spritenya ya, munkgin yg Bash / headsplitter tapi pas dia ngangkat pedang itu di hold beberapa ms

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
		animator.playAnimation("20%Power");
		ostate = SKILL1;
		if (manaCost(Friendly::MP * 0.2) == true)
			updateAttack(0.2);
		//For 5s, CD = 10s
	}

	void Skill2() override {
		animator.playAnimation("80%Power");
		ostate = SKILL2;
		if (manaCost(Friendly::MP * 0.5) == true)
			updateAttack(0.8);
		//For 8s, CD = 20s
	}
	void Ultimate() {
		animator.playAnimation("BeyondPlusUltra");
		ostate = SKILL4;
		if (manaCost(Friendly::MP) == true)
			updateAttack(100);
		//For 15s, CD = 60s
	}
};
