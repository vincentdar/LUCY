#pragma once

#include "Archer.h"

namespace UNITS {
	class Ranger : public Archer {
	public:
		Ranger(GameDataRef data, Lane* lane, int laneNumber) : Archer(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) {
			Archer::setup(position);
			Friendly::setUnitStats(500, 1500, 300);
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
				if (skillTimer.getElapsedTime().asSeconds() >= 2.0) {
					skillIsActivated = false;
					stats.normalDamage -= attackUp;
					numOfAttacks = 0;
				}
			}

		}

		void triggerStateChanges() override {
			Friendly::triggerStateChanges();

			if (!skillIsActivated) {
				if (numOfAttacks >= 5) {
					skillIsActivated = true;
					skill();
				}
			}
		}

		void skill() override {
			attackUp = stats.normalDamage * 35;
			stats.normalDamage += attackUp;
			skillTimer.restart();
			printf("SKILL USED\n");
		}

		void update() override {
			Base::update();
		}
	};
}