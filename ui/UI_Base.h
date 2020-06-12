#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Utils.h"

// TODO: Move base shape to position in a certain timeframe

namespace UI {

	enum UI_Type {
		BUTTON, TEXTBOX, BOARD, CONFIRM, ALERT
	};

	enum UI_Origin {
		TOPLEFT, CENTERED
	};

	class Base
	{
	private:
		// Perlu?
		static unsigned int static_ID;

	protected:
		unsigned int id;

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
			// Ketika object BaseUI dibuat, maka gui_generate_id akan mengenerate id baru,
			//  dimana id tsb akan dimiliki scr unik oleh tiap gui component.
			static_ID++;
			id = static_ID;
		}

		void setBounds(sf::Vector2f bounds) {
			this->base_shape.setSize(bounds);
		}

		sf::Vector2f getBounds() { return this->base_shape.getSize(); }

		void move(sf::Vector2f moveTarget, float time_total, float smoothness) {
			//move_start = base_shape.getPosition();
			//move_difference = moveTarget - base_shape.getPosition();

			//// Move yang dilakukan per step
			//move_difference = sf::Vector2f(move_difference.x / time_total, move_difference.y / time_total);

			//isTranslating = true;

			//printf("%d", isTranslating);

			move_target = moveTarget;
		}

		void setOrigin(UI_Origin origin) {
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

		virtual ~Base() {}

		unsigned int getID() { return id; }

		virtual void init() = 0;

		virtual void draw(sf::RenderTarget& target) = 0;
		// Jangan lupa panggil di update di child classnya!!!! -- important
		virtual void update(sf::RenderWindow& window) {
			if (isTranslating) {

				sf::Vector2f targetPos = UTILS.lerp(base_shape.getPosition(), move_target, 0.5);
				base_shape.move(targetPos);

				if (base_shape.getPosition() == move_target) {
					isTranslating = false;
				}
			}
		}

		virtual UI_Type getType() = 0;

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