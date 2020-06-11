#pragma once
#include "IState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "units/GoldenKnight.h"
#include "units/Archer.h"
#include "units/Spearman.h"
#include "ui/UI_Board.h"
#include "ui/UI_Button.h"
#include "Camera.h"

namespace LUCY
{
	class DemoState : public IState
	{
	private:
		sf::Clock m_clock;
		sf::Sprite m_background;
		GameDataRef m_data;

		std::vector<BaseUnit*> units;

		UI::Board board;
		UI::Button button;

		sf::Shader sh;

		Camera cam;

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


