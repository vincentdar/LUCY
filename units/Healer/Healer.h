#pragma once

#include "../Friendly.h"

class Healer :
	public Friendly
{
public:
	Healer(LUCY::GameDataRef data) :Friendly(data) {  }

	void setup(sf::Vector2f position) {

		Friendly::setUnit(0.25, 1, 1, 10, 1, 2, 0, 0, 5.0f, 0, -1, 13, 5.0f); //Sets unit info // cannot block any enemies 

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
			"AOEHeal",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"PassiveHeal",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		); //Passive, always on

		animator.addAnimationState(
			"LuminositeE",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);
		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");

		updateHPRegen(3);
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
		animator.playAnimation("AOEHeal");
		ostate = SKILL1;
		if (manaCost(50) == true) {
			updateAttack(0.5);
		}
		//For 5 seconds, CD = 60s
	}

	void Ultimate() override {
		animator.playAnimation("LuminositeE");
		ostate = SKILL4;
		if (manaCost(0) == true) {
			setShieldHP(3 * HP);
			updateHPRegen(30);
			isAlive = false;
		}
	}
};

