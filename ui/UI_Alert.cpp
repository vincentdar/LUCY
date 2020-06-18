#include "UI_Alert.h"

namespace UI 
{
	void Alert::setContent(const std::string & content)
	{
		this->contentStr.assign(content);
	}

	void Alert::setTitle(const std::string & title)
	{
		this->titleStr.assign(title);
	}

	void Alert::init()
	{
		if (font == nullptr) {
			printf("Font not set.\n");
			return;
		}

		this->content.setFont(*font);
		this->title.setFont(*font);

		this->setFillColor(color);

		this->content.setString(contentStr);
		this->title.setString(titleStr);

		this->title.setPosition(
			sf::Vector2f(
				base_shape.getPosition().x - UTILS.getTextWidth(this->title) / 2.0,
				base_shape.getGlobalBounds().top + base_shape.getGlobalBounds().height / 5.0
			)
		);

		this->content.setPosition(
			sf::Vector2f(
				base_shape.getPosition().x - UTILS.getTextWidth(this->content) / 2.0,
				base_shape.getPosition().y - content.findCharacterPos(0).y
			)
		);
	}

	void Alert::update(sf::RenderWindow & window)
	{
		Base::update(window);

		if (alert == TIMED) {
			if (timer.getElapsedTime().asSeconds() >= hideTimer) {
				hide();
				alert = CLICK;
			}
		}

		this->title.setPosition(
			sf::Vector2f(
				base_shape.getPosition().x - UTILS.getTextWidth(this->title) / 2.0,
				base_shape.getGlobalBounds().top + base_shape.getGlobalBounds().height / 5.0
			)
		);

		this->content.setPosition(
			sf::Vector2f(
				base_shape.getPosition().x - UTILS.getTextWidth(this->content) / 2.0,
				base_shape.getPosition().y
			)
		);
	}

	void Alert::draw(sf::RenderTarget & target)
	{
		if (isShown) {
			target.draw(base_shape);
			target.draw(title);
			target.draw(content);
		}
	}

	void Alert::handleInput(sf::Event & event, sf::RenderWindow& window)
	{
		if (isShown) {
			if (event.type == sf::Event::MouseButtonPressed &&
				UTILS.isMouseOver(base_shape.getPosition(), base_shape.getSize().x, base_shape.getSize().y, window)) {
				hide();
			}
		}
	}

	void Alert::setFont(sf::Font * font) 
	{
		this->font = font;
	}

	void Alert::setFillColor(sf::Color color)
	{
		this->color = color;
	}

	void Alert::show()
	{
		isShown = true;
	}

	void Alert::hide()
	{
		isShown = false;
	}
}