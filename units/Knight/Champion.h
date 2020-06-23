#pragma once

#include "GoldenKnight.h"

namespace UNITS {
	class Champion : public GoldenKnight {
	public:
		Champion(GameDataRef data, Lane* lane, int laneNumber) : GoldenKnight(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) {

			Friendly::setup(position);
			Friendly::setUnitStats(175, 80, 50);
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
				if (skillTimer.getElapsedTime().asSeconds() >= 20.0) {
					skillIsActivated = false;
					stats.normalDamage -= attackUp;
					numOfAttacks = 0;
				}
			}

		}

		void triggerStateChanges() override {
			Friendly::triggerStateChanges();

			if (!skillIsActivated) {
				if (numOfAttacks >= 25) {
					skillIsActivated = true;
					skill();
				}
			}
		}

		void skill() override {
			attackUp = stats.normalDamage * 100;
			stats.normalDamage += attackUp;
			stats.health += attackUp;
			skillTimer.restart();
			printf("SKILL USED\n");
		}

		void update() override {
			Base::update();
		}
		
	};
}