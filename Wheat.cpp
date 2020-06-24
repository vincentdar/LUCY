#include "Wheat.h"

void LUCY::Wheat::Init()
{
	m_texture = *m_data->assets.GetTexturePtr("Wheat");
	m_sprite.setTexture(m_texture);

	rect.width = 64;
	rect.height = 64;
	m_sprite.setTextureRect(rect);
	m_sprite.setPosition(position);

	anim.Attach(m_texture, m_sprite, sf::Vector2i(64, 64));
	anim.Change(1, 1.0f, 0, 0);
	
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0, m_sprite.getLocalBounds().height);

	m_shader.loadFromFile("res/shader/outline.shader", sf::Shader::Fragment);
	m_shader.setUniform("u_texture", sf::Shader::CurrentTexture);
	m_shader.setUniform("outline_color",	 sf::Glsl::Vec4(sf::Color::Black));

	m_state = Grow;

	m_sprite.setScale(1.2, 1.2);
}

void LUCY::Wheat::Planted()
{
	m_state = Grow;
	m_clock.restart();
}

void LUCY::Wheat::Harvested()
{
	m_state = Seed;
}

void LUCY::Wheat::Pillaged()
{
	m_state = Pillage;
}

void LUCY::Wheat::Remove()
{
	m_state = Removed;
}

void LUCY::Wheat::Update(float dt)
{
	anim.Update(dt, m_sprite, true);
	if (m_state == Seed) {
		anim.Change(1, 1.0f, 3, 0);
		
		if (m_clock.getElapsedTime().asSeconds() >= 5) {
			m_clock.restart();
			m_state = Grow;
		}
	}
	else if (m_state == Grow) {
		anim.Change(1, 1.0f, 0, 0);

		if (m_clock.getElapsedTime().asSeconds() >= 15) {
			m_clock.restart();
			m_state = Harvest;
		}
	}
	// Selama 10 detik tidak diharvest : jadi withered = nilainya berkurang.
	else if (m_state == Harvest) {
		anim.Change(1, 1.0f, 1, 0);

		if (m_clock.getElapsedTime().asSeconds() >= 10) {
			m_clock.restart();
			m_state = Withered;
		}
	}
	// Selama 5 detik apabila dibakar musuh otomatis hilang sendiri + value = 0;
	else if (m_state == Pillage) {
		anim.Change(1, 1.0f, 2, 0);
		value = 0;
		if (m_clock.getElapsedTime().asSeconds() >= 5) {
			m_clock.restart();
			m_state = Removed;
		}
	}
	// Withered: tidak diharvest lebih dari 10 detik nilainya jadi 10
	else if (m_state == Withered) {
		anim.Change(1, 1.0f, 2, 0);
		value = 10;
	}
}

void LUCY::Wheat::Draw(sf::RenderTarget & target)
{
	target.draw(m_sprite, &m_shader);
}

sf::Sprite& LUCY::Wheat::getSprite()
{
	return m_sprite;
}
