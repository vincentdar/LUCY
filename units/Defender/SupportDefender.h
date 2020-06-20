#pragma once

#include "Defender.h"

class SupportDeff :public Defender {
public:
	SupportDeff(GameDataRef data) : Defender(data) {}

	void setup(sf::Vector2f position) {

		Friendly::setUnit(5, 0.1, 15, 0.3, 0.5, 7, 100, 7, 2.0f, 0, -1, 23, 2.5f); //Sets unit info

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
			"HealUp",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"DeffBuff",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"TacticalRetreat",
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
		animator.playAnimation("HealUp");
		ostate = SKILL1;
		if (manaCost(3) == true) {
			HP += HP * 0.2;
			updateDefend(0.5);
			//For friendly units
		}
		//Defense up for 10s, CD = 20s
	}

	void Skill2() override {
		animator.playAnimation("DeffBuff");
		ostate = SKILL2;
		if (manaCost(5) == true) {
			updateDefend(5);
			updateHPRegen(5);
			//For friendly units
		}
		//For 10s, CD = 20s
	}

	void Ultimate() override {
		animator.playAnimation("TacticalRetreat");
		ostate = SKILL4;
		if (manaCost(7.5f) == true) {
			updateAttack(7);
			updateDefend(10);
			updateHPRegen(10);
			updateMPRegen(20);
			//For friendly units
			isAlive = false; //Suicide
		}
		//For 5s
	}
};
