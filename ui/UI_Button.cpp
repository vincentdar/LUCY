#include "UI_Button.h"

#include "../Utils.h"

namespace UI {

	void Button::init() {
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
	}

	void Button::setWindow(sf::RenderWindow& window)
	{
		this->window = &window;
	}

	void Button::update(sf::RenderWindow& window)
	{
		UI::Base::update(window);

		// Check apakah button disabled
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

		// Check apakah button hovered
		if (UTILS.isMouseOver(base_shape.getPosition(), base_shape.getSize().x, base_shape.getSize().y, window)) {
			currentState = ISHOVERED;

			if (usingColor) {
				this->base_shape.setFillColor(hovered_color);
			}
			else {
				this->base_shape.setTexture(hovered_texture);
			}

			hovered = true;
		}
	}

	bool Button::isClicked(sf::Event& event)
	{
		// Check apakah button diclick
		if (UTILS.isMouseOver(base_shape.getPosition(), base_shape.getSize().x, base_shape.getSize().y, *window) && event.type == sf::Event::MouseButtonReleased) {

			if (usingColor) {
				this->base_shape.setFillColor(pressed);
			}
			else {
				this->base_shape.setTexture(pressed_texture);
			}

			return true;
		}
		return false;
	}

	bool Button::isHovered()
	{
		return hovered;
	}

	void Button::draw(sf::RenderTarget& target)
	{
		target.draw(base_shape);
	}

	void Button::setColor(sf::Color main, sf::Color secondary, sf::Color disabled, sf::Color pressed, sf::Color hovered)
	{
		usingColor = true;

		this->main_color = main;
		this->hovered_color = hovered == sf::Color() ? main : hovered;
		this->secondary = secondary == sf::Color() ? main : secondary;
		this->pressed = pressed == sf::Color() ? main : pressed;
		this->disabled = disabled == sf::Color() ? main : disabled;
	}
	void Button::setTexture(sf::Texture * main_texture, sf::Texture * hovered_texture, sf::Texture * secondary_texture, sf::Texture * pressed_texture, sf::Texture * disabled_texture)
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
