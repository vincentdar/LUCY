#include "../UI_Button.h"

#include "../../utils/Utils.h"

namespace GUI {

	void UI_Button::update(sf::RenderWindow& window)
	{
		if (currentState == DISABLED) {
			if (usingColor) {
				this->bounds.setFillColor(disabled);
			}
			else {
				this->bounds.setTexture(disabled_texture);
			}
			return;
		}
		else {
			if (usingColor) {
				this->bounds.setFillColor(main_color);
			}
			else {
				this->bounds.setTexture(main_texture);
			}
		}

		if (UTILS.isMouseOver(bounds.getPosition(), bounds.getSize().x, bounds.getSize().y, window)) {
			currentState = ISHOVERED;
			onHovered();
			if (usingColor) {
				this->bounds.setFillColor(hovered_color);
			}
			else {
				this->bounds.setTexture(hovered_texture);
			}
		}

		if (currentState == ISHOVERED && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			currentState = ISPRESSED;
			onPressed();
			if (usingColor) {
				this->bounds.setFillColor(pressed);
			}
			else {
				this->bounds.setTexture(pressed_texture);
			}
		}
	}

	void UI_Button::draw(sf::RenderTarget& target)
	{
		target.draw(bounds);
	}

	void UI_Button::setColor(sf::Color main, sf::Color secondary, sf::Color disabled, sf::Color pressed, sf::Color hovered)
	{
		usingColor = true;
	
		this->main_color	= main;
		this->hovered_color = hovered == sf::Color() ? main : hovered;
		this->secondary		= secondary == sf::Color() ? main : secondary;
		this->pressed		= pressed == sf::Color() ? main : pressed;
		this->disabled		= disabled == sf::Color() ? main : disabled;
	}
	void UI_Button::setTexture(sf::Texture * main_texture, sf::Texture * hovered_texture, sf::Texture * secondary_texture, sf::Texture * pressed_texture, sf::Texture * disabled_texture)
	{
		usingColor = false;
		this->main_texture		= main_texture;
		// Kalau nullptr, maka dapatnya main_texture;
		this->hovered_texture	= hovered_texture == nullptr ? main_texture : hovered_texture;
		this->secondary_texture	= secondary_texture == nullptr ? main_texture : secondary_texture;
		this->pressed_texture	= pressed_texture == nullptr ? main_texture : pressed_texture;;
		this->disabled_texture	= disabled_texture == nullptr ? main_texture : disabled_texture;
	}

}
