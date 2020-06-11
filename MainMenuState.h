#pragma once

#include <SFML/Graphics.hpp>

#include "IState.h"
#include "Game.h"

namespace LUCY
{
	class MenuState
		: public IState
	{
	private:
		GameDataRef m_data;
	public:
		MenuState(GameDataRef data);
		void VInit();
		void VDraw(float dt);
		void VHandleInput();
		void VUpdate(float dt);
		void VResume();
		void VPause();
		void VExit();

		~MenuState() {}
	};

}