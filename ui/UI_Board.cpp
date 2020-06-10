#include "UI_Board.h"

UI::UI_Board::UI_Board(sf::Font* font_head, sf::Font* font, const std::string& head, const std::string& body, float duration)
{
	setup(font, font_head, head, body, duration);
}

void UI::UI_Board::setup(sf::Font* font, sf::Font* font_head, const std::string& head, const std::string& body, float duration)
{
	headText = head;
	bodyText = body;
	this->duration = duration;

	this->font = font;
	this->font_head = font_head;
	
	this->head.setFont(*this->font_head);
	this->head.setString(headText);

	this->body.setFont(*this->font);
	this->body.setString(bodyText);
}

void UI::UI_Board::display()
{
	this->isDisplayed = true;
}

void UI::UI_Board::hide()
{
	this->isDisplayed = false;
}

void UI::UI_Board::setPosition(sf::Vector2f position)
{
	this->base_shape.setPosition(position);

}

void UI::UI_Board::update(sf::RenderWindow & window)
{
	UI::UI_Base::update(window);
}

void UI::UI_Board::draw(sf::RenderTarget & target)
{
	if (!isDisplayed) {
		return;
	}

	target.draw(base_shape);
	target.draw(head);
	target.draw(body);

}

void UI::UI_Board::setTextPosition(sf::Vector2f position)
{
	sf::Vector2f startPoint = { base_shape.getGlobalBounds().left, base_shape.getGlobalBounds().top };

	this->head.setPosition(sf::Vector2f(
		startPoint.x + base_shape.getLocalBounds().width / 2.0 - 
		(head.findCharacterPos(INT_MAX).x - head.getPosition().x) / 2.0,
		startPoint.y + base_shape.getGlobalBounds().height / 7.0
	));

	this->body.setPosition(
		sf::Vector2f(
			base_shape.getGlobalBounds().left + position.x,
			base_shape.getGlobalBounds().top + position.y
		)
	);

	printf("%f, %f\n", base_shape.getGlobalBounds().left, base_shape.getGlobalBounds().top);
}