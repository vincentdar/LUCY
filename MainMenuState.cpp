#include "MainMenuState.h"
#include "GameState.h"
#include "LoadingState.h"
#include <SFML/Audio/Music.hpp>

LUCY::MainMenuState::MainMenuState(GameDataRef data) : m_data(data)
{
}

void LUCY::MainMenuState::VInit()
{
	//background
	_background.setTexture(m_data->assets.GetTexture("MenuBackground"));

	//logo
	_logo.setTexture(*m_data->assets.GetTexturePtr("LogoGame"));
	_logo.setOrigin(_logo.getLocalBounds().width / 2.0, _logo.getLocalBounds().height / 1.6);
	_logo.setPosition(m_data->window.getSize().x /2.0, m_data->window.getSize().y/ 3.5);
	UTILS::getScaleToSize(*m_data->assets.GetTexturePtr("LogoGame"), sf::Vector2f(820, 400));
	sf::Vector2f scaleSize = UTILS::getScaleToSize(*m_data->assets.GetTexturePtr("LogoGame"),sf::Vector2f(820, 400));
	_logo.scale(scaleSize);

	//menu box 
	_menuBox.setSize(sf::Vector2f(350.0f, 500.0f));
	_menuBox.setOrigin(_menuBox.getLocalBounds().width / 2.0, _menuBox.getLocalBounds().height / 2.0);
	_menuBox.setPosition(m_data->window.getSize().x / 2.0, m_data->window.getSize().y / 2.0 + 100);
	_menuBox.setFillColor(sf::Color(0, 0, 0, 80));

	//buttons
	/* 
		index [0]=Start/NewGame button
		index[1]=Load game button
		index[2]=Options button
		index[3]=Credits button
		index[4]=Exit button
	*/

	for (int q = 0; q < 4; q++) {
		_buttons[q].setOrigin(UI::TOPLEFT);
		_buttons[q].setSize(sf::Vector2f(300.0f, 75.0f));
		_buttons[q].init();
	}

	float buttonCentered = m_data->window.getSize().x / 2.0 - _buttons[0].getSize().x / 2.0;

	_buttons[0].setPosition(sf::Vector2f(buttonCentered, 265.0f));
	_buttons[0].setTexture(m_data->assets.GetTexturePtr("startButton"));
	_buttons[1].setPosition(sf::Vector2f(buttonCentered, 365.0f));
	_buttons[1].setTexture(m_data->assets.GetTexturePtr("loadButton"));
	_buttons[2].setPosition(sf::Vector2f(buttonCentered, 465.0f));
	_buttons[2].setTexture(m_data->assets.GetTexturePtr("creditsButton"));
	_buttons[3].setPosition(sf::Vector2f(buttonCentered, 565.0f));
	_buttons[3].setTexture(m_data->assets.GetTexturePtr("exitButton"));
	
	_cam.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, 0));
	_cam.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	m_data->window.setView(_cam);

	_clock.restart();

	
	if (!_music.openFromFile("res/sfx/music.wav"))
	{
		std::cout << "Failed to open music" << std::endl;
	}
	_music.setLoop(true);
	_music.play();
}

void LUCY::MainMenuState::VDraw(float dt)
{
	m_data->window.clear();

	m_data->window.draw(_background);
	m_data->window.draw(_menuBox);
	m_data->window.draw(_logo);
	for (int q = 0;q < 4;q++) {
		_buttons[q].draw(m_data->window);
	}
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
		if (_buttons[0].isClicked(event, m_data->window) ){// New Game Button
			m_data->machine.AddState(StateRef(new LoadingState<GameState>(m_data, 3)), false);
		}
		else if (_buttons[1].isClicked(event, m_data->window)) { // Load Game Button
			m_data->machine.AddState(StateRef(new LoadingState<GameState>(m_data, 3, true)), false);
		}
		else if (_buttons[2].isClicked(event, m_data->window)) { // Credits Button
			//MARK TO OPTIMIZE
		}

		else if (_buttons[3].isClicked(event, m_data->window)) { // Exit Button
			m_data->window.close();
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

	for (int q = 0;q < 4;q++) {
		_buttons[q].update(m_data->window);
	}
	
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