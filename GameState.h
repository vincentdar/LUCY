#pragma once

#include "Game.h"
#include "IState.h"
#include "units/Wall.h"

#include "units/Base_Unit.h"

#include "ui/UI_Container.h"
#include "ui/UI_Button.h"
#include "ui/UI_Alert.h"
#include "Wheat.h"
#include "Spawner.h"

#include "Lane.h"

namespace LUCY {

	class GameState
		: public IState
	{
	private:

		// Save To File
		void saveToFile();
		void loadFromFile();

		// Resources 
		int food, seed;

		bool isPausing = false;
		bool isLoad;

		// Spawn-related
		Lane lanes[5];
		int waveNumber;

		GameDataRef data;
		
		// Render variables
		sf::RenderTexture renderTexture;
		sf::Sprite background;

		// Area selection
		sf::RectangleShape selectionArea;  

		// UI Elements
		UI::Container bottom_ui;
		UI::Container resources_ui;
		UI::Container pause_menu;

		UI::Button* unitBtnRef[7];
		int selectedUnit = -1;

		UI::Alert alert;

		sf::Text seedText, foodText, wallHPText;

		Wall wall;

		Spawner spawner;

		// Functions untuk create UI dll
		void UISetup();

		// Unit factories utk load game
		void UnitFactories(std::string buffer, int lane_id);

	public:
		GameState(GameDataRef data, bool isLoad = false)
			: data(data), isLoad(isLoad), wall(data), spawner(lanes, data, &wall) {}

		

		// Fungsi dlm game loop
		void VHandleInput()		override;
		void VInit()			override;
		void VDraw(float dt)	override;
		void VUpdate(float dt)	override;
		void VResume()			override;
		void VPause()			override;
		void VExit()			override;

		// Fungsi khusus di GameState
		void clearUnitSelection();
		bool isSelectedAreaEmpty(int laneNo);
		void bottomUISelection(sf::Event& event);
		void spawnUnitBasedOnSelection(int laneNo);

	};
}