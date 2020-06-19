#include "GameState.h"

#include "units/Archer.h"

void LUCY::GameState::saveToFile(int slot)
{

}

void LUCY::GameState::loadFromFile(int slot)
{

}

void LUCY::GameState::UISetup()
{
	// Setup container
	bottom_ui.setOrigin(UI::TOPLEFT);
	//bottom_ui.setColor(sf::Color::White);
	bottom_ui.setPosition(sf::Vector2f(400, data->window.getSize().y - 200));
	bottom_ui.setSize(sf::Vector2f(data->window.getSize().x - 400, 200));
	bottom_ui.setTexture(data->assets.GetTexturePtr("UI_Box"));

	// Add UI components
	bottom_ui.addComponent("Archer", new UI::Button(), sf::Vector2f(20, 10));

	// Archer
	UI::Button* btn1 = bottom_ui.getComponent<UI::Button>("Archer");
	btn1->setOrigin(UI::TOPLEFT);
	btn1->setSize(sf::Vector2f(37 * 2.2, 53 * 2.2));
	btn1->setTexture(data->assets.GetTexturePtr("Archer_Black"));
	btn1->setTextureRect(sf::IntRect(0, 53, 37, 53));

	// First alert
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

	UISetup();
	//bottom_ui.translate(sf::Vector2f(400, data->window.getSize().y - 200), 2);
	
	
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

		bottom_ui.handleInput(event, data->window);
		alert.handleInput(event, data->window);

		if (bottom_ui.getComponent<UI::Button>("Archer")->isClicked(event, data->window)) {
			lanes[0].spawnEnemyUnit(new Archer(data));
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

	bottom_ui.update(data->window);
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
	bottom_ui.draw(renderTexture);

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
