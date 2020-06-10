#include "UI_Button.h"

#include "../Utils.h"

namespace UI {

	void UI_Button::update(sf::RenderWindow& window)
	{
		UI::UI_Base::update(window);

		if (currentState == DISABLED) {
			if (usingColor) {
				this->base_shape.setFillColor(disabled);
			}
			else {
				this->base_shape.setTexture(disabled_texture);
			}
			return;
		}
		else {
			if (usingColor) {
				this->base_shape.setFillColor(main_color);
			}
			else {
				this->base_shape.setTexture(main_texture);
			}
		}

		if (UTILS.isMouseOver(base_shape.getPosition(), base_shape.getSize().x, base_shape.getSize().y, window)) {
			currentState = ISHOVERED;

			if (usingColor) {
				this->base_shape.setFillColor(hovered_color);
				hovered = true;
			}
			else {
				this->base_shape.setTexture(hovered_texture);
				hovered = false;
			}
		}

		if (currentState == ISHOVERED && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			currentState = ISPRESSED;

			if (usingColor) {
				this->base_shape.setFillColor(pressed);
				clicked = true;
			}
			else {
				this->base_shape.setTexture(pressed_texture);
				clicked = false;
			}
		}
	}

	void UI_Button::draw(sf::RenderTarget& target)
	{
		target.draw(base_shape);
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
