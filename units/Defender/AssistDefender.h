#pragma once

#include "Defender.h"

class AssistDeff : public Defender {
public:
	AssistDeff(GameDataRef data): Defender(data){}

	void setup(sf::Vector2f position) {
		//3, 0.2, 5, 10, 0, 5, 0, 5, 0.0f, 0, -1, 15, 0
		Friendly::setUnit(5, 0.5, 7.5, 10, 1, 3.5, 75, 3, 6.0f, 0, -1,  20, 3.0f); //Sets unit info

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
			"RegenUp",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"AllOutMode",
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
		animator.playAnimation("AttackUp");
		ostate = SKILL1;
		if (manaCost(10) == true)
			updateAttack(2);
		//For 15s, CD = 25s
	}

	void Skill2() override {
		animator.playAnimation("RegenUp");
		ostate = SKILL2;
		if (manaCost(20) == true) {
			updateHPRegen(10);
			updateMPRegen(10);
		}
		//For 10s, CD = 20
	}

	void Ultimate() override {
		animator.playAnimation("AllOutMode");
		ostate = SKILL4;
		if (manaCost(35) == true) {
			updateAttack(3);
			updateDefend(5);
			//For friendly
			updateHPRegen(20);
			updateMPRegen(15);
			//Exclusive for this unit
		}
		//For 7.5s, CD = 80s
	}
};
