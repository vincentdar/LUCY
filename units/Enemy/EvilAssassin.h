#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilAssassin : public Enemies {
	private:
		float initialDamage;

	public:
		EvilAssassin(GameDataRef data, Lane* lane, int laneNumber) : Enemies(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) override {
			
			Base::setUnitStats(50, 30, 100, 1, 2.0);

			animator.bindSprite(&charSprite);

			animator.addAnimationState(
				"Idle",
				data->assets.GetTexturePtr("Assassin_Red"),
				sf::IntRect(54 * 3, 36 * 0, 54, 36),
				sf::Vector2i(54, 0), 0.2, 2, true, true
			);

			animator.addAnimationState(
				"Move",
				data->assets.GetTexturePtr("Assassin_Red"),
				sf::IntRect(0, 36 * 0, 54, 36),
				sf::Vector2i(54, 0), 0.2, 2, true, false
			);

			animator.addAnimationState(
				"Attack",
				data->assets.GetTexturePtr("Assassin_Red"),
				sf::IntRect(0, 36 * 2, 54, 36),
				sf::Vector2i(54, 0), 0.4, 5, false, false
			);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(MOVE);

			// Custom skill setup
			shader.loadFromFile("res/shader/invisible.shader", sf::Shader::Fragment);
			skillIsActivated = true;

			stats.normalDamage *= 3;

			Enemies::setup(position);
		}

		void update() {
			Base::update();
			if (state == MOVE) {
				charSprite.move(-1 * stats.movementSpeed, 0);
			}
		}

		void processStateChanges() override {
			Base::processStateChanges();

			if (skillIsActivated)
				shader.loadFromFile("res/shader/invisible.shader", sf::Shader::Fragment);
		}

		void draw(sf::RenderTarget& target) override {
			if (isHit) {
				// Override existing shader
				shader.loadFromFile("res/shader/hitflash.shader", sf::Shader::Fragment);
				isHit = false;
				target.draw(charSprite, &shader);
				return;
			}

			if (skillIsActivated) {
				target.draw(charSprite, &shader);
			}
			else {
				target.draw(charSprite);
			}

			target.draw(base);
			target.draw(bar);
		}

		void skill() {}

		void updateStateActions() override
		{
			if (state == ATTACK) {
				
				if (clock.getElapsedTime().asSeconds() >= stats.attackSpeed) {
					this->setState(MOVE);
					if (targetedEntity != nullptr) {
						targetedEntity->takeDamage(stats.normalDamage);
						std::cout << stats.normalDamage << std::endl;
						targetedEntity = nullptr;
					}
					clock.restart();

					if (skillIsActivated) {
						skillIsActivated = false;
						stats.normalDamage /= 3;
					}
				}

			}
		}
		
	};
}