#pragma once

#include "Friendly.h"

class Magi :
	public Friendly
{
public:
	Magi(GameDataRef data) :Friendly(data) {
		//Set units info
		BaseUnit::setHP(1);
		BaseUnit::setAttack(3);
		BaseUnit::setCurrentLane(-1);
		BaseUnit::setDef(0.1);
		Friendly::setDoT(0);
		BaseUnit::setRange(12.0f);
		Friendly::setMP(2);
		Friendly::setShieldHP(0);
		Friendly::setUnitCost(18);
		Friendly::setUnitLevel(1);
	}

	void setup(sf::Vector2f position) {

		animator.bindSprite(&charSprite);
		//62 x 63
		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr("Magi"),	
			sf::IntRect(0, 63 * 6, 62, 52),	
			sf::Vector2i(62, 0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr("Magi"),
			sf::IntRect(0, 63 * 7, 62, 63),
			sf::Vector2i(62, 0), 0.2, 3, false, false
		);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr("Magi"),
			sf::IntRect(0, 63 * 8, 62, 63),
			sf::Vector2i(62, 0), 0.2, 7, false, false
		);

		//Skills

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
};

