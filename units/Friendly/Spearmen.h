#pragma once

#include "../Friendly.h"

namespace UNITS {
	class Spearman
		: public Friendly
	{
	protected:
		int numOfAttacks = 0;
		float attackUp;

		sf::Clock skillTimer;

	public:
		Spearman(GameDataRef data, Lane* lane, int laneNumber) : Friendly(data, lane, laneNumber) {}
		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(225, 175, 400, 0, 1.0);

			animator.bindSprite(&charSprite);
			//71 x 51
			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Spearman"),
				sf::IntRect(0, 51 * 0, 71, 51),
				sf::Vector2i(71, 0), 0.2, 2, true, true);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Spearman"),
				sf::IntRect(0, 51 * 1, 71, 51),
				sf::Vector2i(71, 0), 0.2, 9, false, false);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Spearman"),
				sf::IntRect(0, 51 * 2, 71, 51),
				sf::Vector2i(71, 0), 0.2, 10, false, false);

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
				if (skillTimer.getElapsedTime().asSeconds() >= 30.0) {
					skillIsActivated = false;
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
			stats.range = 100;
			attackUp = stats.normalDamage * 3;
			skillTimer.restart();
			printf("SPEARMAN USED SKILL\n");
		}

		void update() override {
			Base::update();
		}

		std::string getType() override {
			return "Spearman";
		}
	};
}