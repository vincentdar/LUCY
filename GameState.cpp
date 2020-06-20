#include "GameState.h"

#include "units/Archer/Archer.h"

void LUCY::GameState::saveToFile(int slot)
{

}

void LUCY::GameState::loadFromFile(int slot)
{

}

void LUCY::GameState::UISetup()
{
	// Setup container unit
	bottom_ui.setOrigin(UI::TOPLEFT);
	bottom_ui.setPosition(sf::Vector2f(400, data->window.getSize().y - BOTTOM_UI_HEIGHT));
	bottom_ui.setSize(sf::Vector2f(data->window.getSize().x - 400, BOTTOM_UI_HEIGHT));
	bottom_ui.setTexture(data->assets.GetTexturePtr("UI_Box"));

	// Setup container resource
	resources_ui.setOrigin(UI::TOPLEFT);
	resources_ui.setPosition(sf::Vector2f(0, data->window.getSize().y - BOTTOM_UI_HEIGHT));
	resources_ui.setSize(sf::Vector2f(400, BOTTOM_UI_HEIGHT));
	resources_ui.setTexture(data->assets.GetTexturePtr("UI_Box"));

	// Add UI components
	bottom_ui.addComponent("Archer", new UI::Button(), sf::Vector2f(20, 10));

	// Setup resources
	foodStr = "Food: ";
	cashStr = "Cash: ";

	cashText.setPosition(resources_ui.getPosition().x + 20, resources_ui.getPosition().y + 30);
	cashText.setFont(*data->assets.GetFontPtr("Press_Start"));
	cashText.setCharacterSize(15);
	foodText.setPosition(resources_ui.getPosition().x + 20, resources_ui.getPosition().y + 80);
	foodText.setFont(*data->assets.GetFontPtr("Press_Start"));
	foodText.setCharacterSize(15);

	// Archer
	UI::Button* btn1 = bottom_ui.getComponent<UI::Button>("Archer");
	btn1->setOrigin(UI::TOPLEFT);
	btn1->setSize(sf::Vector2f(37 * 2.2, 53 * 2.2));
	btn1->setTexture(data->assets.GetTexturePtr("Archer_Black"));
	btn1->setTextureRect(sf::IntRect(0, 53, 37, 53));

	// UI

	// Opening alert setup
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

	// Pause menu setup
	pause_menu.setPosition(sf::Vector2f(data->window.getSize().x / 2.0, data->window.getSize().y / 2.0));
	pause_menu.setSize(sf::Vector2f(500, 250));
	pause_menu.setOrigin(UI::CENTERED);
	pause_menu.setTexture(data->assets.GetTexturePtr("UI_Box"));

	// Adding pause UI components
	pause_menu.addComponent("Pause_Resume",
new UI::Button());
pause_menu.addComponent("Pause_Exit",
	new UI::Button());

UI::Button* resumeButton = pause_menu.getComponent<UI::Button>("Pause_Resume");
UI::Button* exitButton = pause_menu.getComponent<UI::Button>("Pause_Exit");

resumeButton->setOrigin(UI::TOPLEFT);
resumeButton->setSize(sf::Vector2f(300, 70));
resumeButton->setColor(sf::Color::Black, sf::Color::White, sf::Color::Magenta, sf::Color::White, sf::Color::White);
resumeButton->setFont(data->assets.GetFontPtr("Press_Start"));
resumeButton->setText("RESUME");

exitButton->setOrigin(UI::TOPLEFT);
exitButton->setSize(sf::Vector2f(300, 70));
exitButton->setColor(sf::Color::Black, sf::Color::White, sf::Color::Magenta, sf::Color::White, sf::Color::White);
exitButton->setFont(data->assets.GetFontPtr("Press_Start"));
exitButton->setText("EXIT");

pause_menu.setComponentPosition("Pause_Resume",
	sf::Vector2f(pause_menu.getSize().x / 2.0 - resumeButton->getSize().x / 2.0, 50));
pause_menu.setComponentPosition("Pause_Exit",
	sf::Vector2f(pause_menu.getSize().x / 2.0 - resumeButton->getSize().x / 2.0, 140));
}

void LUCY::GameState::displayPauseMenu()
{
	if (isPausing) {

	}
}

void LUCY::GameState::onExitClear()
{

}

