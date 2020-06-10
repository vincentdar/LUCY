#include "MainMenuState.h"

namespace LUCY {
	MenuState::MenuState(GameDataRef data) : m_data(data) {}

	void MenuState::VInit()
	{
	}

	void MenuState::VDraw(float dt)
	{
		m_data->window.clear();


		m_data->window.display();
	}

	void MenuState::VHandleInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->VExit();
				this->m_data->window.close();
			}
		}
	}

	void MenuState::VUpdate(float dt)
	{
	}

	void MenuState::VResume()
	{
	}

	void MenuState::VPause()
	{
	}

	void MenuState::VExit()
	{
	}
}