#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace GUI {

	enum UI_Type {
		UI_BUTTON = 0, UI_TEXTBOX
	};

	class UI_Base
	{
	private:
		static unsigned int static_ID;

	protected:
		unsigned int id;

	public:
		UI_Base() {
			// Ketika object BaseUI dibuat, maka gui_generate_id akan mengenerate id baru,
			//  dimana id tsb akan dimiliki scr unik oleh tiap gui component.
			static_ID++;
			id = static_ID;
		}

		virtual ~UI_Base() {}

		unsigned int getID() { return id; }

		virtual void update(sf::RenderWindow& window) = 0;
		virtual void draw(sf::RenderTarget& target) = 0;

		virtual UI_Type getType() = 0;
	};

}