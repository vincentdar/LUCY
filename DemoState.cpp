#include "DemoState.h"

#include "Input.h"

#include "MainMenuState.h"

namespace LUCY
{
	DemoState::DemoState(GameDataRef data) : m_data(data), gk(data), gk1(data)
	{

	}

	void DemoState::VInit()
	{
		gk.setup(sf::Vector2f(100, 100));
		gk1.setup(sf::Vector2f(100, 200));
		INPUT.registerKey("Attack", sf::Keyboard::Enter);

		board.setup(m_data->assets.GetFontPtr("Press_Start"),
			m_data->assets.GetFontPtr("Press_Start"),
			"Hello World", "Just passing by");

		board.display();
		board.setSize(sf::Vector2f(500, 400));
		board.setOrigin(UI::UI_Origin::CENTERED);

		board.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		board.setHeadToCenter();
		board.setTextPositionBody(sf::Vector2f(10, 150));

		board.setTexture(m_data->assets.GetTexturePtr("Grass"));

		button.setSize(sf::Vector2f(200, 20));
		button.setPosition(sf::Vector2f(0, 0));
		button.setColor(sf::Color::Blue, sf::Color::Red, sf::Color::Cyan, sf::Color::Red);
	}

	void DemoState::VDraw(float dt)
	{
		m_data->window.clear();

		gk.draw(m_data->window);
		gk1.draw(m_data->window);

		board.draw(m_data->window);

		button.draw(m_data->window);

		m_data->window.display();
	}
	void DemoState::VHandleInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (INPUT.getKey("Attack", InputMode::INPUT_KEYRELEASED, event)) {
				gk1.attack();
			}

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
			}
		}

		if (button.isClicked()) {
			m_data->machine.AddState(StateRef(new MenuState(m_data)));
		}
	}
	void DemoState::VUpdate(float dt)
	{
		gk.update();
		gk1.update();
		board.update(m_data->window);
		button.update(m_data->window);
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

