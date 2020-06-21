#pragma once

#include "Game.h"
#include "IState.h"

#include "units/Base_Unit.h"

#include "ui/UI_Base.h"
#include "ui/UI_Container.h"
#include "ui/UI_Button.h"
#include "ui/UI_Textfield.h"
#include "ui/UI_Text.h"
#include "ui/UI_Alert.h"

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
		int cash;

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

		UI::Button* unitSelectionRef[5];
		int selectedUnit = -1;

		UI::Alert alert;

		sf::Text cashText, foodText;

		std::string cashStr, foodStr;

		// Functions untuk create UI dll
		void UISetup();
		void displayPauseMenu();

	public:
		GameState(GameDataRef data, int saveSlot = -1) 
			: data(data), saveSlot(saveSlot) {}

		// Fungsi khusus di GameState
		void onExitClear();

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