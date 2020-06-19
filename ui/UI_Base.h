#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Utils.h"

namespace UI {

	enum UI_Type {
		CONTAINER, BUTTON, TEXTFIELD, BOARD, ALERT
	};

	enum UI_Origin {
		TOPLEFT, CENTERED, CUSTOM
	};

	class Base
	{
	protected:
		UI_Origin origin;

		sf::RectangleShape base_shape;

		// Untuk menggerakkan UI biar smooth
		sf::Vector2f		move_target;
		sf::Clock			timer;
		float				move_duration;
		bool				isTranslating;

		sf::Texture*		main_texture;
		sf::Color			main_color;

	public:
		Base() {
			this->main_texture = nullptr;
			this->main_color = sf::Color::White;
			this->isTranslating = false;
			this->origin = TOPLEFT;
		}

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

		// Setup main color, main texture.
		virtual void setColor(sf::Color main) {
			main_color = main;

			base_shape.setFillColor(main_color);
		}

		virtual void setTexture(sf::Texture* texture) {
			main_texture = texture;

			base_shape.setTexture(texture);
		}

		void translate(sf::Vector2f target, float seconds) {
			isTranslating = true;
			move_target = target;
			move_duration = seconds;
		}

		// Handle input utk hal-hal yang perlu pakai event.
		virtual void handleInput(sf::Event& event, sf::RenderWindow& window) {}

		virtual void update(sf::RenderWindow& window) {
			if (isTranslating) {

				float time_percentage = UTILS.getValueFromRange(0, move_duration, 0, 1, timer.getElapsedTime().asSeconds());

				sf::Vector2f lerpedVec = UTILS.lerp(base_shape.getPosition(), move_target, time_percentage);

				base_shape.setPosition(lerpedVec);

				if (base_shape.getPosition() == move_target) {
					isTranslating = false;
				}
			}

		}

		// PAM
		void setPosition(sf::Vector2f position) {
			base_shape.setPosition(position);
		}

		void setSize(sf::Vector2f size) {
			base_shape.setSize(size);
		}

		sf::Vector2f getPosition() { return base_shape.getPosition(); }

		sf::Vector2f getSize() { return base_shape.getSize(); }
	};

}