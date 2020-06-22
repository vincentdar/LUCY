#include "Wheat.h"

void LUCY::Wheat::Init()
{
	m_texture = m_data->assets.GetTexture("Wheat");
	m_sprite.setTexture(m_texture);
	rect.width = 64;
	rect.height = 64;
	m_sprite.setTextureRect(rect);
	m_sprite.setPosition(10.0f, 500.0f);
	m_state = Grow;
	anim.Attach(m_texture, m_sprite, sf::Vector2i(64, 64));
	anim.Change(1, 1.0f, 0, 0);
}

void LUCY::Wheat::Planted()
{
	m_clock.restart();
	m_state = Grow;
}

void LUCY::Wheat::Harvested()
{
	m_state = Seed;
}

void LUCY::Wheat::Pillaged()
{
	m_state = Pillage;
}

void LUCY::Wheat::HandleInput()
{
	if (UTILS.isMouseOver(m_sprite.getPosition(), m_sprite.getGlobalBounds().width,
		m_sprite.getGlobalBounds().height, m_data->window))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_state == Harvest)
			{
				
			}
			else if (m_state == Pillage)
			{
				m_state = Seed;
			}
		}
	}
}

void LUCY::Wheat::Update(float dt)
{
	anim.Update(dt, m_sprite, true);
	if (m_state == Seed) {
		anim.Change(1, 1.0f, 3, 0);

		// Grow now!
		if (m_clock.getElapsedTime().asSeconds() >= 10) {
			m_clock.restart();
			m_state = Grow;
		}
	}

	else if (m_state == Grow) {
		anim.Change(1, 1.0f, 0, 0);

		if (m_clock.getElapsedTime().asSeconds() >= 10) {
			m_clock.restart();
			m_state = Harvest;
		}
	}

	else if (m_state == Harvest) {
		anim.Change(1, 1.0f, 1, 0);

		if (m_clock.getElapsedTime().asSeconds() >= 10) {
			m_clock.restart();
				m_state = Withered;
		}
	}
	else if (m_state == Pillage || m_state == Withered) {
		anim.Change(1, 1.0f, 2, 0);
	}
}

sf::Sprite& LUCY::Wheat::getSprite()
{
	return m_sprite;
}
