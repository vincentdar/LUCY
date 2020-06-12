#pragma once

#include "Base_Unit.h"

class Defender :
	public BaseUnit
{
private:
	Animator animator;

	sf::Vector2f position;

	LUCY::GameDataRef gdr;

	sf::Sprite charSprite;

public:
	Defender(LUCY::GameDataRef gdr) :gdr(gdr) { position = { 100, 100 }; }

	void setup(sf::Vector2f position) {

		BaseUnit::setUnit(3, 0.2, 5, 10, 0, 0, 5, 0, 5); //Sets unit info

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			gdr->assets.GetTexturePtr(""),	//Need a file name
			sf::IntRect(0, 52 * 2, 86, 52),	//Probably stays the same as the golden knight
			sf::Vector2i(86, 0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			gdr->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 3, false, false
		);

		animator.addAnimationState(
			"Attack",
			gdr->assets.GetTexturePtr(""),
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

