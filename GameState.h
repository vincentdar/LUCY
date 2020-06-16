#pragma once

#include "Game.h"
#include "IState.h"

#include "units/Base_Unit.h"
#include "units/Archer.h"

#include "Lane.h"

#define ENEMY_SPAWN_X data->window.getSize().x

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

		int saveSlot;

	public:
		GameState(GameDataRef data, int saveSlot = -1) 
			: data(data), saveSlot(-1) {}

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