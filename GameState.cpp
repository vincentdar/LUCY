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
	lanes[0].getEnemyUnit(0)->run();
	lanes[0].getEnemyUnit(0)->setOutlineState(HITFLASH);
	
	container1.setPosition(sf::Vector2f(100, 100));
	container1.setSize(sf::Vector2f(200, 200));
	container1.setOrigin(UI::TOPLEFT);
	container1.addComponent("Button", new UI::Button(), sf::Vector2f(0, 0));

	container1.getComponent<UI::Button>("Button")->setOrigin(UI::CENTERED);
	container1.getComponent<UI::Button>("Button")->setSize(sf::Vector2f(100, 50));
	container1.getComponent<UI::Button>("Button")->setTexture(data->assets.GetTexturePtr("bar"));

	container1.addComponent("Textbox", new UI::Textfield(), sf::Vector2f(0, 0));
	container1.getComponent<UI::Textfield>("Textbox")->setOrigin(UI::TOPLEFT);
	container1.getComponent<UI::Textfield>("Textbox")->setSelected(true);
	container1.getComponent<UI::Textfield>("Textbox")->setSize({ 200, 20 });
	container1.getComponent<UI::Textfield>("Textbox")->setup(data->assets.GetFontPtr("Press_Start"), "Hello", sf::Color::Blue);
	container1.getComponent<UI::Textfield>("Textbox")->setMaxCharacters(100);

	alert.setSize(sf::Vector2f(800, 300));
	alert.setOrigin(UI::CENTERED);
	alert.setPosition(sf::Vector2f(data->window.getSize().x / 2.0, 0.0));
	alert.setTitle("Hello World!");
	alert.setContent("Welcome to the game!\nHere's how to play!");
	alert.setTitleCharacterSize(40);
	alert.setContentCharacterSize(25);
	alert.setFont(data->assets.GetFontPtr("Press_Start"));
	alert.setTexture(data->assets.GetTexturePtr("UI_Box"));
	alert.init();
	alert.show();

	alert.translate(sf::Vector2f(data->window.getSize().x / 2.0, data->window.getSize().y / 2.0), 2.0);
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
		container1.handleInput(event, data->window);
		alert.handleInput(event, data->window);

		if (container1.getComponent<UI::Button>("Button")->isClicked(event, data->window)) {
			printf("Hello World!\n");
		}
	}

}

void LUCY::GameState::VUpdate(float dt)
{
	for (Lane &lane : lanes) {
		for (int i = 0; i < lane.getEnemyCount(); i++) {
			lane.getEnemyUnit(i)->update();
		}
	}

	alert.update(data->window);

	container1.update(data->window);
}

void LUCY::GameState::VDraw(float dt)
{
	data->window.clear();

	// Draw ke rendertexture
	renderTexture.clear();

	renderTexture.draw(background);

	container1.draw(renderTexture);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < lanes[i].getEnemyCount(); j++) {
			lanes[i].getEnemyUnit(j)->draw(renderTexture);
		}
	}

	alert.draw(renderTexture);

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

void LUCY::GameState::VResume()
{
}

void LUCY::GameState::VPause()
{
}

void LUCY::GameState::VExit()
{
}
