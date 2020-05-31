#pragma once
#include "IState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "ui/UI_Button.h"

namespace LUCY
{
	class SplashState : public IState
	{
	private:
		sf::Clock m_clock;
		sf::Sprite m_background;
		GameDataRef m_data;

		Hero m_hero;

		// Debug
		UI_Button button;
		UI_Button button1;
	public:
		SplashState(GameDataRef data);
		virtual void VInit();
		virtual void VDraw(float dt);
		virtual void VHandleInput();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();

	};
	
}


