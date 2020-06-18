#pragma once

#include "UI_Base.h"

namespace UI 
{
	class Textfield
		: public Base
	{
	private:
		std::string		enteredText;
		sf::Text		displayedText;
		sf::Font*		textFont;

		bool			fieldIsSelected;
		bool			allowSpaces;
		int				characterSize;
		int				maximumCharacters;

		bool			isSubmitted;
		std::string		submittedText;

	public:
		Textfield();

		void init() override;
		void draw(sf::RenderTarget& target) override;
		UI_Type getType() override { return TEXTFIELD; }

		void setup(sf::Font* font, const std::string& placeholder, sf::Color fillColor);

		void setSelected(bool selected);
		bool getSelected() { return fieldIsSelected; }

		void update(sf::RenderWindow& window) override;

		void handleInput(sf::Event& event, sf::RenderWindow& window) override;

		void setAllowSpaces(bool allowSpaces);
		void setMaxCharacters(int max);
		void setCharacterSize(int size);

		std::string getSubmittedText() {
			if (!isSubmitted) { return ""; }
			return submittedText;
		}

		bool getIsSubmitted() { return isSubmitted; }
		void reset();
	};
}