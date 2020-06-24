#include "GameState.h"

#include "units/Archer/Archer.h"
#include "units/Knight/GoldenKnight.h"
#include "units/Friendly/Assassin.h"
//#include "units/Healer/Healer.h"
//#include "units/Spearmen/Spearmen.h"

#include "units/Enemy/EvilArcher.h"
#include "units/Enemy/EvilAssassin.h"
#include "units/Enemy/EvilSpearmen.h"

// Save/load
void LUCY::GameState::saveToFile()
{
	std::ofstream file("saved.txt");
	if (file.is_open())
	{
		for (int i = 0; i < 5; i++)
		{
			std::string buffer = std::to_string(i) + "\n" + lanes[i].LaneSerialize();
			std::cout << buffer << std::endl;
			file << buffer;
		}
		file.close();
	}
	else
	{
		std::cout << "File for saving doesn't exist" << std::endl;
	}
}

void LUCY::GameState::loadFromFile()
{
	std::ifstream file("saved.txt");
	int lane = 0;
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string buffer;

			file >> buffer;
			if (buffer.find('$') == std::string::npos)
			{
				if (buffer.length() > 0)
				{
					lane = std::stoi(buffer);
					std::cout << lane << std::endl;
				}
			}
			else
			{
				if (buffer.length() > 0)
				{
					UnitFactories(buffer, lane);
				}
			}
		}
		file.close();
	}
	else
	{
		std::cout << "File for saving doesn't exist" << std::endl;
	}
}

void LUCY::GameState::UnitFactories(std::string buffer, int lane_id)
{
	std::cout << buffer << std::endl;
	UNITS::Friendly* pFriend = nullptr;
	std::vector<std::string> string_var_vector;
	std::string string_var;
	for (int i = 0; i < buffer.length(); i++)
	{
		if (buffer.at(i) == '$')
		{
			string_var_vector.push_back(std::move(string_var));

			string_var.empty();
			string_var.shrink_to_fit();
		}
		else
		{
			string_var.push_back(buffer.at(i));
		}
	}

	//FACTORY
	if (string_var_vector.at(0) == "Archer")
	{
		//need setup for finish load
		pFriend = new UNITS::Archer(data, lanes, lane_id);
		pFriend->StatUnserialize(
			string_var_vector[3],
			string_var_vector[4],
			string_var_vector[5],
			string_var_vector[6],
			string_var_vector[7]
		);
		lanes[lane_id].spawnFriendlyUnit(pFriend, std::stof(string_var_vector[1]));
	}
	else if (string_var_vector.at(0) == "Knight")
	{
		pFriend = new UNITS::GoldenKnight(data, lanes, lane_id);
		pFriend->StatUnserialize(
			string_var_vector[3],
			string_var_vector[4],
			string_var_vector[5],
			string_var_vector[6],
			string_var_vector[7]
		);
		lanes[lane_id].spawnFriendlyUnit(pFriend, std::stof(string_var_vector[1]));
	}
	else if (string_var_vector.at(0) == "Assassin")
	{
		pFriend = new UNITS::Assassin(data, lanes, lane_id);
		pFriend->StatUnserialize(
			string_var_vector[3],
			string_var_vector[4],
			string_var_vector[5],
			string_var_vector[6],
			string_var_vector[7]
		);
		lanes[lane_id].spawnFriendlyUnit(pFriend, std::stof(string_var_vector[1]));
	}
}

