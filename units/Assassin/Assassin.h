#pragma once

#include "../Friendly.h"

class Assassin :
	public Friendly
{
protected:
	bool isInvis;
public:
	Assassin(LUCY::GameDataRef data) : Friendly(data) { isInvis = false; }

	void setup(sf::Vector2f position) {

		Friendly::setUnit(0.5, 0.3, 2, 4, 2.5, 0.8, 0, 1, 3.0f, 0, -1, 8, 6.0f); //Sets unit info

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
			"SpectralDagger",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"Evade",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"Azrael",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 5, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void update() {
		animator.updateAnimation();
	}

	void draw(sf::RenderTarget& target) {
		target.draw(charSprite);
	}

	void attack() {
		animator.playAnimation("Attack");
		isInvis = false;
	}

	void run() {
		animator.playAnimation("Move");
		isInvis = false;
	}

	void Skill1() override {
		animator.playAnimation("SpectralDagger");
		ostate = SKILL1;
		isInvis = false;
		if (manaCost(7.5) == true) {
			updateAttack(100);
			updateDefend(-0.3);
		}
		//For 10s, CD = 15s
	}

	void Skill2() override {
		animator.playAnimation("Evade");
		ostate = SKILL2;
		isInvis = true;
		//By default is true, no MP cost, No CD
	}

	void Ultimate() override {
		animator.playAnimation("Azrail");
		ostate = SKILL4;
		isInvis = false;
		if (manaCost(100) == true) {
			updateAttack(99999);
			//Give debuf -100%Deff to all friendly on field
		}
		//For one attack, can only be used when there's enemy in this unit range of attack, CD = 120s
	}
};

