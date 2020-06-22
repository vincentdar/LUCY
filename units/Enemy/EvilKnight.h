#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilKnight : public Enemies {

	public:
		EvilKnight(GameDataRef data, Lane* lane, int laneNumber) : Enemies(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) override {
			Base::setUnitStats(150, 30, 70);	

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr(""),
				sf::IntRect(0, 52 * 2, 86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr(""),
				sf::IntRect(0, 52 * 1, 86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr(""),
				sf::IntRect(0, 52 * 1, 86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, false
			);

			animator.addAnimationState(
				"Death",
				data->assets.GetTexturePtr(""),
				sf::IntRect(0, 52 * 1, 86, 52),
				sf::Vector2i(86, 0), 0.2, 2, false, false
			);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(MOVE);
		}

		void update() {
			Base::update();
			if (state == MOVE)
				charSprite.move(-1, 0);
		}
	};
}