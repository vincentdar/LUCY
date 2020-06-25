#pragma once

#include "../Friendly.h"

#include "../../Lane.h"

namespace UNITS {
	class Healer :
		public Friendly
	{
	protected:
		sf::Clock skillTimer;
		int numOfAttacks = 0;
	public:
		Healer(GameDataRef data, Lane* lane, int laneNumber) :Friendly(data, lane, laneNumber) {
			unitCost = 30;
		}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(100, 125, 900, 0, 4);
			animator.bindSprite(&charSprite);
			//42 x 52 Healer
			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Healer"),
				sf::IntRect(0, 52 * 4, 42, 52),
				sf::Vector2i(42, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Healer"),
				sf::IntRect(0, 52 * 5, 42, 52),
				sf::Vector2i(42, 0), 0.2, 3, false, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Healer"),
				sf::IntRect(0, 52 * 6, 42, 52),
				sf::Vector2i(42, 0), 0.2, 4, false, false
			);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(IDLE);

			Friendly::setup(position);
		}

		void updateStateActions() override {

			if (state == ATTACK) {
				if (clock.getElapsedTime().asSeconds() >= 2.0) {
					checkFriendlyHP();
					numOfAttacks++;
					clock.restart();
				}
			}

			if (skillIsActivated) {
				numOfAttacks = 0;
				skillIsActivated = false;
				stats.normalDamage /= 2;
			}

		}

		void checkFriendlyHP() {
			for (int i = 0; i < laneDataRef[this->laneNumber].getFriendlyCount(); i++) {
				if (laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().health < laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().max_health)
					this->setState(ATTACK);
				else
					this->setState(IDLE);
			}
		}

		void triggerStateChanges() override {
			if (state != ATTACK) {
				// If enemy is close, setState attack
				// SAMPLE MELEE ATTACK!1!1
				int friendlyWithMinDistance = INT_MAX;
				int target = 0;
				Friendly* friendlyUnit = nullptr;
				for (int i = 0; i < laneDataRef[laneNumber].getFriendlyCount(); i++)
				{
					int distance = charSprite.getPosition().x - laneDataRef[laneNumber].getFriendlyUnit(i)->getPosition().x;
					if (distance < stats.range && distance < friendlyWithMinDistance && distance > 0)
					{
						friendlyWithMinDistance = distance;
						friendlyUnit = laneDataRef[laneNumber].getFriendlyUnit(i);
					}

				}

				if (friendlyUnit != nullptr) {
					this->setState(ATTACK);
					friendlyUnit->takeDamage(stats.normalDamage * -1);

					for (int i = 0; i < laneDataRef[this->laneNumber].getFriendlyCount(); i++) {
						if (laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().health >= laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().max_health) {
							laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().health 
								= laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().max_health;
						}
					}

					friendlyUnit = nullptr;
					numOfAttacks++;
					clock.restart();
				}

				if (!skillIsActivated) {
					if (numOfAttacks >= 5) {
						skillIsActivated = true;
						skill();
					}
				}
			}
		}

		void update() {
			Base::update();
		}

		void skill() override {
			//Waiting for near future implementation, coz im dumb
			//Edit 1: IT WORKS
			for (int i = 0; i < laneDataRef[this->laneNumber].getFriendlyCount(); i++) {
				laneDataRef[this->laneNumber].getFriendlyUnit(i)->takeDamage(-(this->stats.normalDamage * 2));

				if (laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().health >= laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().max_health)
					laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().health = laneDataRef[this->laneNumber].getFriendlyUnit(i)->getUnitStats().max_health;
			}

			stats.normalDamage *= 2;
			printf("HEALER USED SKILL\n");
		}

		std::string getType() override { return "Healer"; }
	};

}