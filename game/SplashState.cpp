#include "SplashState.h"
#include "DemoState.h"

#include "../controls/Input.h"
#include "../ui/UI_Button.h"

//namespace LUCY
//{
//	SplashState::SplashState(GameDataRef data) : m_data(data), m_hero(data)
//	{
//	}
//
//	void SplashState::VInit()
//	{
//		Input::get().registerKey("Hello", sf::Keyboard::Space);
//
//		button.setPosition(sf::Vector2f(10, 10));
//		button.setColor(sf::Color::White, sf::Color::Blue, sf::Color::Yellow, sf::Color::Red, sf::Color::Green);
//		button.setBounds(sf::Vector2f(100, 50));
//
//		button1.setPosition(sf::Vector2f(10, 100));
//		button1.setColor(sf::Color::Yellow, sf::Color::Blue, sf::Color::Yellow, sf::Color::White, sf::Color::Red);
//		button1.setBounds(sf::Vector2f(100, 50));
//
//		std::cout << button.getID() << std::endl;
//		std::cout << button1.getID() << std::endl;
//
//		camera.set(sf::Vector2f(640 / 2, 480 / 2), sf::Vector2f(640, 480));
//		camera.setRenderTarget(&m_data->window);
//		camera.translateCameraToPosition(sf::Vector2f(320, 255), 0.1f);
//	}
//
//	void SplashState::VDraw(float dt)
//	{
//		m_data->window.clear();
//		button.draw(m_data->window);
//		button1.draw(m_data->window);
//
//		m_data->window.display();
//	}
//
//	void SplashState::VHandleInput()
//	{
//
//	}
//}
  
LUCY::SplashState::SplashState(GameDataRef data): m_data(data), m_hero(data)
{
}

void LUCY::SplashState::VInit()
{
	/*logo_sfx.setBuffer(m_data->assets.GetSoundBuffer("LOGO_SFX"));
	logo_sfx.play();*/
	m_data->assets.LoadAssetFromText("res/assets.path");

	//m_data->assets.LoadTexture("SFML_Logo", SFML_LOGO);

	sf_logo.setTexture(m_data->assets.GetTexture("SFML_Logo"));
	sf_logo.setScale(0.5, 0.5);
	sf_logo.setOrigin(sf::Vector2f(sf_logo.getLocalBounds().width / 2, sf_logo.getLocalBounds().height / 2));
	//sf_logo.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	sf_logo.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	std::cout << sf_logo.getOrigin().x << " " << sf_logo.getOrigin().y << std::endl;
	//stop_point.x = SCREEN_WIDTH/2 - sf_logo.getGlobalBounds().width / 3;
	/*sf_logo.setOrigin(sf::Vector2f(sf_logo.getGlobalBounds().width / 3, sf_logo.getGlobalBounds().height));
	sf_logo.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - sf_logo.getGlobalBounds().width/2,
		SCREEN_HEIGHT / 2 - sf_logo.getGlobalBounds().height/2));*/

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
//	void SplashState::VUpdate(float dt)
//	{
//		button.update(m_data->window);
//		button1.update(m_data->window);
//
//		camera.update();
//
//		//std::cout << m_data->window.getView().getCenter().x << " " << m_data->window.getView().getCenter().y << std::endl;
//			this->VExit();
//			this->m_data->window.close();
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//		{
//			this->VExit();
//		}
//}

void LUCY::SplashState::VUpdate(float dt)
{
	if (m_clock.getElapsedTime().asSeconds() < 1.75f)
	{
		opaque = 255 * ( 1.0f - (m_clock.getElapsedTime().asSeconds()) / 1.75f);
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
	
	if (m_clock.getElapsedTime().asSeconds() > 4.5f)
	{
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
	//m_data->machine.AddState(StateRef(new DemoState(this->m_data)), true);
}