// Virtual fn dari IState
void LUCY::GameState::VInit()
{
	// Default resource setup (klo load nanti dioverwrite
	food = 100;
	seed = 5;

	// Load game?
	if (isLoad) {
		loadFromFile();
	}

	renderTexture.create(data->window.getSize().x, data->window.getSize().y);

	selectionArea.setSize(sf::Vector2f(60, LANE_HEIGHT));
	selectionArea.setFillColor(sf::Color(0, 255, 0, 100));
	selectionArea.setOrigin(selectionArea.getGlobalBounds().width / 2.0, selectionArea.getGlobalBounds().height / 2.0);

	background.setTexture(*data->assets.GetTexturePtr("Grass"));
	background.setColor(sf::Color(250, 250, 250, 200));
	background.setPosition(sf::Vector2f(0, 0));

	for (int i = 0; i < TOTAL_LANES; i++) {
		lanes[i].setSpawnPosition(sf::Vector2f(ENEMY_SPAWN_X - 100, (i + 1) * LANE_HEIGHT));
	}

	lanes[0].spawnEnemyUnit(new UNITS::EvilAssassin(data, lanes, 0));
	lanes[1].spawnEnemyUnit(new UNITS::EvilArcher(data, lanes, 1));
	lanes[2].spawnEnemyUnit(new UNITS::EvilArcher(data, lanes, 2));
	lanes[3].spawnEnemyUnit(new UNITS::EvilAssassin(data, lanes, 3));
	lanes[4].spawnEnemyUnit(new UNITS::EvilSpearmen(data, lanes, 4));

	UISetup();
}

