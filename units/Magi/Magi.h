#pragma once

#include "../Friendly.h"

namespace UNITS {
	class Magi :
		public Friendly
	{
	public:
		Magi(GameDataRef data, Lane* lane, int laneNumber) :Friendly(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(100, 300, 100);
			animator.bindSprite(&charSprite);
			//62 x 63
			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Magi"),
				sf::IntRect(0, 63 * 6, 62, 52),
				sf::Vector2i(62, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Magi"),
				sf::IntRect(0, 63 * 7, 62, 63),
				sf::Vector2i(62, 0), 0.2, 3, false, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Magi"),
				sf::IntRect(0, 63 * 8, 62, 63),
				sf::Vector2i(62, 0), 0.2, 7, false, false
			);
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