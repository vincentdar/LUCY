#include "GameState.h"

#include "units/Archer.h"

void LUCY::GameState::saveToFile(int slot)
{

}

void LUCY::GameState::loadFromFile(int slot)
{
}

void LUCY::GameState::onExitClear()
{

}

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
	// Load game?
	if (saveSlot != -1) {
		loadFromFile(saveSlot);
	}

	renderTexture.create(data->window.getSize().x, data->window.getSize().y);

	background.setTexture(*data->assets.GetTexturePtr("Grass"));
	background.setPosition(sf::Vector2f(0, 0));

	for (int i = 0; i < 6; i++) {
		lanes[i].setSpawnPosition(sf::Vector2f(ENEMY_SPAWN_X, (i + 1) * 100));
	}

	for (Lane &lane : lanes) {
		lane.spawnEnemyUnit(new Archer(data));
	}
}

void LUCY::GameState::VDraw(float dt)
{
	data->window.clear();

	// Draw ke rendertexture
	renderTexture.clear();

	renderTexture.draw(background);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < lanes[i].getEnemyCount(); j++) {
			lanes[i].getEnemyUnit(j)->draw(renderTexture);
		}
	}

	renderTexture.display();

	sf::Sprite spr(renderTexture.getTexture());

	if (isPausing) {
		data->window.draw(spr);
	}
	else {
		data->window.draw(spr);
	}
 
	data->window.display();
}

void LUCY::GameState::VUpdate(float dt)
{
	for (Lane &lane : lanes) {
		for (int i = 0; i < lane.getEnemyCount(); i++) {
			lane.getEnemyUnit(i)->update();
		}
	}
}

void LUCY::GameState::VResume()
{
}

void LUCY::GameState::VPause()
{
}

void LUCY::GameState::VExit()
{
}
