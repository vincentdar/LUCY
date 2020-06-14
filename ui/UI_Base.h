#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Utils.h"

// TODO: Move base shape to position in a certain timeframe

namespace UI {

	enum UI_Type {
		BUTTON, TEXTFIELD, BOARD, CONFIRM, ALERT
	};

	enum UI_Origin {
		TOPLEFT, CENTERED
	};

	class Base
	{
	protected:
		UI_Origin origin;

		sf::RectangleShape base_shape;

		// Untuk menggerakkan UI biar smooth
		sf::Vector2f		move_difference;
		sf::Vector2f		move_target;
		sf::Clock			move_timer;
		float				move_duration;
		bool				isTranslating;

		sf::Texture*		main_texture;
		sf::Color			main_color;

		sf::RenderWindow*	window;

	public:
		Base() {
			main_texture = nullptr;
			main_color = sf::Color::White;
			
			// Default origin: CENTERED
			this->setOrigin(CENTERED);
		}

		void setBounds(sf::Vector2f bounds) {
			this->base_shape.setSize(bounds);
		}

		sf::Vector2f getBounds() { return this->base_shape.getSize(); }

		void setOrigin(UI_Origin origin) {
			this->origin = origin;
			switch (origin)
			{
			case UI::TOPLEFT:
				base_shape.setOrigin(0, 0);
				break;
			case UI::CENTERED:
				base_shape.setOrigin(
					base_shape.getLocalBounds().width / 2, 
					base_shape.getLocalBounds().height / 2);
				break;
			default:
				break;
			}
		}

		UI_Origin getOrigin() { return origin; }

		virtual ~Base() {}

		virtual void init() = 0;
		virtual void draw(sf::RenderTarget& target) = 0;
		virtual UI_Type getType() = 0;

		// Handle input utk hal-hal yang jalan di input.
		virtual void handleInput(sf::Event& event) {}

		virtual void update(sf::RenderWindow& window) {
			if (isTranslating) {

				sf::Vector2f targetPos = UTILS.lerp(base_shape.getPosition(), move_target, 0.5);
				base_shape.move(targetPos);

				if (base_shape.getPosition() == move_target) {
					isTranslating = false;
				}
			}
		}

		// Base functions
		void setPosition(sf::Vector2f position) {
			base_shape.setPosition(position);
		}

		sf::Vector2f getPosition() { return base_shape.getPosition(); }

		void setSize(sf::Vector2f size) {
			base_shape.setSize(size);
		}

		sf::Vector2f getSize() { return base_shape.getSize(); }

		virtual void setColor(sf::Color main) {
			main_color = main;

			base_shape.setFillColor(main_color);
		}

		virtual void setTexture(sf::Texture* texture) {
			main_texture = texture;

			base_shape.setTexture(texture);
		}
	};

}