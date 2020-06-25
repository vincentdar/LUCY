#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilSpearmen : public Enemies {
	private:

		int numOfAttacks = 0;
		float attackUp = 0;
		sf::Clock skillTimer;

	public:
		EvilSpearmen(GameDataRef data, Lane* lane, int laneNumber, Wall* wall) : Enemies(data, lane, laneNumber, wall) {}

		void setup(sf::Vector2f position) override {
			Base::setUnitStats(120, 50, 150, 1.5, 2.0);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Spearman_Enemy"),
				sf::IntRect(0, 51 * 0, 71, 51),
				sf::Vector2i(71, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Spearman_Enemy"),
				sf::IntRect(0, 51 * 1, 71, 51),
				sf::Vector2i(71, 0), 0.1, 9, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Spearman_Enemy"),
				sf::IntRect(0, 51 * 2, 71, 51),
				sf::Vector2i(71, 0), 0.1, 10, true, false
			);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(MOVE);
		}

		void triggerStateChanges() override {

			Enemies::triggerStateChanges();

			if (!skillIsActivated) {
				if (numOfAttacks >= 10) {
					skillIsActivated = true;
					skill();
				}
			}
		}

		void skill() {
			if (skillIsActivated) {
				if (skillTimer.getElapsedTime().asSeconds() >= 5)
					skillIsActivated = false;
				numOfAttacks = 0;
				attackUp = 0;
				stats.range *= 3;
			}
		}
		
	};
}