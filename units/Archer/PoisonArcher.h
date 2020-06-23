#pragma once

#include "Archer.h"

namespace UNITS {
	class PoisonA : public Archer {
	public:
		PoisonA(GameDataRef data, Lane* lane, int laneNumber) : Archer(data, lane, laneNumber) {
			skillTimer.restart();
		}

		void setup(sf::Vector2f position) {
			Archer::setup(position);
			Friendly::setUnitStats(1200, 750, 600);
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
				if (skillTimer.getElapsedTime().asSeconds() >= 5.0) {
					skillIsActivated = false;
					//stats.normalDamage -= attackUp;
					numOfAttacks = 0;
				}
			}

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
				if (skillTimer.getElapsedTime().asSeconds() >= 10.0) {
					skillIsActivated = false;
					numOfAttacks = 0;
					stats.normalDamage -= attackUp;
				}
			}
		}

		void triggerStateChanges() override {
			Friendly::triggerStateChanges();
			if (!skillIsActivated) {
				if (numOfAttacks >= 15) {
					skillIsActivated = true;
					skill();
				}
			}
		}
		void update() {
			Base::update();
		}

		void skill() override {
			attackUp = stats.normalDamage * 20;
			stats.normalDamage += attackUp;
			skillTimer.restart();
			printf("SKILL USED\n");
		}
	};
}