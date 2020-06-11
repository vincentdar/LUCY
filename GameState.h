#pragma once

#include "Game.h"
#include "IState.h"
#include "units/Base_Unit.h"
#include <vector>

// Semua gameplay disini!!

namespace LUCY {

	class GameState
		: public IState
	{
	private:
		GameDataRef data;

		std::vector<BaseUnit*> enemyUnits;

		// TODO: Saved file reading!

	public:
		GameState(GameDataRef data) : data(data) {}

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