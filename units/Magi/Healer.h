#pragma once

#include "Friendly.h"

class Healer :
	public Friendly
{
public:
	Healer(GameDataRef data) :Friendly(data) {
		//Set units info
		BaseUnit::setHP(0.25);
		BaseUnit::setAttack(2);
		BaseUnit::setCurrentLane(-1);
		BaseUnit::setDef(0);
		Friendly::setDoT(0);
		BaseUnit::setRange(8.0f);
		Friendly::setMP(1);
		Friendly::setShieldHP(0);
		Friendly::setUnitCost(7);
		Friendly::setUnitLevel(1);
	}

	void setup(sf::Vector2f position) {

		animator.bindSprite(&charSprite);
		//42 x 52 Healer
		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr("Healer"),
			sf::IntRect(0, 52 * 5, 42, 52),	
			sf::Vector2i(42, 0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr("Healer"),
			sf::IntRect(0, 52 * 6, 42, 52),
			sf::Vector2i(42, 0), 0.2, 3, false, false
		);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr("Healer"),
			sf::IntRect(0, 52 * 7, 42, 52),
			sf::Vector2i(42, 0), 0.2, 4, false, false
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

