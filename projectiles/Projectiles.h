#pragma once

#include "SFML/Graphics.hpp"

class Projectile
{
private:
	float speed;
	sf::Sprite sprite;
	sf::Vector2f pointOfDetection;

public:
	Projectile();

	void update();
	void draw();


};