#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "StateMachine.h"
#include "Macro.h"

namespace LUCY
{
	struct GameData
	{
		AssetManager assets;
		StateMachine machine;
		sf::RenderWindow window;
	};

	typedef std::shared_ptr<GameData> GameDataRef;
	class Game
	{
	private:
		sf::Clock m_clock;
		GameDataRef m_data = std::make_shared<GameData>();
		const float dt = 1.0f / 60.0f;
		bool exit = false;

		void Run();
		void CleanUp();
	public:
		Game(int width, int height, std::string title);
		

	};
}


