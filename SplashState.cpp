#include "SplashState.h"
#include "DemoState.h"

#include "Input.h"
#include "ui/UI_Button.h"

LUCY::SplashState::SplashState(GameDataRef data) : m_data(data), m_hero(data)
{
}

void LUCY::SplashState::VInit()
{
	m_data->assets.LoadAssetFromText("res/assets.path");

	logo_sfx.setBuffer(*m_data->assets.GetSoundBufferPtr("Logo_SFX"));
	logo_sfx.play();

	sf_logo.setTexture(m_data->assets.GetTexture("SFML_Logo"));
	sf_logo.setScale(0.5, 0.5);
	sf_logo.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	stop_point.x = SCREEN_WIDTH / 2 - sf_logo.getGlobalBounds().width / 3;
	sf_logo.setOrigin(sf::Vector2f(sf_logo.getGlobalBounds().width / 3, sf_logo.getGlobalBounds().height));


	rect_mask.setSize(sf::Vector2f(500.0f, 128.0f));
	rect_mask.setPosition(sf::Vector2f(sf_logo.getPosition().x + 75.f, sf_logo.getPosition().y - 50.0f));
	rect_mask.setFillColor(sf::Color(15, 0, 20));

	rect_omask.setSize(sf::Vector2f(175.0f, 175.0f));
	rect_omask.setPosition(sf::Vector2f(sf_logo.getPosition().x - 100.0f, sf_logo.getPosition().y - 80.0f));
	rect_omask.setFillColor(sf::Color(15, 0, 20, opaque));
	//m_view = m_data->window.getDefaultView();
	//m_view.zoom(0.75f);
	//m_data->window.setView(m_view);

}

void LUCY::SplashState::VDraw(float dt)
{
	m_data->window.clear(sf::Color(15, 0, 20));
	m_data->window.draw(sf_logo);
	m_data->window.draw(rect_mask);
	m_data->window.draw(rect_omask);
	m_data->window.display();
}

void LUCY::SplashState::VHandleInput()
{
	sf::Event event;
	while (m_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
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
	}
}

void LUCY::SplashState::VUpdate(float dt)
{
	if (m_clock.getElapsedTime().asSeconds() < 1.75f)
	{
		opaque = 255 * (1.0f - (m_clock.getElapsedTime().asSeconds()) / 1.75f);
		rect_omask.setFillColor(sf::Color(15, 0, 20, opaque));
	}

	if (m_clock.getElapsedTime().asSeconds() > 1.75f)
	{
		if (sf_logo.getPosition().x > stop_point.x)
		{
			sf_logo.move(sf::Vector2f(initial_speed_sf, 0.0f));
			rect_mask.move(sf::Vector2f(initial_speed_rectMask, 0.0f));
		}
	}

	/*if (logo_sfx.getStatus() == sf::SoundSource::Status::Stopped)
	{
		VExit();
	}*/
	if (m_clock.getElapsedTime().asSeconds() > 4.75) {
		VExit();
	}
}

void LUCY::SplashState::VResume()
{
}

void LUCY::SplashState::VPause()
{
}

void LUCY::SplashState::VExit()
{
	m_data->machine.AddState(StateRef(new DemoState(this->m_data)), true);
}