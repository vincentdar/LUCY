#pragma once

#include "../Friendly.h"

namespace UNITS
{
	class Assassin :
		public Friendly
	{
	public:
		Assassin(LUCY::GameDataRef data, Lane* lanes, int laneCount) : Friendly(data, lanes, laneCount) {}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(1, 1, 1, 1, 1, 1, 1, 1, 1, 1); //Sets unit info

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Assassin_Green"),
				sf::IntRect(0, 36 * 0, 54, 36),
				sf::Vector2i(54, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Assassin_Green"),
				sf::IntRect(0, 36 * 1, 54, 36),
				sf::Vector2i(54, 0), 0.2, 2, false, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Assassin_Green"),
				sf::IntRect(0, 52 * 3, 54, 36),
				sf::Vector2i(54, 0), 0.2, 2, false, false
			);

			//Skills

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(IDLE);
		}

		void update() {
			Base::update();
		}

		void skill() {}
	};
}
