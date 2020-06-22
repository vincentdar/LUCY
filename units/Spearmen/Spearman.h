#pragma once

#include "Friendly.h"

class Spearman
	: public Friendly
{
public:
	Spearman(GameDataRef data) : Friendly(data) {
		//Set units info
		BaseUnit::setHP(1.25);
		BaseUnit::setAttack(1.5);
		BaseUnit::setCurrentLane(-1);
		BaseUnit::setDef(0.5);
		Friendly::setDoT(0);
		BaseUnit::setRange(5.0f);
		Friendly::setMP(0.3);
		Friendly::setUnitCost(10);
		Friendly::setUnitLevel(1);
	}
	void setup(sf::Vector2f position) {

		animator.bindSprite(&charSprite);
		//71 x 51
		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr("Spearmen"),
			sf::IntRect(0, 51 * 0, 71, 51),
			sf::Vector2i(71, 0), 0.2, 2, true, true);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr("Spearmen"),
			sf::IntRect(0, 51 * 1, 71, 51),
			sf::Vector2i(71, 0), 0.2, 9, false, false);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr("Spearmen"),
			sf::IntRect(0, 51 * 2, 71, 51),
			sf::Vector2i(71, 0), 0.2, 10, false, false);

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