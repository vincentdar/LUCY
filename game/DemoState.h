#pragma once
#include "../engine/IState.h"
#include "../engine/Game.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "units/GoldenKnight.h"

namespace LUCY
{
	class DemoState : public IState
	{
	private:
		sf::Clock m_clock;
		sf::Sprite m_background;
		GameDataRef m_data;

		GoldenKnight gk, gk1;

		//Hero m_hero;
	public:
		DemoState(GameDataRef data);
		virtual void VInit();
		virtual void VDraw(float dt);
		virtual void VHandleInput();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();

	};
	
}


