#include "DemoState.h"

#include "Input.h"

#include "MainMenuState.h"

namespace LUCY
{
	DemoState::DemoState(GameDataRef data) : m_data(data)
	{

	}

	void DemoState::VInit()
	{
		//sh.loadFromFile("res/shader/fragtest.shader", sf::Shader::Fragment);

		units.push_back(new Archer(m_data));
		units.back()->setup(sf::Vector2f(50, 50));
		
		INPUT.registerKey("Attack", sf::Keyboard::Enter);
		INPUT.registerKey("Move", sf::Keyboard::A);
		INPUT.registerKey("Skill1", sf::Keyboard::Num1);
		INPUT.registerKey("Skill2", sf::Keyboard::Num2);
		INPUT.registerKey("Skill3", sf::Keyboard::Num3);
		INPUT.registerKey("Skill4", sf::Keyboard::Num4);

		cam.set(
			sf::Vector2f(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0),
			sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)
		);

		cam.setRenderTarget(&m_data->window);

		cam.translateCameraToPosition(sf::Vector2f(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0 - 300), 0.5);

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

		//sh.setUniform("u_texture", sf::Shader::CurrentTexture);
	}

	void DemoState::VDraw(float dt)
	{
		m_data->window.clear();

		for (int i = 0; i < units.size(); i++) {
			units[i]->draw();
		}

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
				units[0]->attack();
			}
			else if (INPUT.getKey("Move", InputMode::INPUT_KEYRELEASED, event)) {
				units[0]->run();
			}
			else if (INPUT.getKey("Skill1", InputMode::INPUT_KEYRELEASED, event)) {
				units[0]->setOutlineState(SKILL1);
			}
			else if (INPUT.getKey("Skill2", InputMode::INPUT_KEYRELEASED, event)) {
				units[0]->setOutlineState(SKILL2);
			}
			else if (INPUT.getKey("Skill3", InputMode::INPUT_KEYRELEASED, event)) {
				units[0]->setOutlineState(SKILL3);
			}
			else if (INPUT.getKey("Skill4", InputMode::INPUT_KEYRELEASED, event)) {
				units[0]->setOutlineState(SKILL4);
			}

			if (sf::Event::Closed == event.type)
			{
				this->VExit();
				this->m_data->window.close();
			}
			else if (sf::Event::KeyReleased == event.type)
			{
				if (event.key.code == sf::Keyboard::Escape) {
					this->VExit();
					this->m_data->window.close();
				}
				else if (event.key.code == sf::Keyboard::A)
					units[0]->run();
			}
		}
	}
	void DemoState::VUpdate(float dt)
	{
		for (int i = 0; i < units.size(); i++) {
			units[i]->update();
		}

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
		for (int i = 0; i < units.size(); i++) {
			delete units[i];
		}

		units.clear();

		m_data->machine.RemoveState();
	}
}

