#pragma once

#include "GoldenKnight.h"

namespace UNITS {
	class Swordsman : public GoldenKnight {
	public:
		Swordsman(GameDataRef data, Lane* lane, int laneNumber) : GoldenKnight(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) {
			Friendly::setUnitStats(100, 150, 80);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(0, 52 * 2, 86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, true);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(0, 52 * 1, 86, 52),
				sf::Vector2i(86, 0), 0.2, 3, false, false);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(0, 52 * 0, 86, 52),
				sf::Vector2i(86, 0), 0.2, 2, false, false);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(IDLE);

		}

		void update() {
			Base::update();
		}

		void skill() override {
			printf("SKILL\n");
		}
	};
}