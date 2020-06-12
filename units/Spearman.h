#pragma once

#include "Base_Unit.h"

class Spearman
	: public BaseUnit
{
public:
	Spearman(LUCY::GameDataRef data) : BaseUnit(data) { }
	void setup(sf::Vector2f position) {

		BaseUnit::setUnit(1.25, 0.3, 3, 5, 0, 1.5, 0.5, 0, 2);

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 2, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, true, true);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 3, false, false);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

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
	}

	void run() {
		animator.playAnimation("Move");
	}
};