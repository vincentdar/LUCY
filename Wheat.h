#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Animation.h"

namespace LUCY
{
	enum Crop_State
	{
		// Condition dalam gameplay
		Seed,
		Grow,
		Harvest,
		Pillage,
		Withered,

		// Condition SETELAH diambil (apapun kondisi sebelumnya)
		Removed
	};

	class Wheat
	{
	private:
		sf::Vector2f position;
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::IntRect rect;
		Crop_State m_state;
		int value = 100;

		GameDataRef m_data;
		sf::Clock m_clock;
		Animation anim;

		sf::Shader m_shader;

	public:
		Wheat(GameDataRef data, sf::Vector2f position) : m_data(data), position(position) {}
		void Init();
		void Planted();
		void Harvested();
		void Pillaged();
		void Remove();
		void Update(float dt);
		void Draw(sf::RenderTarget& target);
		sf::Sprite& getSprite();

		Crop_State getCurrentState() { return m_state; }

		sf::Vector2f getPosition() { return m_sprite.getPosition(); }

		int getValue() { return value; }

	};
}


