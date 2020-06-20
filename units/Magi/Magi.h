#pragma once

#include "../Friendly.h"

class Magi :
	public Friendly
{
public:
	Magi(LUCY::GameDataRef data) :Friendly(data) { }

	void setup(sf::Vector2f position) {

		Friendly::setUnit(1, 2, 2, 10, 3, 0.1, 0, 1, 11.5f, 0, -1, 20, 5.0f); //Sets unit info

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
			"ManaRegenUP",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		); //Skill always on, Passive

		animator.addAnimationState(
			"Cataclysm",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 5, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");

		updateMPRegen(5);
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
		if (manaCost(5) == true)
			updateAttack(0.5);
		//For 15s, CD = 30s
	}

	void Ultimate() override {
		animator.playAnimation("Cataclysm");
		ostate = SKILL4;
		if (manaCost(125) == true)
			updateAttack(10);
		//AOE Damage on entire screen, only damages enemies, CD = 120s
	}
};


