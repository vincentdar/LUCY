#pragma once

#include "Game.h"
#include "IState.h"

#include "units/Base_Unit.h"

#include "ui/UI_Container.h"
#include "ui/UI_Button.h"
#include "ui/UI_Alert.h"
#include "Wheat.h"

#include "Lane.h"

namespace LUCY {

	class GameState
		: public IState
	{
	private:

		// Save To File
		void saveToFile(int slot);
		void loadFromFile(int slot);

		// Resources 
		int food;
		int seed;

		bool isPausing = false;

		// Spawn-related
		int totalNumberOfFriendlyUnits;
		Lane lanes[5];
		int saveSlot;
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

		sf::Text cashText, foodText;

		std::string seedStr, foodStr;

		// Functions untuk create UI dll
		void UISetup();

		// Unit factories utk load game
		void UnitFactories(std::string buffer, int lane_id);

	public:
		GameState(GameDataRef data, int saveSlot = -1) 
			: data(data), saveSlot(saveSlot) {}

		// Fungsi khusus di GameState
		void clearUnitSelection();
		bool isSelectedAreaEmpty(int laneNo);
		void bottomUISelection(sf::Event& event);

		// Fungsi dlm game loop
		void VHandleInput()		override;
		void VInit()			override;
		void VDraw(float dt)	override;
		void VUpdate(float dt)	override;
		void VResume()			override;
		void VPause()			override;
		void VExit()			override;

	};
}