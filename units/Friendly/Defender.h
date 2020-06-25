#pragma once

#include "../Friendly.h"

namespace UNITS {
	class Defender :
		public Friendly
	{
	private:
		sf::Clock reagent;

	public:
		Defender(GameDataRef data, Lane* lanes, int laneCount) :Friendly(data, lanes, laneCount) {
			reagent.restart();

			unitCost = 175;
		}

		void setup(sf::Vector2f position) {

			Friendly::setUnitStats(350, 0, 0, 0, 0);
			animator.bindSprite(&charSprite);

			//36 x 42
			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Defender"),
				sf::IntRect(0, 42 * 0, 36, 42),
				sf::Vector2i(36, 0), 0.2, 5, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Defender"),
				sf::IntRect(0, 42 * 1, 36, 42),
				sf::Vector2i(36, 0), 0.2, 11, false, false
			);

			animator.addAnimationState(
				"GetHit",
				data->assets.GetTexturePtr("Defender"),
				sf::IntRect(0, 42 * 2, 36, 42),
				sf::Vector2i(36, 0), 0.2, 2, false, false);

			//Skills

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(IDLE);

			Friendly::setup(position);
		}

		void updateStateActions() override {

			if (skillIsActivated) {
				if (reagent.getElapsedTime().asSeconds() >= 10.0) {
					skillIsActivated = false;

					stats.max_health /= 2;
					if (stats.health > stats.max_health)
						stats.health = stats.max_health;
					reagent.restart();
				}
			}

		}

		void triggerStateChanges() override {

			if (!skillIsActivated) {
				if (reagent.getElapsedTime().asSeconds() >= 15) {
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
			stats.max_health *= 2;
			stats.health += stats.health * 1.5;

			if (stats.health > stats.max_health)
				stats.health = stats.max_health;

			reagent.restart();
			printf("DEFENDER USED SKILL\n");
		}

		// KEtika take damage maka play animationnya
		void takeDamage(float damage) override {
			isHit = true;
			animator.playAnimation("GetHit");
			stats.health -= damage;
			if (stats.health <= 0) {
				setState(DIE);
			}
		}

		std::string getType() override {
			return "Defender";
		}
	};
}
