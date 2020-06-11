#include "UI_Board.h"

UI::Board::Board() {}

UI::Board::Board(sf::Font* font_head, sf::Font* font, const std::string& head, const std::string& body, float duration)
{
	setup(font, font_head, head, body, duration);
}

void UI::Board::setup(sf::Font* font, sf::Font* font_head, const std::string& head, const std::string& body, float duration)
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

void UI::Board::display()
{
	this->isDisplayed = true;
}

void UI::Board::hide()
{
	this->isDisplayed = false;
}

void UI::Board::updateTextPosition()
{
	setTextPositionHead(headPos);
	setTextPositionBody(bodyPos);
}

void UI::Board::setPosition(sf::Vector2f position)
{
	this->base_shape.setPosition(position);

	updateTextPosition();
}

void UI::Board::update(sf::RenderWindow & window)
{
	UI::Base::update(window);

	updateTextPosition();
}

void UI::Board::draw(sf::RenderTarget & target)
{
	if (!isDisplayed) {
		return;
	}

	target.draw(base_shape);
	target.draw(head);
	target.draw(body);
}

void UI::Board::setTextPositionHead(sf::Vector2f position)
{
	headPos = position;

	sf::Vector2f startPoint = { base_shape.getGlobalBounds().left, base_shape.getGlobalBounds().top };

	this->head.setPosition(startPoint + position);
}

void UI::Board::setTextPositionBody(sf::Vector2f position)
{
	bodyPos = position;

	this->body.setPosition(
		sf::Vector2f(
			base_shape.getGlobalBounds().left + position.x,
			base_shape.getGlobalBounds().top + position.y
		)
	);
}