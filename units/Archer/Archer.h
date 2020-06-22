#pragma once

#include "../Friendly.h"

namespace UNITS {
	class Archer :
		public Friendly
	{
	private:

	public:
		Archer(LUCY::GameDataRef data, Lane lanes[], int laneNumber) : Friendly(data, lanes, laneNumber) {}

		void setup(sf::Vector2f position) override {

			Friendly::setUnitStats(1, 1, 1, 1, 1, 1 ,1, 1, 1, 1); //Sets unit info

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Archer_Green"),
				sf::IntRect(0, 51 * 1, 37, 51),
				sf::Vector2i(37, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Archer_Green"),
				sf::IntRect(0, 51 * 0, 37, 51),
				sf::Vector2i(37, 0), 0.2, 3, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Archer_Green"),
				sf::IntRect(0, 51 * 2, 37, 51),
				sf::Vector2i(37, 0), 0.2, 6, false, false
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
