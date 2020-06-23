#pragma once

#include "Archer.h"

namespace UNITS {
	class Ranger : public Archer {
	public:
		Ranger(GameDataRef data, Lane* lane, int laneNumber) : Archer(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) {
			
			Friendly::setUnitStats(90, 50, 600);

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

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(IDLE);
		}
	};
}