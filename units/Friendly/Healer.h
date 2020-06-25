#pragma once

#include "../Friendly.h"

namespace UNITS {
	class Healer :
		public Friendly
	{
	protected:
		sf::Clock skillTimer;
		int numOfAttacks = 0;
	public:
		Healer(GameDataRef data, Lane* lane, int laneNumber) :Friendly(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(250, 700, 500, 100, 100);
			animator.bindSprite(&charSprite);
			//42 x 52 Healer
			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Healer"),
				sf::IntRect(0, 52 * 5, 42, 52),
				sf::Vector2i(42, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Healer"),
				sf::IntRect(0, 52 * 6, 42, 52),
				sf::Vector2i(42, 0), 0.2, 3, false, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Healer"),
				sf::IntRect(0, 52 * 7, 42, 52),
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
					this->setState(IDLE);
					numOfAttacks++;
					clock.restart();
				}
			}

			if (skillIsActivated) {
				if (skillTimer.getElapsedTime().asSeconds() >= .0) {
					skillIsActivated = false;
					numOfAttacks = 0;
				}
			}

		}

		void triggerStateChanges() override {
			Friendly::triggerStateChanges();

			if (!skillIsActivated) {
				if (numOfAttacks >= 8) {
					isSkillChanged = true;
					skillIsActivated = true;
					skill();
				}
			}
		}

		void update() {
			Base::update();
		}

		void skill() override {
			//Nge heal, how to access other's HP ?
			printf("SKILL\n");
		}

		std::string getType() override {
			return "Healer";
		}
	};

}