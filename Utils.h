#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace UTILS {
	// Check number ada diantara min dan max
	bool isInBetween(float number, float min, float max);

	// Get mouse over
	bool isMouseOver(sf::Vector2f objPos, float width, float height, sf::RenderWindow& window);

	// Normalize vector2f (not used)
	void normalizeVector2f(sf::Vector2f &range);

	// Menghapus space di dpn string
	void clearSpacesInFront(std::string& str);

	// Utk convert posisi di screen jadi lane keberapa
	int screenPositionToLaneMap(sf::Vector2i position, int start, int laneCount, int height);

	// Untuk ubah string ke lowercase
	std::string getLowercase(std::string str);

	// Cari factor utk scale sprite ke size tertentu
	sf::Vector2f getScaleToSize(sf::Texture& tex, const sf::Vector2f& target);

	// Rumus lerp
	sf::Vector2f lerp(sf::Vector2f position, sf::Vector2f target, float time);

	// Cari panjang text
	float getTextWidth(sf::Text& text);

	// Cari value oldVal dari range yang berbeda
	float getValueFromRange(float oldMin, float oldMax, float newMin, float newMax, float oldVal);
}