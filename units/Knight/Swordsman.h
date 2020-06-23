#pragma once

#include "GoldenKnight.h"

namespace UNITS {
	class Swordsman : public GoldenKnight {
	public:
		Swordsman(GameDataRef data, Lane* lane, int laneNumber) : GoldenKnight(data, lane, laneNumber) {
			skillTimer.restart();
		}

		void setup(sf::Vector2f position) {
			Friendly::setup(position);
			Friendly::setUnitStats(2000, 3000, 100);
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
			attackUp = stats.normalDamage * 20;
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