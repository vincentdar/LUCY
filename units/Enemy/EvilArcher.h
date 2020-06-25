#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilArcher : public Enemies {
	private:
		int numOfAttacks = 0;
		float attackUp = 0;
		sf::Clock gracePeriod;

	public:
		EvilArcher(GameDataRef data, Lane* lane, int laneNumber, Wall* wall) : Enemies(data, lane, laneNumber, wall) {}

		void setup(sf::Vector2f position) override {
			Base::setUnitStats(140, 70, 400, 1, 1.4);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Archer_Black"),
				sf::IntRect(0, 53 * 1, 37, 53),
				sf::Vector2i(37, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Archer_Black"),
				sf::IntRect(0, 53 * 0, 37, 53),
				sf::Vector2i(37, 0), 0.2, 3, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Archer_Black"),
				sf::IntRect(0, 53 * 2, 37, 53),
				sf::Vector2i(37, 0), 0.2, 6, false, false
			);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(MOVE);

			Enemies::setup(position);
		}

		void updateStateActions() override {
			Enemies::updateStateActions();

			if (state == ATTACK) {
				if (clock.getElapsedTime().asSeconds() >= stats.attackSpeed) {
					this->setState(MOVE);
					clock.restart();
				}
			}
			else if (state == IDLE)
			{
				if (gracePeriod.getElapsedTime().asSeconds() >= 5.0f)
					this->setState(MOVE);
			}

			if (skillIsActivated) {
				skillIsActivated = false;
				numOfAttacks = 0;
				attackUp = 0;
			}
		}


		void skill() {
			attackUp = stats.normalDamage * 2;
			stats.normalDamage += attackUp;
		}
	};
}
