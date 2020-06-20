#pragma once

#include "../Friendly.h"

class Archer :
	public Friendly
{
public:
	Archer(LUCY::GameDataRef data) :Friendly(data) {}

	void setup(sf::Vector2f position) {

		Friendly::setUnit(0.75, 0.25, 3, 2, 1, 0.75, 0, 1, 10.0f, 0, -1, 10, 3.5f); //Sets unit info

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr("Archer_Green"),
			sf::IntRect(0, 51 * 1, 37, 51),
			sf::Vector2i(37, 0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr("Archer_Green"),
			sf::IntRect(0, 51 * 0, 37, 51),
			sf::Vector2i(37, 0), 0.2, 3, true, false
		);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr("Archer_Green"),
			sf::IntRect(0, 51 * 2, 37, 51),
			sf::Vector2i(37, 0), 0.2, 6, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void update() {
		charSprite.setOrigin(charSprite.getLocalBounds().width / 2.0, charSprite.getLocalBounds().height);
		animator.updateAnimation();
	}

	void attack() {
		animator.playAnimation("Attack");
	}

	void run() {
		animator.playAnimation("Move");
	}

	virtual void Skill1() override {
		animator.playAnimation("PrecisionShot");
		ostate = SKILL1;
		if(manaCost(10) == true)
			updateAttack(5);
		//For one attack, CD = 10 seconds
	}

	virtual void Skill2() override {
		animator.playAnimation("ManaShield");
		ostate = SKILL2;
		if(manaCost(15) == true)
			setShieldHP(0.5 * HP);
		//Infinite Duration, Staccable, CD = 20 s
	}

	virtual void Ultimate()  override {
		animator.playAnimation("CosmicShot");
		ostate = SKILL4;
		if(manaCost(30) == true)
			updateAttack(10);
		//For one attack, CD = 60s
	}
};

