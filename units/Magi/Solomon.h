#pragma once

#include "Magi.h"

class Solomon : public Magi {
	bool first, second;
public:
	Solomon(GameDataRef data) : Magi(data) { first = false; second = false; }

	void setup(sf::Vector2f position) {

		Friendly::setUnit(20, 50, 15, 30, 1, 3, 300, 3, 11.5f, 0, -1, 50, 12.0f); //Sets unit info

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
			"ArsPaulina",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"ArsAlmadelSalomonis",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"ArsNova",
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

	void Skill2() override {
		animator.playAnimation("ArsAlmadelSalomonis");
		ostate = SKILL2;
		if (manaCost(1500) == true && first == true) {
			updateAttack(10);
			second = true;
		}
		//For 1 attack, CD = 9999999s
	}

	void Skill1() override {
		animator.playAnimation("ArsPaulina");
		ostate = SKILL3;
		if (manaCost(2000) == true) {
			updateAttackSpeed(30);
			first = true;
		}
		//For 2s, CD = 9999999s
	}
	void Ultimate() override {
		animator.playAnimation("ArsNova");
		ostate = SKILL4;
		if (first == true && second == true) {
			//Kills all enemies, also kill this unit, remove from hero pool
		}
	}
};
