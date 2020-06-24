#pragma once

#include "../Friendly.h"

namespace UNITS {
	class Magi :
		public Friendly
	{
	protected:
		int numOfAttacks = 0;
		float attackUp;

		sf::Clock skillTimer;
	public:
		Magi(GameDataRef data, Lane* lane, int laneNumber) :Friendly(data, lane, laneNumber) {
			skillTimer.restart();
		}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(500, 3000, 300);
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

			Friendly::setup(position);
		}
		void updateStateActions() override {

			if (state == ATTACK) {
				if (clock.getElapsedTime().asSeconds() >= 2.0) {
					this->setState(IDLE);
					numOfAttacks++;
					clock.restart();
				}
			}

			if (skillIsActivated) {
				if (skillTimer.getElapsedTime().asSeconds() >= 3.0) {
					skillIsActivated = false;
					stats.normalDamage -= attackUp;
					numOfAttacks = 0;
				}
			}

		}

		void triggerStateChanges() override {
			Friendly::triggerStateChanges();

			if (!skillIsActivated) {
				if (numOfAttacks >= 2) {
					skillIsActivated = true;
					skill();
				}
			}
		}

		void skill() override {
			attackUp = stats.normalDamage * 1.5;
			stats.normalDamage += attackUp;
			skillTimer.restart();
			printf("SKILL USED\n");
		}

		void update() override {
			Base::update();
		}

		std::string getType() override {
			return "Magi";
		}
	};

}