#pragma once

#include "UI_Base.h"

namespace LUCY {

	enum UI_Button_State {
		ENABLED, ISHOVERED, DISABLED, ISPRESSED
	};

	class UI_Button
		: public UI_Base
	{
	protected:

		UI_Button_State currentState = ENABLED;

		bool usingColor = false;

		/* 
			Color yg digunakan pada bounds, pada berbagai state buttonnya.
			-- Main color: Default warna button. Apabila warna lain tidak diset, fallback ke sini.
			-- Secondary: Opsional. Tidak dipanggil kecuali mau diset toggleable. Maka switch dari main color ke secondary color.
			-- Hovered : Ketika dihover (tapi tidak diclick. Kalau diclick ikut yg pressed)
			-- Pressed : Ketika mouse button 1 sedang ngeclick di button ini (ditahan)
		*/
		sf::Color			main_color;
		sf::Color			hovered_color;
		sf::Color			disabled;
		sf::Color			secondary;
		sf::Color			pressed;

		/*
			Sama spt color, tapi texture.
		*/
		sf::Texture*		main_texture;
		sf::Texture*		hovered_texture;
		sf::Texture*		secondary_texture;
		sf::Texture*		pressed_texture;
		sf::Texture*		disabled_texture;

		// Bounds adalah area dimana click dan hover didetect. Bisa invisible (sf::Color::Transparent di main_color)
		sf::RectangleShape	bounds;

	public:
		UI_Button(sf::Vector2f position = { 0, 0 }, sf::Vector2f size = { 0, 0 }) {}

		// Update kondisi.
		void update(sf::RenderWindow &window);
	
		// Manual draw: object.draw();
		void draw(sf::RenderTarget &target);

		// Fungsi yg dijalankan khusus ketika sedang diklik.
		virtual void onPressed() {}

		// Fungsi yg dijalankan khusus ketika sedang dihover. (tidak diclick)
		virtual void onHovered() {}

		void setPosition(sf::Vector2f position) {
			bounds.setPosition(position);
		}

		sf::Vector2f getPosition() { return bounds.getPosition(); }

		void setBounds(sf::Vector2f size) {
			bounds.setSize(size);
		}

		sf::Vector2f getBounds() { return bounds.getSize(); }

		void setColor(
				sf::Color main,
				sf::Color secondary = sf::Color(), 
				sf::Color disabled = sf::Color(), 
				sf::Color pressed = sf::Color(), 
				sf::Color hovered = sf::Color()
		);

		void setTexture(
				sf::Texture*	main_texture,
				sf::Texture*	hovered_texture = nullptr,
				sf::Texture*	secondary_texture = nullptr,
				sf::Texture*	pressed_texture = nullptr,
				sf::Texture*	disabled_texture = nullptr
		);
	};

}