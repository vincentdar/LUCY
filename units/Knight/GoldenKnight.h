#pragma once

#include "../Friendly.h"

namespace UNITS {
	class GoldenKnight
		: public Friendly
	{
	protected:
		int numOfAttacks = 0;
		float attackUp;

		sf::Clock skillTimer;

	public:
		GoldenKnight(GameDataRef data, Lane* lane, int laneNumber) : Friendly(data, lane, laneNumber) { 
			skillTimer.restart();
		}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(1000, 1, 100);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(86, 52 * 2, -86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, true);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(86, 52 * 1, -86, 52),
				sf::Vector2i(86, 0), 0.2, 3, true, false);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Knight_Gold"),
				sf::IntRect(86, 52 * 0, -86, 52),
				sf::Vector2i(86, 0), 0.2, 2, false, false);

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
				if (skillTimer.getElapsedTime().asSeconds() >= 10.0) {
					skillIsActivated = false;
					stats.normalDamage -= attackUp;
					numOfAttacks = 0;
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

		void skill() override {
			attackUp = stats.normalDamage * 50;
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