#include "UI_Textfield.h"

namespace UI 
{
	Textfield::Textfield()
	{
		characterSize = 20;
		this->allowSpaces = true;
		this->fieldIsSelected = false;
		this->maximumCharacters = 100;
		this->enteredText = "";
		init();
	}

	void Textfield::init()
	{
		this->characterSize = characterSize;

		this->displayedText.setString(enteredText);

		this->displayedText.setPosition(
			base_shape.getPosition()
		);
	}

	void Textfield::draw(sf::RenderTarget & target)
	{
		target.draw(base_shape);
		target.draw(displayedText);
	}

	void Textfield::setup(sf::Font * font, const std::string & placeholder, sf::Color fillColor)
	{
		this->enteredText = placeholder;
		this->textFont = font;

		this->displayedText.setFont(*font);
		this->displayedText.setFillColor(fillColor);
	}

	void Textfield::setSelected(bool selected)
	{
		this->fieldIsSelected = selected;
	}

	void Textfield::update(sf::RenderWindow & window)
	{
		Base::update(window);

		if (fieldIsSelected)
			displayedText.setString(enteredText + "_");
		else 
			displayedText.setString(enteredText);

		if (origin == CENTERED) {
			this->displayedText.setPosition(
				base_shape.getPosition().x - UTILS.getTextWidth(displayedText) / 2.0,
				base_shape.getPosition().y - displayedText.getGlobalBounds().height / 2.0
			);
		}
		else {
			this->displayedText.setPosition(
				base_shape.getPosition().x + base_shape.getSize().x / 2.0 - UTILS.getTextWidth(displayedText) / 2.0,
				base_shape.getPosition().y + 20
			);
		}
	}

	void Textfield::handleInput(sf::Event & event)
	{
		if (!fieldIsSelected) {
			return;
		}

		if (event.type == sf::Event::KeyPressed) {
			sf::Keyboard::Key charPressed = event.key.code;

			if (enteredText.length() > maximumCharacters) {
				return;
			}

			// Translate to ASCII
			if (charPressed >= sf::Keyboard::A && 
				charPressed <= sf::Keyboard::Z) {

				// Check apakah huruf besar / kecil.
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
					enteredText += (charPressed + 65);
				}
				else {
					enteredText += (charPressed + 97);
				}
			}
			else if (charPressed >= sf::Keyboard::Num0 && charPressed <= sf::Keyboard::Num9) {
				enteredText += (charPressed + 22);
			}
			else if (charPressed == sf::Keyboard::Space && allowSpaces) {
				enteredText += ' ';
			}
			else if (charPressed == sf::Keyboard::Dash) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
					enteredText += '-';
				}
				else {
					enteredText += '_';
				}
			}
			else if (charPressed == sf::Keyboard::Enter) {
				isSubmitted = true;
				submittedText = enteredText;
			}
			else if (charPressed == sf::Keyboard::BackSpace) {
				if (!enteredText.empty())
					enteredText.pop_back();
			}
			else if (charPressed == sf::Keyboard::Escape) {
				fieldIsSelected = false;
			}
		}
	}
	void Textfield::setAllowSpaces(bool allowSpaces)
	{
		this->allowSpaces = allowSpaces;
	}

	void Textfield::setMaxCharacters(int max)
	{
		this->maximumCharacters = max;
	}

	void Textfield::setCharacterSize(int size)
	{
		characterSize = size;
		displayedText.setCharacterSize(characterSize);
	}

	void Textfield::reset()
	{
		submittedText.clear();
		isSubmitted = false;
	}
}