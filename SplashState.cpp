#include "SplashState.h"

#include "utils/Utils.h"
#include "controls/Input.h"

namespace LUCY
{
	SplashState::SplashState(GameDataRef data): m_data(data) , m_hero(data)
	{
	}
	void SplashState::VInit()
	{
		//m_hero.VInit();
		Input::get()->registerKey("Hello", sf::Keyboard::Space);
	}
	void SplashState::VDraw(float dt)
	{
		m_data->window.clear();

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

			if (Input::get()->getKey("Hello", INPUT_KEYPRESSED, event)) {
				printf("Rip\n");
			}
		}
		//m_hero.VHandleInput();
	}
	void SplashState::VUpdate(float dt)
	{
		//m_hero.VUpdate(dt);
		if (Utils::get()->isMouseOver(sf::Vector2f(0, 0), 50, 50, m_data->window)) {
			printf("Success\n");
		}
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

