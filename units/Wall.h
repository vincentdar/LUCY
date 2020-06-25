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

public:
	Wall(LUCY::GameDataRef data) {
		isHit = false;
		health = 2000;
		wallSprite.setTexture(*data->assets.GetTexturePtr("Wall"));

		wallSprite.setPosition(-50, 0);

		sf::Vector2f f = UTILS::getScaleToSize(*data->assets.GetTexturePtr("Wall"), sf::Vector2f(100, data->window.getSize().y - BOTTOM_UI_HEIGHT));

		wallSprite.scale(f);
	}

	float getHealth() { return health; }

	void takeDamage(float damage) {
		isHit = true;
		health -= damage;
	}

	void draw(sf::RenderTarget& target) {
		if (isHit) {
			shader.loadFromFile("res/shader/hitflash.shader", sf::Shader::Fragment);
			target.draw(wallSprite, &shader);
		}
		else {
			target.draw(wallSprite);
		}
	}
};