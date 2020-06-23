#pragma once

#include "../Friendly.h"

namespace UNITS
{
	class Assassin :
		public Friendly
	{
	protected:
		int numOfAttacks = 0;
		float attackUp;

	public:
		Assassin(LUCY::GameDataRef data, Lane* lanes, int laneCount) : Friendly(data, lanes, laneCount) {}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(100, 500, 300);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Assassin_Green"),
				sf::IntRect(54 * 3, 36 * 0, 54, 36),
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
				sf::IntRect(0, 36 * 3, 54, 36),
				sf::Vector2i(54, 0), 0.2, 2, false, false
			);

			//Skills

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(IDLE);

			Friendly::setup(position);
		}

		void update() {
			Base::update();
		}

		void skill() {}
	};
}
