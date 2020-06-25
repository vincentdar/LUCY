#pragma once

#include "../Friendly.h"

namespace UNITS {
	class Archer :
		public Friendly
	{
	private:
		int numOfAttacks = 0;
		float attackUp;

		sf::Clock skillTimer;

	public:
		Archer(LUCY::GameDataRef data, Lane* lane, int laneNumber) : Friendly(data, lane, laneNumber) {
			skillTimer.restart();
		}

		void setup(sf::Vector2f position) override {

			Friendly::setUnitStats(100, 15, 600, 0.2, 1.4); //Sets unit info

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

			Friendly::setup(position);
		}

		void updateStateActions() override {

			//Friendly::updateStateActions();

			if (state == ATTACK) {
				if (clock.getElapsedTime().asSeconds() >= stats.attackSpeed) {
					numOfAttacks++;
					this->setState(IDLE);
					clock.restart();
				}
			}

			if (skillIsActivated) {
				if (skillTimer.getElapsedTime().asSeconds() >= 5.0) {
					skillIsActivated = false;
					stats.normalDamage -= attackUp;
					numOfAttacks = 0;
				}
			}

		}

		void triggerStateChanges() override {
			Friendly::triggerStateChanges();
			
			if (!skillIsActivated) {
				if (numOfAttacks >= 10) {
					skillIsActivated = true;
					skill();
				}
			}
		}

		void skill() override {
			attackUp = stats.normalDamage * 2;
			stats.normalDamage += attackUp;
			skillTimer.restart();
		}

		void update() override {
			Base::update();
		}
		
		std::string getType() override {
			return "Archer";
		}
	};
}

