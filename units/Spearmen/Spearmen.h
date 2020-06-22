#pragma once

#include "../Friendly.h"

namespace UNITS {
	class Spearman
		: public Friendly
	{
	public:
		Spearman(GameDataRef data, Lane* lane, int laneNumber) : Friendly(data, lane, laneNumber) {}
		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(125, 75, 80);

			animator.bindSprite(&charSprite);
			//71 x 51
			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Spearmen"),
				sf::IntRect(0, 51 * 0, 71, 51),
				sf::Vector2i(71, 0), 0.2, 2, true, true);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Spearmen"),
				sf::IntRect(0, 51 * 1, 71, 51),
				sf::Vector2i(71, 0), 0.2, 9, false, false);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Spearmen"),
				sf::IntRect(0, 51 * 2, 71, 51),
				sf::Vector2i(71, 0), 0.2, 10, false, false);

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