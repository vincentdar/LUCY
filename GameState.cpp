#include "GameState.h"

void LUCY::GameState::onExitClear()
{
}

// GAME.H EXECUTED FUNCTIONS:

void LUCY::GameState::VHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			VExit();
			data->window.close();
			break;
		default:
			break;
		}
	}
}

void LUCY::GameState::VInit()
{
}

void LUCY::GameState::VDraw(float dt)
{
	data->window.clear();

	data->window.display();
}

void LUCY::GameState::VUpdate(float dt)
{

}

void LUCY::GameState::VResume()
{
}

void LUCY::GameState::VPause()
{
}

void LUCY::GameState::VExit()
{
	// Clear vector of ptrs;
	onExitClear();
}
