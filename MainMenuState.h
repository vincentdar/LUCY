#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ui/UI_Button.h"
#include "IState.h"
#include "Camera.h"
#include "Utils.h"

namespace LUCY
{
	class MainMenuState : public LUCY::IState
	{
	private:
		GameDataRef m_data;
		sf::Clock _clock;
		sf::Sprite _logo;
		sf::Sprite _background;
		sf::RectangleShape _menuBox;
		UI::Button _buttons[5];
		sf::View _cam;

		//Camera camera;

	public:
		MainMenuState(GameDataRef data);
		void VInit();
		void VDraw(float dt);
		void VHandleInput();
		void VUpdate(float dt);
		void VResume();
		void VPause();
		void VExit();

		~MainMenuState() {}

		void playButtonPressed();
	};
}
