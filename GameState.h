#pragma once

#include "Game.h"
#include "IState.h"

#include "units/Base_Unit.h"
#include "units/Archer.h"

#include "ui/UI_Base.h"
#include "ui/UI_Container.h"
#include "ui/UI_Button.h"
#include "ui/UI_Textfield.h"
#include "ui/UI_Alert.h"

#include "Lane.h"

#define ENEMY_SPAWN_X data->window.getSize().x + 100
#define TOTAL_LANES 5
#define BOTTOM_UI_HEIGHT 180
#define LANE_HEIGHT (data->window.getSize().y - BOTTOM_UI_HEIGHT) / TOTAL_LANES

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
		Lane lanes[6];

		int waveNumber;

		GameDataRef data;
		sf::RenderTexture renderTexture;

		sf::Sprite background;

		sf::RectangleShape selectionArea;  

		int saveSlot;

		UI::Container bottom_ui;

		UI::Container pause_menu;

		UI::Alert alert;

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