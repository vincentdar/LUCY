#pragma once

#include "UI_Base.h"

/*
	Urutan setup:
	1. Size
	2. Origin, texture
	3. Position (keseluruhan)
	4. Position head sm body
*/

namespace UI 
{
	class Board
		: public Base
	{
	private:
		// Board isinya: Content, terima click event untuk close.

		sf::Text head;
		sf::Text body;

		std::string headText;
		std::string bodyText;

		sf::Font* font_head;
		sf::Font* font;

		// Relative
		sf::Vector2f headPos;
		sf::Vector2f bodyPos;

		float duration;

		// Apabila duration < 0 => tidak pakai timer

		sf::Clock timer;

		bool isDisplayed = false;

	public:
		Board();
		Board(sf::Font* font, sf::Font* font_head, const std::string& head, const std::string& body, float duration = -1);

		void setup(sf::Font* font, sf::Font* font_head, const std::string& head, const std::string& body, float duration = -1);

		void display();

		void hide();

		void updateTextPosition();

		bool getIsDisplayed() { return isDisplayed; }

		void setPosition(sf::Vector2f position);

		void update(sf::RenderWindow& window) override;
		void draw(sf::RenderTarget& target) override;

		void setTextPositionBody(sf::Vector2f position);
		void setTextPositionHead(sf::Vector2f position);
		void setHeadToCenter() {
			setTextPositionHead (sf::Vector2f(
				base_shape.getLocalBounds().width / 2.0 - UTILS.getTextWidth(this->head) / 2.0,
				base_shape.getLocalBounds().height / 7.0
			));
		}

		// For full control!!
		sf::Text& getHeadText() { return head; }
		sf::Text& getBodyText() { return body; }
		
		void setSize(sf::Vector2f size) {
			this->base_shape.setSize(size);
		}

		void setColor(sf::Color col) {
			this->base_shape.setFillColor(col);
		}

		UI_Type getType() override {
			return UI_Type::BOARD;
		}

		void setCharacterSizeBody(int s) {
			this->body.setCharacterSize(s);
		}

		void setCharacterSizeHead(int s) {
			this->head.setCharacterSize(s);
		}
	};
}