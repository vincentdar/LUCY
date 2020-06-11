#pragma once

#include "Base_Unit.h"
#include "../Game.h"
#include "../Animator.h"

class GoldenKnight
	: public BaseUnit
{
private:
	Animator animator;

	sf::Vector2f position;

	LUCY::GameDataRef gdr;
public:
	GoldenKnight(LUCY::GameDataRef gdr) : gdr(gdr) {  }

	void setup(sf::Vector2f position) {

		BaseUnit::setUnit(1.5, 0.1, 5, 1, 0, 1.2, 1, 0, 2);

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			gdr->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 2, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, true, true);

		animator.addAnimationState(
			"Move",
			gdr->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 3, false, false);

		animator.addAnimationState(
			"Attack",
			gdr->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState("HeadSplitter",
			gdr->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 3, 86, 52),
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

	void HeadSplitter() {
		animator.playAnimation("HeadSplitter");

	}

	void Ultimate() {
		animator.playAnimation("Excalibur");
	}
};