void LUCY::GameState::VHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event)) {

		// General
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) { saveToFile(); }

			// Bottom UI seelction
			bottomUISelection(event);

			// Selection area highlighting and what to do on click.
			if (event.type == sf::Event::MouseButtonPressed) {
				int laneNo = UTILS::screenPositionToLaneMap(sf::Mouse::getPosition(data->window), 0, TOTAL_LANES, LANE_HEIGHT);
				if (laneNo != -1) {
					if (isSelectedAreaEmpty(laneNo)) {

						if (selectedUnit == 0) {

							if (food >= 50) {
								food -= 50;
							}

							lanes[laneNo].spawnFriendlyUnit(new UNITS::Archer(data, lanes, laneNo), selectionArea.getPosition().x + selectionArea.getSize().x / 2.0);
						}
						else if (selectedUnit == 1) {


							lanes[laneNo].spawnFriendlyUnit(new UNITS::GoldenKnight(data, lanes, laneNo), selectionArea.getPosition().x + selectionArea.getSize().x / 2.0);
						}
						else if (selectedUnit == 2) {

							lanes[laneNo].spawnFriendlyUnit(new UNITS::Assassin(data, lanes, laneNo), selectionArea.getPosition().x + selectionArea.getSize().x / 2.0);
						}
						else if (selectedUnit == 3) {
							//lanes[laneNo].spawnFriendlyUnit(new UNITS::Spearman(data, lanes, laneNo), selectionArea.getPosition().x + selectionArea.getSize().x / 2.0);
						}
						else if (selectedUnit == 4) {
							//lanes[laneNo].spawnFriendlyUnit(new UNITS::Defender(data, lanes, laneNo), selectionArea.getPosition().x + selectionArea.getSize().x / 2.0);
						}
						else if (selectedUnit == 5) {
							//lanes[laneNo].spawnFriendlyUnit(new UNITS::Healer(data, lanes, laneNo), selectionArea.getPosition().x + selectionArea.getSize().x / 2.0);
						}
						else if (selectedUnit == 6) {

							if (seed >= 1) {
								seed -= 1;
							}

							lanes[laneNo].spawnWheat(data, selectionArea.getPosition().x + selectionArea.getGlobalBounds().width / 2.0);
						}

					}
					else {
						// Harvest wheat
						for (int i = 0; i < lanes[laneNo].getWheatCount(); i++) {
							Wheat* w = lanes[laneNo].getWheat(i);
							if (selectionArea.getGlobalBounds().intersects(
								w->getSprite().getGlobalBounds()))
							{
								if (w->getCurrentState() == Harvest || w->getCurrentState() == Pillage) {
									food += lanes[laneNo].getWheat(i)->getValue();
									lanes[laneNo].getWheat(i)->Remove();
								}
							}
						}
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

	// Update ketika pause
	if (isPausing) {
		pause_menu.update(data->window);
		return;
	}

	bottom_ui.update(data->window);

	resources_ui.update(data->window);

	// Update UI resources dgn data resources yang baru
	foodText.setString(foodStr + std::to_string(food));

	cashText.setString(seedStr + std::to_string(seed));


	int index = UTILS::screenPositionToLaneMap(sf::Mouse::getPosition(data->window), 0, TOTAL_LANES, LANE_HEIGHT);

	// Update posisi Selection Area
	selectionArea.setOrigin(0, 0);
	int xMouse = sf::Mouse::getPosition(data->window).x;
	int yMouse = sf::Mouse::getPosition(data->window).y;
	// Kapan Selection Area berhenti di batas.
	if (index != -1 &&
		UTILS::isInBetween(xMouse, 
					selectionArea.getGlobalBounds().width, 
					data->window.getSize().x - selectionArea.getGlobalBounds().width) &&
		UTILS::isInBetween(yMouse, 0, data->window.getSize().y))
	{
		selectionArea.setPosition(xMouse - selectionArea.getGlobalBounds().width / 2.0, LANE_HEIGHT * index);
	}
	else if (xMouse >= data->window.getSize().x - selectionArea.getGlobalBounds().width) {
		selectionArea.setPosition(data->window.getSize().x - selectionArea.getGlobalBounds().width, LANE_HEIGHT * index);
	}
	else if (xMouse <= selectionArea.getGlobalBounds().width) {
		selectionArea.setPosition(0, LANE_HEIGHT * index);
	}

	// Update enemy unit, friendly unit, dan wheat.
	for (Lane &lane : lanes) {
		for (int i = 0; i < lane.getEnemyCount(); i++) {
			lane.getEnemyUnit(i)->update();
		}
		for (int i = 0; i < lane.getFriendlyCount(); i++) {
			lane.getFriendlyUnit(i)->update();
		}
		for (int i = 0; i < lane.getWheatCount(); i++) {
			lane.getWheat(i)->Update(1);
		}
	}

	// Hapus unit / wheat yang tidak dipakai lagi
	for (int i = 0; i < TOTAL_LANES; i++) {
		lanes[i].removeDeadUnits();
	}

}

void LUCY::GameState::VDraw(float dt)
{
	data->window.clear();

	// Draw ke rendertexture (gameplay only)
	// Spy => Shader bisa diapply ke 1 layar.
	renderTexture.clear();
	renderTexture.draw(background);

	for (int i = 0; i < TOTAL_LANES; i++) {
		for (int j = 0; j < lanes[i].getEnemyCount(); j++) {
			lanes[i].getEnemyUnit(j)->draw(renderTexture);
		}
		for (int j = 0; j < lanes[i].getFriendlyCount(); j++) {
			lanes[i].getFriendlyUnit(j)->draw(renderTexture);
		}
		for (int j = 0; j < lanes[i].getWheatCount(); j++) {
			lanes[i].getWheat(j)->Draw(renderTexture);
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

// Function dlm GameState
void LUCY::GameState::UISetup()
{
	// Setup container unit
	bottom_ui.setOrigin(UI::TOPLEFT);
	bottom_ui.setPosition(sf::Vector2f(400, data->window.getSize().y - BOTTOM_UI_HEIGHT));
	bottom_ui.setSize(sf::Vector2f(data->window.getSize().x - 400, BOTTOM_UI_HEIGHT));
	bottom_ui.setTexture(data->assets.GetTexturePtr("UI_Box"));

	// Add UI components
	bottom_ui.addComponent("Archer",	new UI::Button());
	bottom_ui.addComponent("Knight",	new UI::Button());
	bottom_ui.addComponent("Assassin",	new UI::Button());
	bottom_ui.addComponent("Spearman",	new UI::Button());
	bottom_ui.addComponent("Defender",	new UI::Button());
	bottom_ui.addComponent("Healer",	new UI::Button());
	bottom_ui.addComponent("Wheat",		new UI::Button());

	// Archer
	unitBtnRef[0] = bottom_ui.getComponent<UI::Button>("Archer");
	unitBtnRef[1] = bottom_ui.getComponent<UI::Button>("Knight");
	unitBtnRef[2] = bottom_ui.getComponent<UI::Button>("Assassin");
	unitBtnRef[3] = bottom_ui.getComponent<UI::Button>("Spearman");
	unitBtnRef[4] = bottom_ui.getComponent<UI::Button>("Defender");
	unitBtnRef[5] = bottom_ui.getComponent<UI::Button>("Healer");
	unitBtnRef[6] = bottom_ui.getComponent<UI::Button>("Wheat");

	sf::Vector2f btnSize = { 37 * 2.2, 53 * 2.2 };

	unitBtnRef[0]->set(UI::TOPLEFT, btnSize, 
		data->assets.GetTexturePtr("Archer_Green"),		sf::IntRect(0, 53, 37, 53));
	unitBtnRef[1]->set(UI::TOPLEFT, btnSize, 
		data->assets.GetTexturePtr("Knight_Gold"),		sf::IntRect(61, 0, -37, 53));
	unitBtnRef[2]->set(UI::TOPLEFT, btnSize, 
		data->assets.GetTexturePtr("Assassin_Green"),	sf::IntRect(0, 0, 37, 36));
	unitBtnRef[3]->set(UI::TOPLEFT, btnSize, 
		data->assets.GetTexturePtr("Spearman"),			sf::IntRect(0, 0, 37, 36));
	unitBtnRef[4]->set(UI::TOPLEFT, btnSize, 
		data->assets.GetTexturePtr("Defender"),			sf::IntRect(0, 0, 37, 36));
	unitBtnRef[5]->set(UI::TOPLEFT, btnSize, 
		data->assets.GetTexturePtr("Healer"),			sf::IntRect(0, 0, 37, 36));
	unitBtnRef[6]->set(UI::TOPLEFT, btnSize, 
		data->assets.GetTexturePtr("Wheat"),			sf::IntRect(0, 0, 64, 64));

	float y_btn_position = bottom_ui.getSize().y / 2.0 - unitBtnRef[0]->getSize().y / 2.0;
	float x_btn_position = 53 * 2.2;
	float padding_left = 45;
	int count = 1;

	bottom_ui.setComponentPosition("Archer", 
		sf::Vector2f(40, y_btn_position));
	bottom_ui.setComponentPosition("Knight", 
		sf::Vector2f(padding_left + (count++ * x_btn_position), y_btn_position));
	bottom_ui.setComponentPosition("Assassin", 
		sf::Vector2f(padding_left + (count++ * x_btn_position), y_btn_position));
	bottom_ui.setComponentPosition("Spearman", 
		sf::Vector2f(padding_left + (count++ * x_btn_position), y_btn_position));
	bottom_ui.setComponentPosition("Defender", 
		sf::Vector2f(padding_left + (count++ * x_btn_position), y_btn_position));
	bottom_ui.setComponentPosition("Healer", 
		sf::Vector2f(padding_left + (count++ * x_btn_position), y_btn_position));
	bottom_ui.setComponentPosition("Wheat", 
		sf::Vector2f(padding_left + (count++ * x_btn_position), y_btn_position));

	// Setup container resource
	resources_ui.setOrigin(UI::TOPLEFT);
	resources_ui.setPosition(sf::Vector2f(0, data->window.getSize().y - BOTTOM_UI_HEIGHT));
	resources_ui.setSize(sf::Vector2f(400, BOTTOM_UI_HEIGHT));
	resources_ui.setTexture(data->assets.GetTexturePtr("UI_Box"));

	// Setup resources display
	foodStr = "Food: ";
	seedStr = "Seed: ";

	cashText.setPosition(resources_ui.getPosition().x + 20, resources_ui.getPosition().y + 30);
	cashText.setFont(*data->assets.GetFontPtr("Press_Start"));
	cashText.setCharacterSize(15);

	foodText.setPosition(resources_ui.getPosition().x + 20, resources_ui.getPosition().y + 80);
	foodText.setFont(*data->assets.GetFontPtr("Press_Start"));
	foodText.setCharacterSize(15);

	// Opening alert setup
	alert.setSize(sf::Vector2f(800, 300));
	alert.setOrigin(UI::CENTERED);
	alert.setPosition(sf::Vector2f(data->window.getSize().x / 2.0, 0.0));
	alert.setTitle("How to play:");
	alert.setContent("Plant seeds and harvest crops by clicking on the left grid,\nClick on the heroes to select and spawn them on the field!\nFarming gets you food and killing enemies gets you money.");
	alert.setTitleCharacterSize(30);
	alert.setContentCharacterSize(20);
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
	pause_menu.addComponent("Pause_Resume", new UI::Button());
	pause_menu.addComponent("Pause_Exit", new UI::Button());

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

void LUCY::GameState::clearUnitSelection()
{
	for (int i = 0; i < 7; i++) {
		if (unitBtnRef[i] != nullptr)
			unitBtnRef[i]->setOutline(0, sf::Color());
	}
}

bool LUCY::GameState::isSelectedAreaEmpty(int laneNo)
{
	bool areaIsEmpty = true;

	// Check friendly
	for (int i = 0; i < lanes[laneNo].getFriendlyCount(); i++) {
		if (selectionArea.getGlobalBounds().intersects(
			lanes[laneNo].getFriendlyUnit(i)->getUnitBounds()))
		{
			areaIsEmpty = false;
			break;
		}
	}

	// Check wheat
	for (int i = 0; i < lanes[laneNo].getWheatCount(); i++) {
		if (selectionArea.getGlobalBounds().intersects(
			lanes[laneNo].getWheat(i)->getSprite().getGlobalBounds()))
		{
			areaIsEmpty = false;
			break;
		}
	}

	return areaIsEmpty;
}

void LUCY::GameState::bottomUISelection(sf::Event& event)
{
	// Bottom UI selection
	if (bottom_ui.getComponent<UI::Button>("Archer")->isClicked(event, data->window)) {
		clearUnitSelection();

		if (selectedUnit != 0) {
			unitBtnRef[0]->setOutline(5, sf::Color::White);
			selectedUnit = 0;
		}
	}
	else if (bottom_ui.getComponent<UI::Button>("Knight")->isClicked(event, data->window)) {
		clearUnitSelection();

		if (selectedUnit != 1) {
			unitBtnRef[1]->setOutline(5, sf::Color::White);
			selectedUnit = 1;
		}
	}
	else if (bottom_ui.getComponent<UI::Button>("Assassin")->isClicked(event, data->window)) {
		clearUnitSelection();

		if (selectedUnit != 2) {
			unitBtnRef[2]->setOutline(5, sf::Color::White);
			selectedUnit = 2;
		}
	}
	else if (bottom_ui.getComponent<UI::Button>("Spearman")->isClicked(event, data->window)) {
		clearUnitSelection();

		if (selectedUnit != 3) {
			unitBtnRef[3]->setOutline(5, sf::Color::White);
			selectedUnit = 3;
		}
	}
	else if (bottom_ui.getComponent<UI::Button>("Defender")->isClicked(event, data->window)) {
		clearUnitSelection();

		if (selectedUnit != 4) {
			unitBtnRef[4]->setOutline(5, sf::Color::White);
			selectedUnit = 4;
		}
	}
	else if (bottom_ui.getComponent<UI::Button>("Healer")->isClicked(event, data->window)) {
		clearUnitSelection();

		if (selectedUnit != 5) {
			unitBtnRef[5]->setOutline(5, sf::Color::White);
			selectedUnit = 5;
		}
	}
	else if (bottom_ui.getComponent<UI::Button>("Wheat")->isClicked(event, data->window)) {
		clearUnitSelection();

		if (selectedUnit != 6) {
			unitBtnRef[6]->setOutline(5, sf::Color::White);
			selectedUnit = 6;
		}
	}
}