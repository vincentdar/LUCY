#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

// Class singleton
// Penggunaan: 
//   Utils::get()->fungsi();

// Last edit: Matthew Sutanto 28/05/2020 => First

#define UTILS Utils::get()

class Utils
{
private:
	static Utils* instance;

public:
	Utils() {}

	// Copying is no-no;
	Utils(const Utils& utils) = delete;
	void operator=(const Utils& utils) = delete;

	static Utils& get() {
		if (instance == nullptr) {
			instance = new Utils();
		}
		return *instance;
	}

	bool isInBetween(float number, float min, float max) {
		return (number >= min && number <= max);
	}

	// Get mouse over
	bool isMouseOver(sf::Vector2f objPos, float width, float height, sf::RenderWindow& window) {
		return (isInBetween(sf::Mouse::getPosition(window).x, objPos.x, objPos.x + width) &&
			isInBetween(sf::Mouse::getPosition(window).y, objPos.y, objPos.y + height));
	}

	void normalizeVector2f(sf::Vector2f &range) {
		// Get vector length
		double vec_magnitude = sqrt(pow(range.x, 2) + pow(range.y, 2));

		range.x = float(range.x / vec_magnitude);
		range.y = float(range.y / vec_magnitude);
	}

	/*
		TODO : isInRange, isCollided.. etc
	*/

};