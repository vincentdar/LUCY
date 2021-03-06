#pragma once

#include "UI_Base.h"

namespace UI {

	class Button
		: public Base
	{
	protected:
		// Bisa color atau texture. Tergantung yg di set terakhir
		bool usingColor = false;

		sf::Color			pressed;
		sf::Color			hovered_color;
		sf::Color			disabled;
		sf::Color			secondary;
		
		sf::Texture*		pressed_texture;
		sf::Texture*		hovered_texture;
		sf::Texture*		disabled_texture;
		sf::Texture*		secondary_texture;

		sf::IntRect			currentTexRect;

		sf::Font*			font;
		sf::Text			text;

		// Button states
		bool clicked = false;
		bool hovered = false;
		bool enabled = true;
		bool usingSecondary = false;
		bool isOutlined = false;

	public:
		Button() {}

		//Untuk buat perubahan setTexture SetColor FIX 
		void init() override;
		void handleInput(sf::Event& event, sf::RenderWindow& window) override;

		void setText(std::string text);
		void setFont(sf::Font* font);

		void setOutline(float thickness, sf::Color color);

		// Update kondisi.
		void update(sf::RenderWindow &window);

		bool isClicked(sf::Event& event, sf::RenderWindow& window);
		bool isHovered(sf::Event& event, sf::RenderWindow& window);
	
		// Manual draw: object.draw();
		void draw(sf::RenderTarget &target);

		void setColor(
				sf::Color main,
				sf::Color pressed,
				sf::Color hovered, 
				sf::Color disabled,
				sf::Color secondary 
		);

		void setTexture(
				sf::Texture*	main_texture,
				sf::Texture*	pressed_texture = nullptr,
				sf::Texture*	hovered_texture = nullptr,
				sf::Texture*	disabled_texture = nullptr,
				sf::Texture*	secondary_texture = nullptr
		);

		void setTextureRect(sf::IntRect texRect) {
			currentTexRect = texRect;
			base_shape.setTextureRect(currentTexRect);
		}

		sf::IntRect getTextureRect() {
			return currentTexRect;
		}

		UI_Type getType() override {
			return UI_Type::BUTTON;
		}

		void setSecondary(bool isSecondary) {
			if (usingColor)
				usingSecondary = isSecondary;
		}

		void set(UI_Origin origin, sf::Vector2f size, sf::Texture* texture, sf::IntRect texRect) {
			setOrigin(origin);
			setSize(size);
			setTexture(texture);
			setTextureRect(texRect);
		}
	};
}