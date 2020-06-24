#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilSpearmen : public Enemies {

	public:
		EvilSpearmen(GameDataRef data, Lane* lane, int laneNumber) : Enemies(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) override {
			Base::setUnitStats(120, 25, 100, 0.5, 1.0);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Spearman_Enemy"),
				sf::IntRect(0, 51 * 0, 71, 51),
				sf::Vector2i(71, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Spearman_Enemy"),
				sf::IntRect(0, 51 * 1, 71, 51),
				sf::Vector2i(71, 0), 0.1, 9, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Spearman_Enemy"),
				sf::IntRect(0, 51 * 2, 71, 51),
				sf::Vector2i(71, 0), 0.1, 10, true, false
			);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(MOVE);
		}

		void skill() {}
		
	};
}