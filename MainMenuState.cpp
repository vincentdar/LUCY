#include "MainMenuState.h"
#include "GameState.h"

LUCY::MainMenuState::MainMenuState(GameDataRef data) : m_data(data)
{
}

void LUCY::MainMenuState::VInit()
{
	_background.setTexture(m_data->assets.GetTexture("MenuBG"));

	_play.setPosition(sf::Vector2f(100.0f, 100.0f));
	_play.setTexture(m_data->assets.GetTexturePtr("Play_Button"));
	_play.setSize(sf::Vector2f(200.0f, 200.0f));
	_play.init();

	_cam.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, 0));
	_cam.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	m_data->window.setView(_cam);

	// Using camera.h
	/*camera.set(sf::Vector2f(SCREEN_WIDTH / 2, 0), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	camera.setRenderTarget(&m_data->window);
	camera.translateCameraToPosition(sf::Vector2f(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0),
		sf::Vector2f(0, 5.0f));*/

	_clock.restart();
}

void LUCY::MainMenuState::VDraw(float dt)
{
	m_data->window.clear();

	m_data->window.draw(_background);
	_play.draw(m_data->window);

	m_data->window.display();
}

void LUCY::MainMenuState::VHandleInput()
{
	sf::Event event;
	while (m_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->m_data->window.close();
			this->VExit();
		}
		if (_play.isClicked(event, m_data->window))
		{
			m_data->machine.AddState(StateRef(new GameState(m_data)), false);
		}
	}
}

void LUCY::MainMenuState::VUpdate(float dt)
{
	if (m_data->window.getView().getCenter().y <= SCREEN_HEIGHT / 2)
	{
		_cam.move(sf::Vector2f(0, 5.0f));
		_cam.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		m_data->window.setView(_cam);
	}

	//camera.update();

	_play.update(m_data->window);
}

void LUCY::MainMenuState::VResume()
{
}

void LUCY::MainMenuState::VPause()
{
}

void LUCY::MainMenuState::VExit()
{
	_cam = m_data->window.getDefaultView();
	m_data->window.setView(_cam);
	m_data->machine.RemoveState();
}

void LUCY::MainMenuState::playButtonPressed()
{
	m_data->machine.AddState(StateRef(new GameState(m_data)), false);
}