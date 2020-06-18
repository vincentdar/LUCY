#pragma once

#include "UI_Base.h"

namespace UI {

	enum Button_State {
		ENABLED, ISHOVERED, DISABLED, ISPRESSED
	};

	class Button
		: public Base
	{
	protected:

		Button_State currentState = ENABLED;

		// Bisa color atau texture. Tergantung yg di set terakhir
		bool usingColor = false;
		
		sf::Color			main_color;
		sf::Color			hovered_color;
		sf::Color			disabled;
		sf::Color			secondary;
		sf::Color			pressed;
		
		sf::Texture*		hovered_texture;
		sf::Texture*		secondary_texture;
		sf::Texture*		pressed_texture;
		sf::Texture*		disabled_texture;

		bool clicked = false;
		bool hovered = false;

	public:
		Button() {}

		//Untuk buat perubahan setTexture SetColor FIX 
		void init() override;

		// Update kondisi.
		void update(sf::RenderWindow &window);

		bool isClicked(sf::Event& event, sf::RenderWindow& window);
		bool isHovered();
	
		// Manual draw: object.draw();
		void draw(sf::RenderTarget &target);

		void setColor(
				sf::Color main,
				sf::Color pressed = sf::Color(-1, -1, -1, -1), 
				sf::Color hovered = sf::Color(-1, -1, -1, -1),
				sf::Color disabled = sf::Color(-1, -1, -1, -1),
				sf::Color secondary = sf::Color(-1, -1, -1, -1)
		);

		void setTexture(
				sf::Texture*	main_texture,
				sf::Texture*	pressed_texture = nullptr,
				sf::Texture*	hovered_texture = nullptr,
				sf::Texture*	disabled_texture = nullptr,
				sf::Texture*	secondary_texture = nullptr
		);

		UI_Type getType() override {
			return UI_Type::BUTTON;
		}
	};
}