#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilKnight : public Enemies {
	private:
		sf::Clock gracePeriod;

	public:
		EvilKnight(GameDataRef data, Lane* lane, int laneNumber, Wall* wall) : Enemies(data, lane, laneNumber, wall) {}

		void setup(sf::Vector2f position) override {
			Base::setUnitStats(200, 150, 100, 0.5, 1.2);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("EKnight"),
				sf::IntRect(0, 52 * 2, 86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("EKnight"),
				sf::IntRect(0, 52 * 1, 86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("EKnight"),
				sf::IntRect(0, 52 * 0, 86, 52),
				sf::Vector2i(86, 0), 0.2, 2, true, false
			);
			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(IDLE);
		}

		void update() {
			Base::update();
			if (state == MOVE)
				charSprite.move(-1, 0);
		}

		void updateStateActions() override {
			if (state == ATTACK) {
				if (clock.getElapsedTime().asSeconds() >= 2.0) {
					this->setState(MOVE);
					clock.restart();
				}
			}
			else if (state == IDLE)
			{
				if (gracePeriod.getElapsedTime().asSeconds() >= 5.0f)
					this->setState(MOVE);
			}
		}

		void triggerStateChanges() override {
			Enemies::triggerStateChanges();

			if (!skillIsActivated) {
			}
		}

		void skill() override {
			printf("EVIL KNIGHT SKILL USED\n");
		}
	};
}