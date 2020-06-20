#pragma once

#include "Magi.h"

class Invoker : public Magi {
public:
	Invoker(GameDataRef data): Magi(data){}

	void setup(sf::Vector2f position) {
		
		Friendly::setUnit(1, 2, 2, 10, 3, 0.1, 0, 1, 11.5f, 0, -1, 25, 7.0f); //Sets unit info

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
			"Cataclysm",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"Alacrity",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"SoulOverload",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 5, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void update() {
		BaseUnit::update();
		animator.updateAnimation();
	}

	void draw(sf::RenderTarget& target) {
		target.draw(charSprite);
	}

	void attack() {
		animator.playAnimation("Attack");
	}

	void run() {
		animator.playAnimation("Move");
	}

	void Skill1() override {
		Magi::Ultimate();
	}

	void Skill2() override {
		animator.playAnimation("Alacrity");
		ostate = SKILL2;
		if (manaCost(20) == true) {
			updateAttackSpeed(30);
			updateAttack(1.2);
		}
		//For 15s, CD = 20s
	}

	void Ultimate() override {
		animator.playAnimation("SoulOverload");
		ostate = SKILL4;
		if (manaCost(150) == true) {
			updateAttack(10);
			updateAttackSpeed(20);
			attackRange = 20.0f;
			//Dies the skill duration end
		}
		//For 30s
	}
};
