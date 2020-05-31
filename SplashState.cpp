#include "SplashState.h"

#include "controls/Input.h"
#include "ui/UI_Button.h"

namespace LUCY
{
	SplashState::SplashState(GameDataRef data): m_data(data) , m_hero(data)
	{
	}

	void SplashState::VInit()
	{
		//m_hero.VInit();
		Input::get().registerKey("Hello", sf::Keyboard::Space);

		button.setPosition(sf::Vector2f(10, 10));
		button.setColor(sf::Color::White, sf::Color::Blue, sf::Color::Yellow, sf::Color::Red, sf::Color::Green);
		button.setBounds(sf::Vector2f(100, 50));

		button1.setPosition(sf::Vector2f(10, 100));
		button1.setColor(sf::Color::Yellow, sf::Color::Blue, sf::Color::Yellow, sf::Color::White, sf::Color::Red);
		button1.setBounds(sf::Vector2f(100, 50));

		std::cout << button.getID() << std::endl;
		std::cout << button1.getID() << std::endl;

	}
	void SplashState::VDraw(float dt)
	{
		m_data->window.clear();
		button.draw(m_data->window);
		button1.draw(m_data->window);

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

			if (Input::get().getKey("Hello", INPUT_KEYPRESSED, event)) {
				printf("Rip\n");
			}
		}
		//m_hero.VHandleInput();
	}
	void SplashState::VUpdate(float dt)
	{
		//m_hero.VUpdate(dt);
		//if (Utils::get().isMouseOver(sf::Vector2f(0, 0), 50, 50, m_data->window)) {
		//	printf("Success\n");
		//}

		button.update(m_data->window);
		button1.update(m_data->window);
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

