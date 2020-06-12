#pragma once

#include "Game.h"
#include "IState.h"
#include "units/Base_Unit.h"

#include "Lane.h"

// Semua gameplay disini!!

namespace LUCY {

	class GameState
		: public IState
	{
	private:
		GameDataRef data;

		Lane lanes[6];

		// GameInfo
		int waveNumber;

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