#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilSpearmen : public Enemies {

	public:
		EvilSpearmen(GameDataRef data, Lane* lane, int laneNumber) : Enemies(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) override {
			Base::setUnitStats(130, 60, 80);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Spearman_Enemy"),
				sf::IntRect(0, 51 * 0, 71, 51),
				sf::Vector2i(86, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Spearman_Enemy"),
				sf::IntRect(0, 51 * 1, 71, 51),
				sf::Vector2i(86, 0), 0.2, 2, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Spearman_Enemy"),
				sf::IntRect(0, 51 * 2, 71, 51),
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