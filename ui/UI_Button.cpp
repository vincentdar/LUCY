#include "UI_Button.h"

#include "../Utils.h"

namespace UI {

	void Button::init() {
		
	}

	void Button::handleInput(sf::Event & event, sf::RenderWindow & window)
	{
		if (!enabled) return;

		if (isHovered(event, window)) {
			hovered = true;
		}
		else {
			hovered = false;
		}

		if (isClicked(event, window)) {
			clicked = true;
		}
		else {
			clicked = false;
		}
	}

	void Button::update(sf::RenderWindow& window)
	{
		// Check apakah button disabled
		if (!enabled) {
			if (usingColor) {
				this->base_shape.setFillColor(disabled);
			}
			else {
				this->base_shape.setTexture(disabled_texture);
			}
			return;
		}

		if (usingColor) {
			if (!usingSecondary)
				this->base_shape.setFillColor(main_color);
			else
				this->base_shape.setFillColor(secondary);
		}
		else {
			if (!usingSecondary)
				this->base_shape.setTexture(main_texture);
			else
				this->base_shape.setTexture(secondary_texture);
		}

		// Check apakah button hovered
		if (hovered) {
			if (usingColor) {
				this->base_shape.setFillColor(hovered_color);
			}
			else {
				this->base_shape.setTexture(hovered_texture);
			}
		}
		 
		if (clicked) 
		{
			if (usingColor) {
				this->base_shape.setFillColor(pressed);
			}
			else {
				this->base_shape.setTexture(pressed_texture);
			}
			return;
		}
	}

	bool Button::isClicked(sf::Event& event, sf::RenderWindow& window)
	{
		return (UTILS.isMouseOver(
			sf::Vector2f(base_shape.getGlobalBounds().left, base_shape.getGlobalBounds().top),
			base_shape.getSize().x, base_shape.getSize().y, window) && event.type == sf::Event::MouseButtonPressed);
	}

	bool Button::isHovered(sf::Event& event, sf::RenderWindow& window)
	{
		return UTILS.isMouseOver(
			sf::Vector2f(base_shape.getGlobalBounds().left, base_shape.getGlobalBounds().top),
			base_shape.getSize().x, base_shape.getSize().y, window);
	}

	void Button::draw(sf::RenderTarget& target)
	{
		target.draw(base_shape);
	}

	void Button::setColor(sf::Color main, sf::Color pressed, sf::Color hovered, sf::Color disabled, sf::Color secondary)
	{
		usingColor = true;

		this->main_color = main;
		this->pressed = pressed;
		this->hovered_color = hovered;
		this->disabled = disabled;
		this->secondary = secondary;
	}
	void Button::setTexture(sf::Texture* main_texture, sf::Texture* pressed_texture, sf::Texture* hovered_texture, sf::Texture* disabled_texture, sf::Texture* secondary_texture)
	{
		usingColor = false;
		this->main_texture = main_texture;

		// Kalau nullptr, maka dapatnya main_texture;
		this->hovered_texture = hovered_texture == nullptr ? main_texture : hovered_texture;
		this->secondary_texture = secondary_texture == nullptr ? main_texture : secondary_texture;
		this->pressed_texture = pressed_texture == nullptr ? main_texture : pressed_texture;;
		this->disabled_texture = disabled_texture == nullptr ? main_texture : disabled_texture;
	}

}
