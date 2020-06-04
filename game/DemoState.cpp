#include "DemoState.h"

namespace LUCY
{
	DemoState::DemoState(GameDataRef data): m_data(data) 
	{
	}
	void DemoState::VInit()
	{
	}
	void DemoState::VDraw(float dt)
	{
		m_data->window.clear(sf::Color::Red);
		m_data->window.display();
	}
	void DemoState::VHandleInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->VExit();
				this->m_data->window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				this->VExit();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			{
				m_data->machine.AddState(StateRef(new DemoState(m_data)), false);			
			}
		}
	}
	void DemoState::VUpdate(float dt)
	{
	}
	void DemoState::VResume()
	{
	}
	void DemoState::VPause()
	{
	}
	void DemoState::VExit()
	{
		m_data->machine.RemoveState();
	}
}

