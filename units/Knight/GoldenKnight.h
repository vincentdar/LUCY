#pragma once

#include "../Friendly.h"

namespace UNITS {
	class GoldenKnight
		: public Friendly
	{
	public:
		GoldenKnight(GameDataRef data, Lane* lane, int laneNumber) : Friendly(data, lane, laneNumber) {  }

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(150, 60, 100);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(86, 52 * 2, -86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, true);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(86, 52 * 1, -86, 52),
				sf::Vector2i(86, 0), 0.2, 3, true, false);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(86, 52 * 0, -86, 52),
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