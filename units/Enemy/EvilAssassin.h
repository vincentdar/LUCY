#pragma once

#include "../Enemies.h"

namespace UNITS {
	class EvilAssassin : public Enemies {
	private:
		float initialDamage;

	public:
		EvilAssassin(GameDataRef data, Lane* lane, int laneNumber) : Enemies(data, lane, laneNumber) {}

		void setup(sf::Vector2f position) override {
			
			Base::setUnitStats(50, 40, 50);

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
				sf::Vector2i(54, 0), 0.2, 5, false, false
			);

			charSprite.setScale(2, 2);
			charSprite.setPosition(position);
			setState(MOVE);

			// Custom skill setup
			shader.loadFromFile("res/shader/invisible.shader", sf::Shader::Fragment);
			skillIsActivated = true;

			initialDamage = stats.normalDamage * 10;
		}

		void update() {
			Base::update();
			if (state == MOVE) {
				charSprite.move(-1, 0);
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
				//charSprite.setColor(sf::Color::Black);
				isHit = false;
				target.draw(charSprite, &shader);
				return;
			}

			if (skillIsActivated) {
				target.draw(charSprite, &shader);
			}
			else {
				target.draw(charSprite);
				charSprite.setColor(sf::Color::White);
			}

			target.draw(base);
			target.draw(bar);
		}

		void skill() {}

		void updateStateActions() override
		{
			if (state == ATTACK) {
				if (skillIsActivated) {
					skillIsActivated = false;
					stats.normalDamage /= 10;
				}
				if (clock.getElapsedTime().asSeconds() >= 2.0) {
					this->setState(MOVE);
					clock.restart();
				}
			}
		}
		
	};
}