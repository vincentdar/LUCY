#pragma once

#include "Base_Unit.h"

class Defender :
	public BaseUnit
{

public:
	Defender(LUCY::GameDataRef data) :BaseUnit(data) { }

	void setup(sf::Vector2f position) {

		BaseUnit::setUnit(3, 0.2, 5, 10, 0, 0, 5, 0, 5); //Sets unit info

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

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void update() {
		BaseUnit::Update();
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
};
