#include "DemoState.h"

namespace LUCY
{
	DemoState::DemoState(GameDataRef data) : m_data(data), gk(data), gk1(data)
	{

	}

	void DemoState::VInit()
	{
		gk.setup(sf::Vector2f(100, 100));
		gk1.setup(sf::Vector2f(100, 200));
	}
	void DemoState::VDraw(float dt)
	{
		m_data->window.clear();

		gk.draw(m_data->window);
		gk1.draw(m_data->window);

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
			else if (sf::Event::KeyReleased == event.type)
			{
				if (event.key.code == sf::Keyboard::Escape)
					this->VExit();
				else if (event.key.code == sf::Keyboard::J)
					m_data->machine.AddState(StateRef(new DemoState(m_data)), false);
				else if (event.key.code == sf::Keyboard::A)
					gk.run();
				else if (event.key.code == sf::Keyboard::Space)
					gk.attack();
				else if (event.key.code == sf::Keyboard::G)
					gk.bash();
			}
		}
	}
	void DemoState::VUpdate(float dt)
	{
		gk.update();
		gk1.update();
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

