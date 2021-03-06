#include "Utils.h"

namespace UTILS
{
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

	void clearSpacesInFront(std::string& str) {
		while (str[0] == ' ' || str[0] == '\t') {
			str.erase(str.begin());
		}
	}

	int screenPositionToLaneMap(sf::Vector2i position, int start, int laneCount, int height) {
		if (position.y < start || position.y >= start + laneCount * height) {
			return -1;
		}
		else {
			return (position.y - start) / (height - start);
		}
	}

	std::string getLowercase(std::string str) {
		for (int i = 0; i < str.length(); i++) {
			str[i] = tolower(str[i]);
		}

		return str;
	}

	sf::Vector2f getScaleToSize(sf::Texture& tex, const sf::Vector2f& target) {
		return
		{
			target.x / tex.getSize().x,
			target.y / tex.getSize().y
		};
	}

	sf::Vector2f lerp(sf::Vector2f position, sf::Vector2f target, float time)
	{
		return (position + (target - position) * time);
	}

	float getTextWidth(sf::Text& text)
	{
		return text.findCharacterPos(
			text.getString().getSize()
		).x - text.getGlobalBounds().left;
	}

	float getValueFromRange(float oldMin, float oldMax, float newMin, float newMax, float oldVal) {
		float oldRange = oldMax - oldMin;
		float newRange = newMax - newMin;

		if (oldRange == 0) {
			return newMin;
		}

		return (oldVal - oldMin) * newRange / oldRange + newMin;
	}
}