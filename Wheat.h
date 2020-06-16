#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Animation.h"

namespace LUCY
{
	enum Crop_State
	{
		Seed = 0,
		Grow,
		Harvest,
		Pillage
	};

	class Wheat
	{
	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::IntRect rect;
		Crop_State m_state;
		int value = 0;

		GameDataRef m_data;
		sf::Clock m_clock;
		Animation anim;
	public:
		Wheat(GameDataRef data): m_data(data) {}
		void Init();
		void Planted();
		void Harvested();
		void Pillaged();
		void HandleInput();
		void Update(float dt);
		sf::Sprite& getSprite();
	};
}


