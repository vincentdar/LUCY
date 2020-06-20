#pragma once

#include "../Friendly.h"

class Defender :
	public Friendly
{

public:
	Defender(LUCY::GameDataRef data) :Friendly(data) { }

	void setup(sf::Vector2f position) {

		Friendly::setUnit(3, 0.2, 5, 10, 0, 5, 0, 5, 0.0f, 0, -1, 15, 0); //Sets unit info

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
			"Camelot",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"Thorns",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"Sacrifice",
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
		animator.playAnimation("Camelot");
		ostate = SKILL1;
		if (manaCost(10) == true) {
			updateDefend(0.5f);
			HP -= BaseUnit::HP * 0.1;
		}
		//For 20s, CD = 30s
	}

	void Skill2() override {
		animator.playAnimation("Thorns");
		ostate = SKILL2;
		//Skill is always on, Reflect 75% of damage taken to enemy blocked
	}

	void Ultimate() override {
		animator.playAnimation("Sacrifice");
		ostate = SKILL4;
		if (manaCost(30) == true) {
			HP += Defend;
			updateAttack(Defend / 100);
			Defend = 0;
			//This unit loses 5% of it's current HP per second
		}
		//For 30s, CD = 60s
	}
};

