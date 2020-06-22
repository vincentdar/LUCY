#pragma once

#include "../Friendly.h"
#include "../../Game.h"
#include "../../Animator.h"

namespace UNITS
{
	class GoldenKnight
		: public Friendly
	{
	public:
		GoldenKnight(LUCY::GameDataRef data, Lane lanes[], int laneNumber) : Friendly(data, lanes, laneNumber) {  }

		void skill() {}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(86, 52 * 2, -86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, true);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(8, 52 * 1, -86, 52),
				sf::Vector2i(86, 0), 0.2, 3, false, false);

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
			animator.updateAnimation();
		}
	};
}