#include "../UI_Base.h"

namespace LUCY {

	UI_Base::UI_Base(sf::Texture * texture, sf::Font * font, sf::String text)
		: texture(texture), font(font)
	{
		this->text.setString(text);
		this->text.setFont(*this->font);
		this->sprite.setTexture(*this->texture);
	}

	void UI_Base::setText(std::string text)
	{
		this->text.setString(text);
	}

	void UI_Base::setFont(sf::Font * font)
	{
		this->font = font;
		this->text.setFont(*this->font);
	}

	void UI_Base::setTexture(sf::Texture * texture)
	{
		this->sprite.setTexture(*texture);
	}

	std::string UI_Base::getText()
	{
		return std::string();
	}

	sf::Texture & UI_Base::getTexture()
	{
		return *texture;
	}

	sf::Font & UI_Base::getFont()
	{
		return *font;
	}

	void UI_Base::draw(sf::RenderWindow * window)
	{
	}
}
