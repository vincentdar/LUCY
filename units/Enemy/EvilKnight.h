#pragma once

#include "../Enemies.h"

class EvilKnight : public Enemies {

public:
	EvilKnight(GameDataRef data) : Enemies(data) {}

	void setup(float hp, float atk, float def, float range, float doT, int lane, float ms, float as, sf::Vector2f position) override {
		BaseUnit::setUnit(hp, atk, def, 0, range, doT, lane, as);
		lifes = 1;
		movementSpeed = ms;

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 2, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, true, false
		);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, true, false
		);

		animator.addAnimationState(
			"Death",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void update() {
		animator.updateAnimation();
	}

	void attack() override {
		animator.playAnimation("Attack");
	}

	void run() override {
		animator.playAnimation("Move");
	}

	void die() override {
		animator.playAnimation("Death");
		lifes--;
		if (lifes <= 0)
			isAlive = false;
	}
};
