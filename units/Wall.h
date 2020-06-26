#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.h"

class Wall 
{
private:
	float health;
	bool isHit;
	sf::Sprite wallSprite;

	sf::Shader shader;

	sf::RectangleShape wallHPBar;
	sf::RectangleShape wallHPBarBase;

	float maxHealth;

public:
	Wall(LUCY::GameDataRef data) {

		maxHealth = data->window.getSize().y - BOTTOM_UI_HEIGHT;

		isHit = false;
		health = 2000;
		wallSprite.setTexture(*data->assets.GetTexturePtr("Wall"));

		wallSprite.setPosition(-50, 0);

		sf::Vector2f f = UTILS::getScaleToSize(*data->assets.GetTexturePtr("Wall"), sf::Vector2f(100, data->window.getSize().y - BOTTOM_UI_HEIGHT));

		wallSprite.scale(f);

		wallHPBar.setPosition(0, 0);
		wallHPBarBase.setPosition(0, 0);

		wallHPBar.setOrigin(wallHPBar.getLocalBounds().left, wallHPBar.getLocalBounds().height);

		wallHPBarBase.setSize(sf::Vector2f(15, 0));
		wallHPBar.setSize(sf::Vector2f(15, maxHealth));

		wallHPBar.setFillColor(sf::Color::Green);
		wallHPBarBase.setFillColor(sf::Color::Black);
	}

	float getHealth() { return health; }

	void takeDamage(float damage) {
		isHit = true;
		health -= damage;
	}

	void update() {
		float health_percentage = UTILS::getValueFromRange(0, 2000, 0, 1, health);
		wallHPBarBase.setSize(sf::Vector2f(15, (1 - health_percentage) * maxHealth));
	}

	void draw(sf::RenderTarget& target) {
		if (isHit) {
			shader.loadFromFile("res/shader/hitflash.shader", sf::Shader::Fragment);
			target.draw(wallSprite, &shader);
			isHit = false;
		}
		else {
			target.draw(wallSprite);
		}

		target.draw(wallHPBar);
		target.draw(wallHPBarBase);
	}

	float getDetectionPoint() {
		return wallSprite.getGlobalBounds().left + wallSprite.getGlobalBounds().width;
	}
};