#pragma once

#include "UI_Base.h"

namespace UI 
{
	class UI_Board
		: public UI_Base
	{
	private:
		// UI_Board isinya: Content, terima click event untuk close.

		sf::Text head;
		sf::Text body;

		std::string headText;
		std::string bodyText;

		sf::Font* font_head;
		sf::Font* font;

		float duration;

		// Apabila duration < 0 => tidak pakai timer

		sf::Clock timer;

		bool isDisplayed = false;

	public:
		UI_Board() {}
		UI_Board(sf::Font* font, sf::Font* font_head, const std::string& head, const std::string& body, float duration = -1);

		void setup(sf::Font* font, sf::Font* font_head, const std::string& head, const std::string& body, float duration = -1);

		void display();

		void hide();

		bool getIsDisplayed() { return isDisplayed; }

		void setPosition(sf::Vector2f position);

		void update(sf::RenderWindow& window) override;
		void draw(sf::RenderTarget& target) override;

		void setTextPosition(sf::Vector2f position);
		
		void setSize(sf::Vector2f size) {
			this->base_shape.setSize(size);
		}

		void setColor(sf::Color col) {
			this->base_shape.setFillColor(col);
		}

		UI_Type getType() override {
			return UI_Type::BOARD;
		}
	};
}