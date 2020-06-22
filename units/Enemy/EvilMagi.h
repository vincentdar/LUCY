#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilMagi : public Enemies {

	public:
		EvilMagi(GameDataRef data, Lane* lane, int laneNumber) : Enemies(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) override {
			Base::setUnitStats(30, 80, 200);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Magi"),
				sf::IntRect(0, 63 * 0, 62, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Magi"),
				sf::IntRect(0, 63 * 1, 62, 63),
				sf::Vector2i(86, 0), 0.2, 2, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Magi"),
				sf::IntRect(0, 63 * 2, 62, 63),
				sf::Vector2i(86, 0), 0.2, 2, true, false
			);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(MOVE);
		}

		void update() {
			Base::update();
			if (state == MOVE)
				charSprite.move(-1, 0);
		}
	};
}