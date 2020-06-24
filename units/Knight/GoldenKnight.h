#pragma once

#include "../Friendly.h"

namespace UNITS {
	class GoldenKnight
		: public Friendly
	{
	protected:
		sf::Clock skillTimer;
		float attackUp;

	public:
		GoldenKnight(GameDataRef data, Lane* lane, int laneNumber) : Friendly(data, lane, laneNumber) { 
			skillTimer.restart();
		}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(180, 15, 100, 0.2, 2.0);

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

			Friendly::updateStateActions();

			if (skillIsActivated) {
				if (skillTimer.getElapsedTime().asSeconds() >= 5.0) {
					skillIsActivated = false;
					stats.attackSpeed /= 2;
				}
			}

		}

		void triggerStateChanges() override {
			Friendly::triggerStateChanges();

			if (!skillIsActivated) {
				if (stats.health <= stats.max_health * 0.3) {
					skillIsActivated = true;
					skill();
				}
			}
		}

		void skill() override {
			stats.attackSpeed *= 2;
			skillTimer.restart();
		}

		void update() override {
			Base::update();
		}

		std::string getType() override {
			return "Knight";
		}
	};
}