void LUCY::GameState::VInit()
{
	// Default resource setup (klo load nanti dioverwrite
	cash = food = 0;

	// Load game?
	if (saveSlot != -1) {
		loadFromFile(saveSlot);
	}

	renderTexture.create(data->window.getSize().x, data->window.getSize().y);

	selectionArea.setSize(sf::Vector2f(86, LANE_HEIGHT));
	selectionArea.setFillColor(sf::Color(0, 255, 0, 100));
	selectionArea.setOrigin(selectionArea.getGlobalBounds().width / 2.0, selectionArea.getGlobalBounds().height / 2.0);

	background.setTexture(*data->assets.GetTexturePtr("Grass"));
	background.setPosition(sf::Vector2f(0, 0));

	for (int i = 0; i < 6; i++) {
		lanes[i].setSpawnPosition(sf::Vector2f(ENEMY_SPAWN_X, (i + 1) * LANE_HEIGHT));
	}

	/*for (int i = 0; i < TOTAL_LANES; i++) {
		lanes[i].spawnEnemyUnit(new EvilArcher(data, &lanes[i]));
	}*/

	UISetup();
}

void LUCY::GameState::VHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			VExit();
			data->window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				isPausing = !isPausing;
			}
		}

		// Non game inputs
		alert.handleInput(event, data->window);

		// Game Inputs
		if (!isPausing) {
			bottom_ui.handleInput(event, data->window);

			if (bottom_ui.getComponent<UI::Button>("Archer")->isClicked(event, data->window)) {
				lanes[0].spawnEnemyUnit(new UNITS::Archer(data, &lanes[0]));
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				int laneNo = UTILS.screenPositionToLaneMap(sf::Mouse::getPosition(data->window), 0, TOTAL_LANES, LANE_HEIGHT);
				if (laneNo != -1) {

					bool areaIsEmpty = true;
					for (int i = 0; i < lanes[laneNo].getFriendlyCount(); i++) {
						if (selectionArea.getGlobalBounds().intersects(
							lanes[laneNo].getFriendlyUnit(i)->getUnitBounds())) {
							areaIsEmpty = false;
							break;
						}
					}

					if (areaIsEmpty) {
						lanes[laneNo].spawnFriendlyUnit(new UNITS::Archer(data, &lanes[laneNo]), selectionArea.getPosition().x + selectionArea.getSize().x / 2.0);
						lanes[laneNo].getFriendlyUnit(lanes[laneNo].getFriendlyCount() - 1)->setState(UNITS::MOVE);
					}

				}

			}

		}
		// Pause inputs
		else {
			pause_menu.handleInput(event, data->window);

			if (pause_menu.getComponent<UI::Button>("Pause_Resume")->isClicked(event, data->window)) {
				isPausing = false;
			}
			else if (pause_menu.getComponent<UI::Button>("Pause_Exit")->isClicked(event, data->window)) {
				VExit();
			}
		}
	}

}

void LUCY::GameState::VUpdate(float dt)
{
	alert.update(data->window);

	bottom_ui.update(data->window);

	resources_ui.update(data->window);

	std::stringstream oss;
	oss << food;

	foodText.setString(foodStr + oss.str());

	oss.str(std::string());
	oss << cash;

	cashText.setString(cashStr + oss.str());

	if (isPausing) {
		pause_menu.update(data->window);
		return;
	}

	int index = UTILS.screenPositionToLaneMap(sf::Mouse::getPosition(data->window), 0, TOTAL_LANES, LANE_HEIGHT);

	selectionArea.setOrigin(0, 0);
	if (index != -1)
		selectionArea.setPosition(sf::Mouse::getPosition(data->window).x - 43, LANE_HEIGHT * index);

	for (Lane &lane : lanes) {
		for (int i = 0; i < lane.getEnemyCount(); i++) {
			lane.getEnemyUnit(i)->update();
		}
		for (int i = 0; i < lane.getFriendlyCount(); i++) {
			lane.getFriendlyUnit(i)->update();
		}
	}
}

void LUCY::GameState::VDraw(float dt)
{
	data->window.clear();

	// Draw ke rendertexture (gameplay only)
	renderTexture.clear();

	renderTexture.draw(background);


	for (int i = 0; i < TOTAL_LANES; i++) {
		for (int j = 0; j < lanes[i].getEnemyCount(); j++) {
			lanes[i].getEnemyUnit(j)->draw(renderTexture);
		}
		for (int j = 0; j < lanes[i].getFriendlyCount(); j++) {
			lanes[i].getFriendlyUnit(j)->draw(renderTexture);
		}
	}

	bottom_ui.draw(renderTexture);

	resources_ui.draw(renderTexture);

	renderTexture.draw(cashText);

	renderTexture.draw(foodText);

	renderTexture.draw(selectionArea);

	renderTexture.display();

	sf::Sprite spr(renderTexture.getTexture());

	if (isPausing) {
		sf::Shader sh;
		sh.loadFromFile("res/shader/tint.shader", sf::Shader::Fragment);
		sh.setUniform("u_texture", sf::Shader::CurrentTexture);
		
		data->window.draw(spr, &sh);

		pause_menu.draw(data->window);
	}
	else 
		data->window.draw(spr);

	alert.draw(data->window);

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
	data->machine.RemoveState();
}
