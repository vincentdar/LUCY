#include "SplashState.h"

namespace LUCY
{
	SplashState::SplashState(GameDataRef data): m_data(data) , m_hero(data)
	{
	}
	void SplashState::VInit()
	{
		m_hero.VInit();
	}
	void SplashState::VDraw(float dt)
	{
		m_data->window.clear(sf::Color::Red);
		m_data->window.draw(m_hero.VGetSprite());
		m_data->window.display();
	}
	void SplashState::VHandleInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->m_data->window.close();
				this->VExit();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				this->VExit();
			}
		}
		m_hero.VHandleInput();
	}
	void SplashState::VUpdate(float dt)
	{
		m_hero.VUpdate(dt);
	}
	void SplashState::VResume()
	{
	}
	void SplashState::VPause()
	{
	}
	void SplashState::VExit()
	{
		m_data->machine.RemoveState();
	}
}

