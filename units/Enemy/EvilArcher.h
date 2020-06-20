#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilArcher : public Enemies {

	public:
		EvilArcher(GameDataRef data, Lane* lane) : Enemies(data, lane) {}

		void setup(sf::Vector2f position) override {
			BaseUnit::setUnit(0.75, 0.25, 3, 2, 1, 0.75, 0, 10);
			lifes = 1;

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Archer_Black"),
				sf::IntRect(0, 53 * 1, 37, 53),
				sf::Vector2i(37, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Archer_Black"),
				sf::IntRect(0, 53 * 0, 37, 53),
				sf::Vector2i(37, 0), 0.2, 3, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Archer_Black"),
				sf::IntRect(0, 53 * 2, 37, 53),
				sf::Vector2i(37, 0), 0.2, 6, false, false
			);

			animator.addAnimationState(
				"Death",
				data->assets.GetTexturePtr("Archer_Black"),
				sf::IntRect(0, 53 * 2, 37, 53),
				sf::Vector2i(37, 0), 0.2, 2, false, false
			);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			animator.playAnimation("Move");
		}

		void update() {
			Base::update();
			charSprite.move(-1, 0);
		}
	};
}
