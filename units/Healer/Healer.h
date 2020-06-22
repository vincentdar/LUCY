#pragma once

#include "../Friendly.h"

namespace UNITS {
	class Healer :
		public Friendly
	{
	public:
		Healer(GameDataRef data, Lane* lane, int laneNumber) :Friendly(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(25, 200, 500);
			animator.bindSprite(&charSprite);
			//42 x 52 Healer
			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Healer"),
				sf::IntRect(0, 52 * 5, 42, 52),
				sf::Vector2i(42, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Healer"),
				sf::IntRect(0, 52 * 6, 42, 52),
				sf::Vector2i(42, 0), 0.2, 3, false, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Healer"),
				sf::IntRect(0, 52 * 7, 42, 52),
				sf::Vector2i(42, 0), 0.2, 4, false, false
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