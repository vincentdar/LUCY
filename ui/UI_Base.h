#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class UI_Shape 
{
	NONE = 0, RECT, CIRCLE, TEXTURE
};

namespace LUCY {

	class UI_Base :
		public sf::Transformable,
		public sf::Drawable
	{
	protected:
		sf::Sprite sprite;
		sf::Texture* texture;
		sf::Text text;
		sf::Font* font;

		int width, height;

	public:
		UI_Base(sf::Texture* texture, sf::Font* font, sf::String text = "");
		UI_Base(const UI_Base& base) = default;

		void setText(std::string text);
		void setFont(sf::Font *font);
		void setTexture(sf::Texture* texture);

		std::string getText();
		sf::Texture& getTexture();
		sf::Font& getFont();

		void draw(sf::RenderWindow* window);
	};
}