#pragma once

#include "../Friendly.h"
#include "../../Game.h"
#include "../../Animator.h"

class GoldenKnight
	: public Friendly
{
public:
	GoldenKnight(LUCY::GameDataRef data) : Friendly(data) {  }

	void setup(sf::Vector2f position) {

		Friendly::setUnit(1.5, 0.1, 5, 1, 1.2, 1, 0, 3, 4.5f, 0, -1, 10, 6.0f);

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
		animator.addAnimationState("HeadSplitter",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState("GuardUp",
			data->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 5, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState("Excalibur",
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
		animator.playAnimation("HeadSplitter");
		ostate = SKILL1;
		if (manaCost(5) == true)
			updateAttack(4);
		//For one attack, CD = 5s
	}

	void Skill2() override {
		animator.playAnimation("ShieldUP");
		ostate = SKILL2;
		//Passive, every 20s Deffend + 50%, staccable
		//Note that the OG Deff value is the one modified not the DefUp
	}
	void Ultimate() {
		animator.playAnimation("Excalibur");
		ostate = SKILL4;
		if (manaCost(MP) == true)
			updateAttack(12);
		//For one attack, attack range became 3 x 8, CD = 240s
	}
};